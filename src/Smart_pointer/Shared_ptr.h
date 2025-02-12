/*
 @Date    : 2018-05-22 16:27:40
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
智能指针类模板Shared_ptr
 */

#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <cstdio>

#include <iostream>

#include "Weak_ptr.h"

namespace DSA
{
    template <typename T>
    class Shared_ptr : public AbstractBaseEntity
    {
        friend bool operator==(const Shared_ptr<T> &lhs, const Shared_ptr<T> &rhs)
        {
            return lhs._wPtr == rhs._wPtr;
        }
        friend bool operator!=(const Shared_ptr<T> &lhs, const Shared_ptr<T> &rhs)
        {
            return !(lhs == rhs);
        }

    public:
        using Rank = uint32_t;

        Shared_ptr(std::nullptr_t);

        // 这里采用成员模板，为了使子类的智能指针可以传给父类
        template <typename TD>
        Shared_ptr(TD *ptr_);
        template <typename TD>
        Shared_ptr(const Shared_ptr<TD> &sPtr);

        ~Shared_ptr();

        template <typename TD>
        Shared_ptr<T> &operator=(const Shared_ptr<TD> &rhs);
        T &operator*();
        const T &operator*() const;
        T *operator->();
        const T *operator->() const;

        T *get();
        const T *get() const;
        Rank use_count() const;
        Weak_ptr<T> *get_wPtr();
        const Weak_ptr<T> *get_wPtr() const;

        operator bool() const;

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

    private:
        Weak_ptr<T> *_wPtr = nullptr;
    };

    template <typename T>
    Shared_ptr<T>::Shared_ptr(std::nullptr_t)
    {
        _wPtr = nullptr;
    }

    template <typename T>
    template <typename TD>
    Shared_ptr<T>::Shared_ptr(TD *ptr_)
    {
        _wPtr = new Weak_ptr<T>(ptr_);
    }

    template <typename T>
    template <typename TD>
    Shared_ptr<T>::Shared_ptr(const Shared_ptr<TD> &sPtr)
        : _wPtr(reinterpret_cast<Weak_ptr<T> *>(const_cast<Weak_ptr<TD> *>(sPtr.get_wPtr())))
    {
        if (_wPtr)
        {
            ++_wPtr->use_count();
        }
    }

    template <typename T>
    Shared_ptr<T>::~Shared_ptr()
    {
        //    printf("Shared_ptr's destructor, _wPtr == nullptr? %d\n", _wPtr == nullptr);
        if (_wPtr && --_wPtr->_count == 0)
        {
            delete _wPtr;
        }
    }

    template <typename T>
    template <typename TD>
    Shared_ptr<T> &Shared_ptr<T>::operator=(const Shared_ptr<TD> &rhs)
    {
        if (reinterpret_cast<const Shared_ptr<TD> *>(this) != &rhs)
        {
            if (_wPtr && --_wPtr->_count == 0)
            {
                delete _wPtr;
            }
            _wPtr = rhs._wPtr;
            if (_wPtr)
            {
                ++_wPtr->_count;
            }
        }
        return *this;
    }

    template <typename T>
    const T &Shared_ptr<T>::operator*() const
    {
        ASSERT_DEBUG(_wPtr, "pointer is nullptr");
        return *(_wPtr->_ptr);
    }

    template <typename T>
    inline T &Shared_ptr<T>::operator*()
    {
        return const_cast<T &>(*(static_cast<const Shared_ptr<T> &>(*this)));
    }

    template <typename T>
    const T *Shared_ptr<T>::operator->() const
    {
        ASSERT_DEBUG(_wPtr, "pointer is nullptr");
        return _wPtr->_ptr;
    }

    template <typename T>
    inline T *Shared_ptr<T>::operator->()
    {
        return const_cast<T *>((static_cast<const Shared_ptr<T> &>(*this)).operator->());
    }

    template <typename T>
    inline T *Shared_ptr<T>::get()
    {
        return const_cast<T *>(static_cast<const Shared_ptr<T> &>(*this).get());
    }

    template <typename T>
    const T *Shared_ptr<T>::get() const
    {
        if (_wPtr)
        {
            return _wPtr->_ptr;
        }
        return nullptr;
    }

    template <typename T>
    inline Weak_ptr<T> *Shared_ptr<T>::get_wPtr()
    {
        return _wPtr;
    }

    template <typename T>
    inline const Weak_ptr<T> *Shared_ptr<T>::get_wPtr() const
    {
        return _wPtr;
    }

    template <typename T>
    inline typename Shared_ptr<T>::Rank Shared_ptr<T>::use_count() const
    {
        return _wPtr ? _wPtr->_count : 0;
    }

    template <typename T>
    inline Shared_ptr<T>::operator bool() const
    {
        return static_cast<bool>(_wPtr);
    }

    template <typename T>
    const char *Shared_ptr<T>::get_entity_name() const
    {
        return "Shared_ptr";
    }

    template <typename T>
    const char *Shared_ptr<T>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "[" << (_wPtr ? _wPtr->get() : nullptr) << ", " << use_count() << "]";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T>
    HashRank Shared_ptr<T>::hash() const
    {
        return (Hash<DSAString>()(get_entity_name()) + Hash<T*>()(_wPtr ? _wPtr->get() : nullptr)
            * Hash<Rank>()(use_count())) % DSA_MAX_HASH_VALUE;
    }

} // DSA

#endif // SHARED_PTR_H
