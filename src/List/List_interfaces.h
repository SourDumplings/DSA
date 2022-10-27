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
    inline typename List<T>::Iterator List<T>::begin()
    {
        return ListIterator<T>(_head->_next);
    }
    template <typename T>
    inline typename List<T>::Iterator List<T>::begin() const
    {
        return ListIterator<T>(_head->_next);
    }

    template <typename T>
    inline typename List<T>::Iterator List<T>::end()
    {
        return ListIterator<T>(_head);
    }
    template <typename T>
    inline typename List<T>::Iterator List<T>::end() const
    {
        return ListIterator<T>(_head);
    }

    template <typename T>
    inline typename List<T>::Rank List<T>::size() const
    {
        return _size;
    }

    template <typename T>
    T& List<T>::front()
    {
        try
        {
            if (!this->empty())
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
            if (!this->empty())
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
            if (!this->empty())
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
            if (!this->empty())
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

    template <typename T>
    const T& List<T>::at(typename List<T>::RankPlus index) const
    {
        Iterator it = begin();
        if (index >= 0)
        {
            if (static_cast<Rank>(index) >= _size)
            {
                printf("Error from List at: index is too large\n");
                throw std::exception();
            }
            for (RankPlus i = 0; i < index; ++i)
            {
                ++it;
            }
        }
        else
        {
            if (static_cast<Rank>(-index) > _size)
            {
                printf("Error from List at: the negative index is too small");
                throw std::exception();
            }

            // 方法一：直接法，仅适用于双链表
            for (int i = 0; i < -index + 1; ++i)
            {
                --it;
            }

            // // 方法二：间接法，亦适用于单链表
            // Iterator temp = it;
            // for (RankPlus i = 0; i < -index; ++i)
            // {
            //     ++temp;
            // }
            // while (temp != end())
            // {
            //     ++temp;
            //     ++it;
            // }
        }
        return *it;
    }

    template <typename T>
    inline T& List<T>::at(RankPlus index)
    { return const_cast<T&>(static_cast<const List<T>&>(*this).at(index)); }

} // CZ

#endif // LIST_INTERFACES_H


