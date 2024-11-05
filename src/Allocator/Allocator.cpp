/*
 * @Author: SourDumplings
 * @Date: 2023-08-06 18:08:18
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description:
 */
#include "Allocator.h"

#include <cstdint>
#include <cstdlib>
#include <cstdio>

namespace CZ
{
    void *Allocator::allocate(size_t size)
    {
        obj *p = nullptr;
        if (_pFreeStore == nullptr)
        {
            // linked list 为空，于是申请一大块
            size_t chunk = CHUNK_SIZE * size;
            _pFreeStore = p = static_cast<obj *>(malloc(chunk));

            // 将分配来的一大块分成小块，当做 linked list 一样串起来
            for (size_t i = 0; i < CHUNK_SIZE - 1; ++i)
            {
                p->_pNext = reinterpret_cast<obj *>(reinterpret_cast<uint8_t *>(p) + size);
                p = p->_pNext;
            }
            p->_pNext = nullptr; // last node
        }
        p = _pFreeStore;
        _pFreeStore = _pFreeStore->_pNext;
        return p;
    }

    void Allocator::deallocate(void *p, size_t)
    {
        // 将 p 收回插入 _pFreeStore 前面，即作为新的内存池头结点指针
        // 这样确保分配的内存小块不会丢失
        static_cast<obj *>(p)->_pNext = _pFreeStore;
        _pFreeStore = static_cast<obj *>(p);
    }
}