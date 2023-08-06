/*
 * @Author: SourDumplings
 * @Date: 2023-08-06 18:04:06
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 内存分配器，使用链表内存池，减少多次调用 malloc 的内存 cookie 成本
 */
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

namespace CZ
{
    class Allocator
    {
    public:
        // 传入参数为 sizeof(obj)，即 obj 的大小，单位为 Byte
        void *allocate(size_t);

        // 传入第二个参数为 sizeof(obj)，即 obj 的大小，单位为 Byte
        void deallocate(void *, size_t);

    private:
        static constexpr size_t CHUNK_SIZE = 8;
        struct obj
        {
            obj *pNext = nullptr; // embedded pointer
        };

        obj *pFreeStore = nullptr;
    };
}

#endif