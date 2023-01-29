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

#include "../Base/Assert.h"
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
    const T &List<T>::front() const
    {
        ASSERT_DEBUG(!this->empty(), "empty list");
        return _head->_next->_data;
    }

    template <typename T>
    inline T &List<T>::front()
    {
        return const_cast<T &>(static_cast<const List<T>&>(*this).front());
    }

    template <typename T>
    inline const T &List<T>::back() const
    {
        ASSERT_DEBUG(!this->empty(), "empty list");
        return _head->_prev->_data;
    }

    template <typename T>
    inline T &List<T>::back()
    {
        return const_cast<T &>(static_cast<const List<T>&>(*this).back());
    }

    template <typename T>
    const T &List<T>::at(typename List<T>::RankPlus index) const
    {
        Iterator it = begin();
        if (index >= 0)
        {
            ASSERT_DEBUG(_size < static_cast<Rank>(index), "Error from List at: index is too large");
            for (RankPlus i = 0; i < index; ++i)
            {
                ++it;
            }
        }
        else
        {
            ASSERT_DEBUG(_size <= static_cast<Rank>(-index), "Error from List at: the negative index is too small");

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
    inline T &List<T>::at(RankPlus index)
    {
        return const_cast<T &>(static_cast<const List<T> &>(*this).at(index));
    }

    template <typename T>
    const char *List<T>::get_entity_name() const
    {
        return "List";
    }

    template <typename T>
    template <typename Pred>
    typename List<T>::Iterator List<T>::search_if(const Pred &predicate) const noexcept
    {
        for (Iterator it = begin(); it != end(); ++it)
        {
            if (predicate(*it))
            {
                return it;
            }
        }
        return end();
    }

    template <typename T>
    inline typename List<T>::Iterator List<T>::search(const T &value) const noexcept
    {
        return search_if([&](const T &data) { return data == value; });
    }

} // CZ

#endif // LIST_INTERFACES_H
