#include "Allocator2.h"

#include <cstdlib>
#include "../Base/Assert.h"
#include "../Algorithms/Max.h"


namespace DSA
{
    Allocator2::Allocator2()
        : _pHead(nullptr)
    {
        _pBeginByteOfChunk = static_cast<char *>(malloc(HEAP_SIZE));
        _pEndByteOfChunk = _pBeginByteOfChunk;
        _pEndByteOfHeap = _pBeginByteOfChunk + HEAP_SIZE;
    }

    Allocator2::~Allocator2()
    {
        ASSERT_DEBUG(is_all_blocks_deallocated(), "Some blocks are not deallocated!");

        free(_pEndByteOfHeap - HEAP_SIZE);
    }

    Allocator2 &Allocator2::get_instance()
    {
        static Allocator2 instance;
        if (instance._pHead == nullptr)
        {
            instance.mem_init();
        }

        return instance;
    }

    int Allocator2::mem_init()
    {
        if ((_pHead = reinterpret_cast<Rank *>(mem_sbrk(4 * WSIZE))) == nullptr)
        {
            return -1;
        }

        *_pHead = 0; // 对齐 Padding
        *(_pHead + 1) = pack_a_cookie(DSIZE, true); // Prologue header，即序言块的头 Cookie
        *(_pHead + 2) = pack_a_cookie(DSIZE, true); // Prologue footer，即序言块的尾 Cookie
        *(_pHead + 3) = pack_a_cookie(0, true); // Epilogue header，即结尾块的头 Cookie
        _pHead += 2;
        /* 
        双字对齐的 Heap：
        |   | 8/1 | 8/1 | hdr |   first Block data   | ftr | ... | hdr | last Block data | ftr | 0/1 |
        ↑         ↑                                                                                  ↑
        A         B                                                                                  C
        A：_pBeginByteOfChunk
        B：_pHead
        C：_pEndByteOfChunk
         */

        if (mem_extend(CHUNK_SIZE / WSIZE) == nullptr)
        {
            return -2;
        }
        return 0;
    }

    typename Allocator2::Rank *Allocator2::mem_extend(Rank words)
    {
        Rank *bp = nullptr;
        Rank size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE; // 保持双字对齐
        if ((bp = reinterpret_cast<Rank *>(mem_sbrk(size))) == nullptr)
        {
            return nullptr;
        }

        *get_hp_from_bp(bp) = pack_a_cookie(size, false); // Free block header，即空闲块的头 Cookie
        *get_fp_from_bp(bp) = pack_a_cookie(size, false); // Free block footer，即空闲块的尾 Cookie
        *get_hp_from_bp(get_nbp_from_bp(bp)) = pack_a_cookie(0, true); // New epilogue header，即新的结尾块的头 Cookie

        // 考察一下前一个块是否也是空闲的需要合并
        return mem_coalesce(bp);
    }

    typename Allocator2::Rank *Allocator2::mem_coalesce(Rank *bp)
    {
        bool isPrevAlloc = is_alloc_from_cookie(get_fp_from_bp(get_pbp_from_bp(bp)));
        bool isNextAlloc = is_alloc_from_cookie(get_hp_from_bp(get_nbp_from_bp(bp)));
        Rank size = get_size_from_cookie(get_hp_from_bp(bp));

        if (isPrevAlloc && isNextAlloc)
        {
            // Case 1
            return bp;
        }

        if (isPrevAlloc && !isNextAlloc)
        {
            // Case 2
            size += get_size_from_cookie(get_hp_from_bp(get_nbp_from_bp(bp)));
            *get_hp_from_bp(bp) = pack_a_cookie(size, false);
            *get_fp_from_bp(bp) = pack_a_cookie(size, false);
        }
        else if (!isPrevAlloc && isNextAlloc)
        {
            // Case 3
            size += get_size_from_cookie(get_hp_from_bp(get_pbp_from_bp(bp)));
            *get_fp_from_bp(bp) = pack_a_cookie(size, false);
            *get_hp_from_bp(get_pbp_from_bp(bp)) = pack_a_cookie(size, false);
            bp = get_pbp_from_bp(bp);
        }
        else
        {
            // Case 4
            size += get_size_from_cookie(get_hp_from_bp(get_nbp_from_bp(bp))) + get_size_from_cookie(get_hp_from_bp(get_pbp_from_bp(bp)));
            *get_hp_from_bp(get_pbp_from_bp(bp)) = pack_a_cookie(size, false);
            *get_fp_from_bp(get_nbp_from_bp(bp)) = pack_a_cookie(size, false);
            bp = get_pbp_from_bp(bp);
        }
        return bp;
    }

    char *Allocator2::mem_sbrk(uint64_t incr)
    {
        char *pOldBrk = _pEndByteOfChunk;
        ASSERT_DEBUG(_pEndByteOfChunk + incr <= _pEndByteOfHeap, "Error: mem_sbrk failed! Ran out of memory!");
        if (_pEndByteOfHeap < _pEndByteOfChunk + incr)
        {
            return nullptr;
        }

        _pEndByteOfChunk += incr;
        return pOldBrk;
    }

