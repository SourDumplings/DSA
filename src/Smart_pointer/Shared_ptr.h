/*
 @Date    : 2018-05-22 16:27:40
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
智能指针类模板Shared_ptr
 */

#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <cstdio>
#include <stdexcept>
#include <iostream>

#include "Weak_ptr.h"

namespace CZ
{
template<typename T>
class Shared_ptr
{
    friend bool operator==(const Shared_ptr<T> &lhs, const Shared_ptr<T> &rhs)
    { return lhs._wPtr == rhs._wPtr; }
    friend bool operator!=(const Shared_ptr<T> &lhs, const Shared_ptr<T> &rhs)
    { return !(lhs == rhs); }
public:
    using Rank = uint32_t;

    Shared_ptr(std::nullptr_t);

    // 这里采用成员模板，为了使子类的智能指针可以传给父类
    template<typename TD>
    Shared_ptr(TD *ptr_);
    template<typename TD>
    Shared_ptr(const Shared_ptr<TD> &sPtr);

    ~Shared_ptr();

    template<typename TD>
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
private:
    Weak_ptr<T> *_wPtr = nullptr;
};

template<typename T>
Shared_ptr<T>::Shared_ptr(std::nullptr_t)
{ _wPtr = nullptr; }

template<typename T>
template<typename TD>
Shared_ptr<T>::Shared_ptr(TD *ptr_)
{
    _wPtr = new Weak_ptr<T>(ptr_);
}

template<typename T>
template<typename TD>
Shared_ptr<T>::Shared_ptr(const Shared_ptr<TD> &sPtr)
    : _wPtr(reinterpret_cast<Weak_ptr<T> *>(const_cast<Weak_ptr<TD> *>(sPtr.get_wPtr())))
{
    if (_wPtr)
    {
        ++_wPtr->use_count();
    }
}

template<typename T>
Shared_ptr<T>::~Shared_ptr()
{
//    printf("Shared_ptr's destructor, _wPtr == nullptr? %d\n", _wPtr == nullptr);
    if (_wPtr && --_wPtr->_count == 0)
    {
        delete _wPtr;
    }
    return;
}

template<typename T>
template<typename TD>
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

template<typename T>
const T &Shared_ptr<T>::operator*() const
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

template<typename T>
inline T &Shared_ptr<T>::operator*()
{ return const_cast<T &>(*(static_cast<const Shared_ptr<T> &>(*this))); }

template<typename T>
const T *Shared_ptr<T>::operator->() const
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

template<typename T>
inline T *Shared_ptr<T>::operator->()
{ return const_cast<T *>((static_cast<const Shared_ptr<T> &>(*this)).operator->()); }

template<typename T>
inline T *Shared_ptr<T>::get()
{ return _wPtr->_ptr; }

template<typename T>
inline const T *Shared_ptr<T>::get() const
{ return _wPtr->_ptr; }

template<typename T>
inline Weak_ptr<T> *Shared_ptr<T>::get_wPtr()
{ return _wPtr; }

template<typename T>
inline const Weak_ptr<T> *Shared_ptr<T>::get_wPtr() const
{ return _wPtr; }

template<typename T>
inline typename Shared_ptr<T>::Rank Shared_ptr<T>::use_count() const
{ return _wPtr->_count; }

template<typename T>
inline Shared_ptr<T>::operator bool() const
{ return static_cast<bool>(_wPtr); }

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Shared_ptr<T> &sP)
{ return os; }

} // CZ

#endif // SHARED_PTR_H
