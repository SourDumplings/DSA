/*
 @Date    : 2018-05-17 19:15:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的动态操作
 */

#ifndef LIST_MODIFICATIONS_H
#define LIST_MODIFICATIONS_H

#include "List.h"
#include <stdexcept>
#include <utility>
#include "..\Algorithms\Swap.h"

namespace CZ
{
    template <typename T>
    void List<T>::clear()
    {
        for (ListNode<T> *node = _head->_next; node != _head;)
        {
            ListNode<T> *temp = node;
            node->_next->_prev = nullptr;
            node = node->_next;
            delete temp;
        }
        _size = 0;
        _head->_next = _head->_prev = _head;
        return;
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(typename List<T>::iterator pos, const T &data)
    {
        ListNode<T> *newNode = pos.get()->insert_as_prev(data);
        pos.get()->_prev->_next = newNode;
        pos.get()->_prev = newNode;
        ++_size;
        return ListIterator<T>(newNode);
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(typename List<T>::iterator pos, T &&data)
    {
        ListNode<T> *posGet = pos.get();
        ListNode<T> *newNode = posGet->insert_as_prev(std::move(data));
        posGet->_prev->_next = newNode;
        posGet->_prev = newNode;
        ++_size;
        return ListIterator<T>(newNode);
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(typename List<T>::iterator pos,
        typename List<T>::iterator b, typename List<T>::iterator e)
    {
        ListNode<T> *posGet = pos.get();
        ListNode<T> *hNode = posGet->_prev;
        while (b != e)
        {
            ListNode<T> *newNode = posGet->insert_as_prev(*b++);
            posGet->_prev->_next = newNode;
            posGet->_prev = newNode;
            ++_size;
        }
        return ListIterator<T>(hNode->_next);
    }

    template <typename T>
    typename List<T>::iterator List<T>::erase(typename List<T>::iterator pos)
    {
        try
        {
            ListNode<T> *posGet = pos.get();
            if (posGet == _head)
            {
                throw "head can not be erased!";
            }
            posGet->_next->_prev = posGet->_prev;
            posGet->_prev->_next = posGet->_next;
            posGet = posGet->_next;
            delete pos.get();
            --_size;
            return ListIterator<T>(posGet);
        }
        catch (const char *errMsg)
        {
            printf("Error from List erase: %s\n", errMsg);
            throw std::exception();
        }
        return pos;
    }

    template <typename T>
    typename List<T>::iterator List<T>::erase(typename List<T>::iterator b,
        typename List<T>::iterator e)
    {
        try
        {
            while (b != e)
            {
                ListNode<T> *posGet = b++.get();
                if (posGet == _head)
                {
                    throw "head can not be erased!";
                }
                posGet->_next->_prev = posGet->_prev;
                posGet->_prev->_next = posGet->_next;
                delete posGet;
                --_size;
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from List erase: %s\n", errMsg);
            throw std::exception();
        }
        return e;
    }

    template <typename T>
    inline void List<T>::push_back(const T &data)
    {
        insert(end(), data);
        return;
    }

    template <typename T>
    inline void List<T>::push_back(T &&data)
    {
        insert(end(), std::move(data));
        return;
    }

    template <typename T>
    inline void List<T>::push_front(const T &data)
    {
        insert(_head->_next, data);
        return;
    }

    template <typename T>
    inline void List<T>::push_front(T &&data)
    {
        insert(_head->_next, std::move(data));
        return;
    }

    template <typename T>
    inline void List<T>::pop_front()
    {
        erase(_head->_next);
        return;
    }

    template <typename T>
    inline void List<T>::pop_back()
    {
        erase(_head->_prev);
        return;
    }

    template <typename T>
    void List<T>::remove(const T &value)
    {
        for (auto it = begin(); it != end();)
        {
            if (*it == value)
            {
                it = erase(it);
            }
            else
                ++it;
        }
        return;
    }
} // CZ

#endif // LIST_MODIFICATIONS_H

