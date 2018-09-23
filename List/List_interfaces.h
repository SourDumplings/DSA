/*
 @Date    : 2018-05-17 19:47:33
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的访问接口函数
 */

#ifndef LIST_INTERFACES_H
#define LIST_INTERFACES_H

#include "List.h"
#include <stdexcept>
#include <iostream>

namespace CZ
{
    template <typename T>
    inline typename List<T>::iterator List<T>::begin()
    {
        return ListIterator<T>(_head->_next);
    }
    template <typename T>
    inline typename List<T>::iterator List<T>::begin() const
    {
        return ListIterator<T>(_head->_next);
    }

    template <typename T>
    inline typename List<T>::iterator List<T>::end()
    {
        return ListIterator<T>(_head);
    }
    template <typename T>
    inline typename List<T>::iterator List<T>::end() const
    {
        return ListIterator<T>(_head);
    }

    template <typename T>
    inline typename List<T>::Rank List<T>::size() const
    {
        return _size;
    }

    template <typename T>
    inline bool List<T>::empty() const
    {
        return _head->_next == _head;
    }

    template <typename T>
    T& List<T>::front()
    {
        try
        {
            if (!empty())
            {
                return _head->_next->_data;
            }
            else
                throw "empty list";
        }
        catch (const char *errMsg)
        {
            printf("Error from List front: %s\n", errMsg);
            throw std::exception();
        }
        return _head->_data;
    }

    template <typename T>
    const T& List<T>::front() const
    {
        try
        {
            if (!empty())
            {
                return _head->_next->_data;
            }
            else
                throw "empty list";
        }
        catch (const char *errMsg)
        {
            printf("Error from List front: %s\n", errMsg);
            throw std::exception();
        }
        return _head->_data;
    }

    template <typename T>
    inline T& List<T>::back()
    {
        try
        {
            if (!empty())
            {
                return _head->_prev->_data;
            }
            else
                throw "empty list";
        }
        catch (const char *errMsg)
        {
            printf("Error from List back: %s\n", errMsg);
            throw std::exception();
        }
        return _head->_data;
    }

    template <typename T>
    inline const T& List<T>::back() const
    {
        try
        {
            if (!empty())
            {
                return _head->_prev->_data;
            }
            else
                throw "empty list";
        }
        catch (const char *errMsg)
        {
            printf("Error from List back: %s\n", errMsg);
            throw std::exception();
        }
        return _head->_data;
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream &os, const List<T> &l) { return os; }

} // CZ

#endif // LIST_INTERFACES_H


