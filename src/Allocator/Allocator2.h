/**
 * @file Allocator2.h
 * @author  SourDumplings (sourdumplings@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2023-12-08
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 * 这个分配器原理是先在堆上申请一个较大的动态内存（Heap），再在其上申请一定的空间作为 Chunk，然后在其上以块（Block）为单位分配内存，比较适合全局单例使用
 * 由于未分配的 Block 和已分配的区块都在 Chunk 中混着，故此为 implicit free list 的方式
 * 即如果要查找一个未分配的 Block 需要把整个 Chunk 遍历一遍，相比于 explicit free list 的方式更消耗时间
 * Block 可以合并
 * Chunk 只能扩展，不能收缩
 * 这个分配器的 Heap 不能扩展，即 Chunk 扩展达到最大值后便不能分配内存了，这样相比于 Allocator 牺牲了一定的扩展性但是方便回收内存
 *
 * 参考：《CSAPP》 9.9.12
 */

#if !defined(ALLOCATOR_2_H)
#define ALLOCATOR_2_H

#include "../Base/BaseDef.h"
#include <cstddef>
#include <cstdint>

namespace DSA
{
    class DLL_EXPORT_IMPORT Allocator2
    {
    public:
        using Rank = uint32_t; // Rank，循址的基本单位，即一个字 Word

        static Allocator2 &get_instance();

        ~Allocator2();

        // 传入参数为 sizeof(obj)，即 obj 的大小，单位为 Byte
        void *allocate(size_t);

        // 传入第二个参数为 sizeof(obj)，即 obj 的大小，单位为 Byte
        void deallocate(void *, size_t);

    private:
        const size_t HEAP_SIZE = 1 << 20; // Heap 的大小，即 Chunk 的最大大小，单位为 Byte
        const size_t CHUNK_SIZE = 1 << 12; // Chunk 扩展的单位大小，单位为 Byte
        const size_t WSIZE = 4; // 字大小，即 Rank 以及头尾 cookie 的大小，单位为 Byte
        const size_t DSIZE = 8; // 双字大小，即 Block 地址对齐的单位，双 Rank 的大小，单位为 Byte

        /* Chunk 和 Heap */
        char *_pBeginByteOfChunk;
        char *_pEndByteOfChunk;
        char *_pEndByteOfHeap;

        Rank *_pHead;

        Allocator2();

        /**
         * @brief 类似于 sbrk 函数，拓展 Chunk incr 个 Byte
         *
         * @param [in] incr
         * @return char* 新区域的起始地址
         */
        char *mem_sbrk(uint64_t incr);

        /**
         * @brief 得到用作头尾的 cookie
         *
         * @param [in] size Block 的大小，即 Block data 的大小加头尾 cookie 的大小
         * @param [in] isAlloc
         * @return Rank
         */
        Rank pack_a_cookie(Rank size, bool isAlloc) const;

        /**
         * @brief 得到 p 所指的头或者尾 cookie 中的 Block 的大小，即 Block data 的大小加头尾 cookie 的大小
         *
         * @param [in] pCookie
         * @return Rank
         */
        Rank get_size_from_cookie(const Rank *pCookie) const;

        /**
         * @brief 从 Cookie 中的信息判断该 Block 是否被分配
         *
         * @param [in] pCookie
         * @return true
         * @return false
         */
        bool is_alloc_from_cookie(const Rank *pCookie) const;

        /* Block 指针结构：

            ... | Prev Block data | ftr | hdr | Block data  | ftr | hdr | Next Block data | ...
                ↑                       ↑     ↑             ↑           ↑
                pbp                     hp    bp            fp          nbp

         */

        /**
         * @brief 从 Block 的指针 bp 中得到指向头 cookie 的指针
         *
         * @param [in] bp
         * @return Rank*
         */
        Rank *get_hp_from_bp(const Rank *bp) const;

        /**
         * @brief 从 Block 的指针 bp 中得到指向尾 cookie 的指针
         *
         * @param [in] bp
         * @return Rank*
         */
        Rank *get_fp_from_bp(const Rank *bp) const;

        /**
         * @brief Get the next blk ptr from blk ptr object
         *
         * @param [in] bp
         * @return Rank*
         */
        Rank *get_nbp_from_bp(const Rank *bp) const;

        /**
         * @brief Get the prev blk ptr from blk ptr object
         *
         * @param [in] bp
         * @return Rank*
         */
        Rank *get_pbp_from_bp(const Rank *bp) const;

        /**
         * @brief 初始化 Heap
         *
         * @return int 0 代表初始化成功
         */
        int mem_init();

        /**
         * @brief 用一个大小为 words 字的未分配的块对 Chunk 进行扩容
         *
         * @param [in] words
         * @return void* Block 的指针
         */
        Rank *mem_extend(Rank words);

        /**
         * @brief 合并前后空闲块
         *
         * @param [in] bp 被考察的块指针
         * @return void*
         */
        Rank *mem_coalesce(Rank *bp);

        /**
         * @brief 找一个 fit aSize 个 Byte 的空闲块
         *
         * @param [in] aSize
         * @return Rank* 找到的空闲块指针 bp，找不到则返回 nullptr
         */
        Rank *find_fit(size_t aSize);

        /**
         * @brief 设置 Cookie，将 bp 所指的块预留大小为 aSize Byte 的数据空间
         * 
         * @param [in] bp 
         * @param [in] aSize 
         */
        void place(Rank *bp, size_t aSize);

        bool is_all_blocks_deallocated() const;
    };
}

#endif // ALLOCATOR_2_H
