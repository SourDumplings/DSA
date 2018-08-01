/*
 @Date    : 2018-04-07 11:42:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector类模板的数据访问接口方法
 */

#ifndef VECTOR_INTERFACES_H
#define VECTOR_INTERFACES_H

#include "Vector.h"
#include <stdexcept>

namespace CZ
{
    template <typename T>
    inline typename Vector<T>::iterator Vector<T>::begin()
    {
        return _elem;
    }

    template <typename T>
    inline typename Vector<T>::iterator Vector<T>::begin() const
    {
        return _elem;
    }

    template <typename T>
    inline typename Vector<T>::iterator Vector<T>::end()
    {
        return _elem + _size;
    }

    template <typename T>
    inline typename Vector<T>::iterator Vector<T>::end() const
    {
        return _elem + _size;
    }

    template <typename T>
    inline typename Vector<T>::Rank Vector<T>::size()
    {
        return _size;
    }

    template <typename T>
    inline typename Vector<T>::Rank Vector<T>::size() const
    {
        return _size;
    }

    template <typename T>
    inline typename Vector<T>::Rank Vector<T>::capacity()
    {
        return _capacity;
    }

    template <typename T>
    inline typename Vector<T>::Rank Vector<T>::capacity() const
    {
        return _capacity;
    }

    template <typename T>
    const T& Vector<T>::back() const
    {
        try
        {
            if (_size == 0)
            {
                throw "no elements";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector back: %s\n", errMsg);
            throw std::exception();
        }
        return _elem[_size-1];
    }

    template <typename T>
    T& Vector<T>::back()
    {
        try
        {
            if (_size == 0)
            {
                throw "no elements";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }
        return _elem[_size-1];
    }

    template <typename T>
    const T& Vector<T>::front() const
    {
        try
        {
            if (_size == 0)
            {
                throw "no elements";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector front: %s\n", errMsg);
            throw std::exception();
        }
        return _elem[0];
    }

    template <typename T>
    T& Vector<T>::front()
    {
        try
        {
            if (_size == 0)
            {
                throw "no elements";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector front: %s\n", errMsg);
            throw std::exception();
        }
        return _elem[0];
    }

    template <typename T>
    inline bool Vector<T>::empty()
    {
        return _size == 0;
    }

    template <typename T>
    inline bool Vector<T>::empty() const
    {
        return _size == 0;
    }
}



#endif // VECTOR_INTERFACES_H



