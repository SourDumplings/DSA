/*
 @Date    : 2018-05-22 16:27:40
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
智能指针模板类Shared_ptr
 */

#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <cstdio>
#include <stdexcept>

#include "Weak_ptr.h"

namespace CZ
{
    template <typename T>
    class Shared_ptr
    {
        friend bool operator==(const Shared_ptr<T> &lhs, const Shared_ptr<T> &rhs)
        { return lhs._wPtr == rhs._wPtr; }
        friend bool operator!=(const Shared_ptr<T> &lhs, const Shared_ptr<T> &rhs)
        { return !(lhs == rhs); }
    public:
        using Rank = unsigned;

        Shared_ptr(std::nullptr_t);
        template <typename U>
        Shared_ptr(U *ptr_);

        Shared_ptr(const Shared_ptr &sPtr);
        ~Shared_ptr();

        Shared_ptr& operator=(const Shared_ptr &rhs);
        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;


        T* get();
        const T* get() const;
        Rank use_count() const;

        operator bool() const;
    private:
        Weak_ptr<T> *_wPtr = nullptr;
    };

    template <typename T>
    Shared_ptr<T>::Shared_ptr(std::nullptr_t) { _wPtr = nullptr; }

    template <typename T>
    template <typename U>
    Shared_ptr<T>::Shared_ptr(U *ptr_)
    {
        _wPtr = new Weak_ptr<T>(ptr_);
    }

    template <typename T>
    Shared_ptr<T>::Shared_ptr(const Shared_ptr<T> &sPtr): _wPtr(sPtr._wPtr)
    {
        if (_wPtr)
        {
            ++_wPtr->_count;
        }
    }

    template <typename T>
    Shared_ptr<T>::~Shared_ptr()
    {
        printf("Shared_ptr's destructor, _wPtr == nullptr? %d\n", _wPtr == nullptr);
        if (_wPtr && --_wPtr->_count == 0)
        {
            delete _wPtr;
        }
        return;
    }

    template <typename T>
    Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr<T> &rhs)
    {
        if (this != &rhs)
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
    const T& Shared_ptr<T>::operator*() const
    {
        try
        {
            if (_wPtr == nullptr)
            {
                throw "pointer is nullptr";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }
        return *(_wPtr->_ptr);
    }

    template <typename T>
    inline T& Shared_ptr<T>::operator*()
    { return const_cast<T&>(*(static_cast<const Shared_ptr<T>&>(*this))); }

    template <typename T>
    const T* Shared_ptr<T>::operator->() const
    {
        try
        {
            if (!_wPtr)
            {
                throw "pointer is nullptr";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }
        return _wPtr->_ptr;
    }

    template <typename T>
    inline T* Shared_ptr<T>::operator->()
    { return const_cast<T*>((static_cast<const Shared_ptr<T>&>(*this)).operator->()); }

    template <typename T>
    inline T* Shared_ptr<T>::get() { return _wPtr->_ptr; }

    template <typename T>
    inline const T* Shared_ptr<T>::get() const { return _wPtr->_ptr; }

    template <typename T>
    inline typename Shared_ptr<T>::Rank Shared_ptr<T>::use_count() const { return _wPtr->_count; }

    template <typename T>
    inline Shared_ptr<T>::operator bool() const
    { return static_cast<bool>(_wPtr); }

} // CZ

#endif // SHARED_PTR_H
