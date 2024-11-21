/*
 @Date    : 2018-05-22 18:20:50
 @Author  : 酸饺子 (sourdumplings@qq.com)
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
#include "../Base/AbstractBaseEntity.h"
#include "../DSAString/DSAString.h"

namespace DSA
{
    template <typename T>
    class Shared_ptr;

    template <typename T>
    class Weak_ptr : public AbstractBaseEntity
    {
        friend class Shared_ptr<T>;
        friend bool operator==(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs)
        {
            return lhs._ptr == rhs._ptr;
        }
        friend bool operator!=(const Weak_ptr<T> &lhs, const Weak_ptr<T> &rhs)
        {
            return !(lhs == rhs);
        }

    public:
        using Rank = uint32_t;

        Weak_ptr(std::nullptr_t)
        {
            _ptr = nullptr;
        }

        template <typename TD>
        Weak_ptr(TD *ptr_) : _count(1)
        {
            _ptr = ptr_;
        }

        template <typename TD>
        Weak_ptr(const Weak_ptr<TD> &w) : _ptr(w.get())
        {
        }

        ~Weak_ptr()
        {
            //        printf("Weak_ptr's destructor\n");
            if (_ptr)
            {
                delete _ptr;
                _ptr = nullptr;
                //            printf("memory has been freed\n");
            }
        }

        const T *get() const
        {
            return _ptr;
        }

        T *get()
        {
            return const_cast<T *>(static_cast<const Weak_ptr<T> &>(*this).get());
        }

        Rank &use_count()
        {
            return _count;
        }
        const Rank &use_count() const
        {
            return _count;
        }

        operator T *()
        {
            return _ptr;
        }
        operator bool() const
        {
            return static_cast<bool>(_ptr);
        }

        template <typename TD>
        Weak_ptr<T> &operator=(const Weak_ptr<TD> w)
        {
            _ptr = w.get();
            _count = w.use_count();
        }

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override
        {
            return "Weak_ptr";
        }

    private:
        T *_ptr;
        Rank _count;
    };

    template <typename T>
    const char *Weak_ptr<T>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "[" << _ptr << ", " << _count << "]";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T>
    HashRank Weak_ptr<T>::hash() const
    {
        return (Hash<DSAString>()(get_entity_name()) + Hash<T *>()(_ptr) * Hash<Rank>()(_count)) % DSA_MAX_HASH_VALUE;
    }
} // DSA

#endif // WEAK_PTR_H
