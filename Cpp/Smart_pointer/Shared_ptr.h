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
    public:
        Shared_ptr(T *ptr_ = nullptr);
        Shared_ptr(const Shared_ptr &sPtr);
        ~Shared_ptr();

        Shared_ptr& operator=(const Shared_ptr &rhs);
        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;


        T* get();
        const T* get() const;
        unsigned use_count() const;
    private:
        Weak_ptr<T> *_wPtr;
    };

    template <typename T>
    inline Shared_ptr<T>::Shared_ptr(T *ptr_): _wPtr(new Weak_ptr<T>(ptr_)) {}

    template <typename T>
    inline Shared_ptr<T>::Shared_ptr(const Shared_ptr<T> &sPtr): _wPtr(sPtr._wPtr) { ++_wPtr->_count; }

    template <typename T>
    inline Shared_ptr<T>::~Shared_ptr()
    {
        printf("Shared_ptr's destructor\n");
        if (--_wPtr->_count == 0)
        {
            delete _wPtr;
        }
        return;
    }

    template <typename T>
    inline Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr<T> &rhs)
    {
        if (this != &rhs)
        {
            delete _wPtr;
            _wPtr = rhs._wPtr;
            ++_wPtr->_count;
        }
        return *this;
    }

    template <typename T>
    inline const T& Shared_ptr<T>::operator*() const
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
    inline const T* Shared_ptr<T>::operator->() const
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
    inline unsigned Shared_ptr<T>::use_count() const { return _wPtr->_count; }

} // CZ

#endif // SHARED_PTR_H

