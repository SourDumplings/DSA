/*
 * @Author: SourDumplings
 * @Date: 2023-08-06 18:08:18
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
 */
#include "Allocator.h"

#include <cstdint>
#include <cstdlib>

namespace CZ
{
    void *Allocator::allocate(size_t size)
    {
        obj *p = nullptr;
        if (pFreeStore == nullptr)
        {
            // linked list 为空，于是申请一大块
            size_t chunk = CHUNK_SIZE * size;
            pFreeStore = p = static_cast<obj*>(malloc(chunk));

            // 将分配来的一大块分成小块，当做 linked list 一样串起来
            for (size_t i = 0; i < CHUNK_SIZE - 1; ++i)
            {
                p->pNext = reinterpret_cast<obj*>(reinterpret_cast<uint8_t*>(p) + size);
                p = p->pNext;
            }
            p->pNext = nullptr; // last node
        }
        p = pFreeStore;
        pFreeStore = pFreeStore->pNext;
        return p;
    }

    void Allocator::deallocate(void *p, size_t)
    {
        // 将 p 收回插入 freeStore 前面
        static_cast<obj*>(p)->pNext = pFreeStore;
        pFreeStore = static_cast<obj*>(p);
    }
}