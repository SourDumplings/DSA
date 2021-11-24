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
#include <iostream>

namespace CZ
{
template<typename T>
class Shared_ptr;

template<typename T>
class Weak_ptr
{
    friend class Shared_ptr<T>;
    friend bool operator==(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs)
    { return lhs._ptr == rhs._ptr; }
    friend bool operator!=(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs)
    { return !(lhs == rhs); }
public:
    using Rank = int32_t;

    Weak_ptr(std::nullptr_t)
    { _ptr = nullptr; }

    template<typename TD>
    Weak_ptr(TD *ptr_): _count(1)
    {
        _ptr = ptr_;
    }

    template<typename TD>
    Weak_ptr(const Weak_ptr<TD> &w): _ptr(w.get())
    {}

    ~Weak_ptr()
    {
//        printf("Weak_ptr's destructor\n");
        if (_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
//            printf("memory has been freed\n");
        }
        return;
    }

    T *get() const
    { return _ptr; }
    Rank &use_count()
    { return _count; }
    const Rank &use_count() const
    { return _count; }

    operator T *()
    { return _ptr; }
    operator bool() const
    { return static_cast<bool>(_ptr); }

    template<typename TD>
    Weak_ptr<T> &operator=(const Weak_ptr<TD> w)
    {
        _ptr = w.get();
        _count = w.use_count();
    }
private:
    T *_ptr;
    Rank _count;
};

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Weak_ptr<T> &wP)
{ return os; }

} // CZ

#endif // WEAK_PTR_H
