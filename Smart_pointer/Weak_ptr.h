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
    template <typename T> class Weak_ptr;
    template <typename T> bool operator==(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs);
    template <typename T> bool operator==(const Weak_ptr<T> &lhs, const std::nullptr_t &rhs);
    template <typename T> bool operator==(const std::nullptr_t &lhs, const Weak_ptr<T> &rhs);
    template <typename T> bool operator!=(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs);
    template <typename T> bool operator!=(const Weak_ptr<T> &lhs, const std::nullptr_t &rhs);
    template <typename T> bool operator!=(const std::nullptr_t &lhs, const Weak_ptr<T> &rhs);

    template <typename T>
    class Weak_ptr
    {
        friend class Shared_ptr<T>;
        friend bool operator==<T>(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs);
        friend bool operator==<T>(const Weak_ptr<T> &lhs, const std::nullptr_t &rhs);
        friend bool operator==<T>(const std::nullptr_t &lhs, const Weak_ptr<T> &rhs);
        friend bool operator!=<T>(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs);
        friend bool operator!=<T>(const Weak_ptr<T> &lhs, const std::nullptr_t &rhs);
        friend bool operator!=<T>(const std::nullptr_t &lhs, const Weak_ptr<T> &rhs);
    public:
        using Rank = unsigned;
        Weak_ptr(T *ptr_ = nullptr): _count(1)
        {
            if (ptr_)
            {
                _ptr = ptr_;
            }
        }
        ~Weak_ptr()
        {
            printf("Weak_ptr's destructor\n");
            if (_ptr)
            {
                delete _ptr;
                _ptr = nullptr;
                printf("memory has been freed\n");
            }
            return;
        }
        operator T*() { return _ptr; }
        operator bool() const { return static_cast<bool>(_ptr); }
    private:
        T *_ptr = nullptr;
        Rank _count = 0;
    };

    template <typename T>
    inline bool operator==(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs)
    { return lhs._ptr == rhs._ptr; }
    template <typename T>
    inline bool operator==(const Weak_ptr<T> &lhs, const std::nullptr_t &rhs)
    { return lhs._ptr == nullptr; }
    template <typename T>
    inline bool operator==(const std::nullptr_t &lhs, const Weak_ptr<T> &rhs)
    { return nullptr == rhs._ptr; }

    template <typename T>
    inline bool operator!=(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs)
    { return lhs._ptr != rhs._ptr; }
    template <typename T>
    inline bool operator!=(const Weak_ptr<T> &lhs, const std::nullptr_t &rhs)
    { return lhs._ptr != nullptr; }
    template <typename T>
    inline bool operator!=(const std::nullptr_t &lhs, const Weak_ptr<T> &rhs)
    { return nullptr != rhs._ptr; }
} // CZ

#endif // WEAK_PTR_H


