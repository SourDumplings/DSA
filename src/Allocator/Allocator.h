/*
 * @Author: SourDumplings
 * @Date: 2023-08-06 18:04:06
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 内存分配器
 * 
 * 该分配器的基本原理是预先申请一大块内存，将其分作大小固定的小块，使用链表串起来作为内存池，
 * 减少多次调用 malloc 的内存 cookie 成本
 * 参考：《C++ 内存管理》-侯捷
 * 
 * 此为 explicit free list 的方式，即有明确的未分配的内存区域（链表）
 * 如果要找未分配的小块，只需要从 explicit free list 里面找即可，相比于 implicit free list 的方式（如 Allocator2）更节省时间
 * 使用 embedded pointer，利用未分配的小块内存内部的空间存储链表指针
 * 
 * 问题：这个 Allocator 通过 malloc 向 OS 要的内存是不会还回去的，即不会调用 free 去还，很霸道
 * 但是为何 Asan 却检测不出内存泄漏？可能是由于没有经过 malloc 分配内存没有标记所致
 */
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "../Base/BaseDef.h"
#include <cstddef>

namespace CZ
{
    class DLL_EXPORT_IMPORT Allocator
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
            /* 
                embedded pointer 内嵌指针
                将未分配的小块的前 sizeof(obj*) 个字节用作链表结点的 next 指针，不浪费内存
                在小块内存分配出去后 pFreeStore 指针记录了下一个可分配的小块地址
             */
            obj *_pNext = nullptr;
        };

        obj *_pFreeStore = nullptr; // 记录了下一个可分配的小块地址，即内存池链表的头结点指针
    };
}

#define DECLARE_POOL_ALLOC() \
public:\
    static void *operator new(size_t size) { return myAlloc.allocate(size); } \
    static void operator delete(void *pDead, size_t size) { return myAlloc.deallocate(pDead, size); } \
protected:\
    static Allocator myAlloc

#define IMPLEMENT_POOL_ALLOC(className) \
Allocator className::myAlloc

#endif