    void *Allocator2::allocate(size_t size)
    {
        if (size == 0)
        {
            return nullptr;
        }

        size_t aSize; // 调整后的块大小
        size_t extendSize; // 对于 Chunk 的扩容大小，如果不 fit 的话
        Rank *bp = nullptr;

        // 将 size 调整为包含头尾两个 Cookie 后的 Block 的大小
        if (size <= DSIZE)
        {
            aSize = 2 * DSIZE;
        }
        else
        {
            aSize = DSIZE * ((size + DSIZE * 2 - 1) / DSIZE);
        }

        // 查找未分配的 Block 看有无 fit 的
        if ((bp = find_fit(aSize)) != nullptr)
        {
            place(bp, aSize);
            return bp;
        }

        // 没有 fit 的空闲块，则需要更多的空间来放置块
        extendSize = Max(aSize, CHUNK_SIZE);
        if ((bp = mem_extend(extendSize / WSIZE)) == nullptr)
        {
            return nullptr;
        }
        place(bp, aSize);
        return bp;
    }

    typename Allocator2::Rank *Allocator2::find_fit(size_t aSize)
    {
        Rank *bp = nullptr;
        for (bp = _pHead; get_size_from_cookie(get_hp_from_bp(bp)) > 0; bp = get_nbp_from_bp(bp))
        {
            if (!is_alloc_from_cookie(get_hp_from_bp(bp)) && (aSize <= get_size_from_cookie(get_hp_from_bp(bp))))
            {
                return bp;
            }
        }
        return nullptr;
    }

    void Allocator2::place(Rank *bp, size_t aSize)
    {
        size_t blockSize = get_size_from_cookie(get_hp_from_bp(bp));
        if (2 * DSIZE <= blockSize - aSize)
        {
            *get_hp_from_bp(bp) = pack_a_cookie(aSize, true);
            *get_fp_from_bp(bp) = pack_a_cookie(aSize, true);
            bp = get_nbp_from_bp(bp);
            *get_hp_from_bp(bp) = pack_a_cookie(blockSize - aSize, false);
            *get_fp_from_bp(bp) = pack_a_cookie(blockSize - aSize, false);
        }
        else
        {
            *get_hp_from_bp(bp) = pack_a_cookie(blockSize, true);
            *get_fp_from_bp(bp) = pack_a_cookie(blockSize, true);
        }
    }

    void Allocator2::deallocate(void *p, size_t)
    {
        if (p == nullptr)
        {
            return;
        }
        Rank *bp = static_cast<Rank *>(p);
        Rank size = get_size_from_cookie(get_hp_from_bp(bp));

        if (_pHead == nullptr)
        {
            mem_init();
        }

        *get_hp_from_bp(bp) = pack_a_cookie(size, false);
        *get_fp_from_bp(bp) = pack_a_cookie(size, false);
        mem_coalesce(bp);
    }

    inline typename Allocator2::Rank Allocator2::pack_a_cookie(Rank size, bool isAlloc) const
    {
        return isAlloc ? (size | 1) : (size | 0);
    }

    inline typename Allocator2::Rank Allocator2::get_size_from_cookie(const Rank *pCookie) const
    {
        return *pCookie & ~0x7;
    }

    inline bool Allocator2::is_alloc_from_cookie(const Rank *pCookie) const
    {
        return static_cast<bool>(*pCookie & 0x1);
    }

    inline typename Allocator2::Rank *Allocator2::get_hp_from_bp(const Rank *bp) const
    {
        return const_cast<Rank*>(bp - 1);
    }

    inline typename Allocator2::Rank *Allocator2::get_fp_from_bp(const Rank *bp) const
    {
        return const_cast<Rank*>(bp + get_size_from_cookie(get_hp_from_bp(bp)) / WSIZE - 2);
    }

    inline typename Allocator2::Rank *Allocator2::get_nbp_from_bp(const Rank *bp) const
    {
        return const_cast<Rank*>(bp + get_size_from_cookie(bp - 1) / WSIZE);
    }

    inline typename Allocator2::Rank *Allocator2::get_pbp_from_bp(const Rank *bp) const
    {
        return const_cast<Rank*>(bp - get_size_from_cookie(bp - 2) / WSIZE);
    }

    bool Allocator2::is_all_blocks_deallocated() const
    {
        for (Rank *bp = _pHead + 2; bp < reinterpret_cast<const Rank*>(_pEndByteOfChunk) - 1; bp = get_nbp_from_bp(bp))
        {
            if (is_alloc_from_cookie(get_hp_from_bp(bp)))
            {
                printf("Bp: %p is not deallocated!", bp);
                return false;
            }
        }
        printf("All blocks have been deallocated!\n");
        return true;
    }
}