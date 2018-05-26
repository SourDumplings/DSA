/*
 @Date    : 2018-05-22 18:20:50
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
弱智能指针，不带引用计数，是其他智能指针实现的基础
 */

#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#include <cstdio>

namespace CZ
{
    template <typename T> class Shared_ptr;

    template <typename T>
    class Weak_ptr
    {
        friend class Shared_ptr<T>;
    public:
        using Rank = unsigned;

        Weak_ptr(T *ptr_ = nullptr): _ptr(ptr_), _count(1) {}
        ~Weak_ptr()
        {
            // printf("Weak_ptr's destructor\n");
            if (_ptr)
            {
                delete _ptr;
                // printf("memory has been freed\n");
            }
            return;
        }
        operator T*() { return _ptr; }
    private:
        T *_ptr = nullptr;
        Rank _count = 0;
    };
} // CZ

#endif // WEAK_PTR_H


