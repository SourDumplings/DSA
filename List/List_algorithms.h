/*
 @Date    : 2018-09-22 23:58:17
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List的一些特有算法
 */

#ifndef LIST_ALGORITHMS_H
#define LIST_ALGORITHMS_H

#include "List.h"
#include <stdexcept>

namespace CZ
{
    template <typename T>
    inline void List<T>::merge(const List<T> &l)
    {
        insert(end(), l.begin(), l.end());
        return;
    }

    template <typename T>
    void List<T>::merge(List<T> &&l)
    {
        _head->_prev->_next = l._head->_next;
        l._head->_next->_prev = _head->_prev;
        l._head->_next = l._head;

        _head->_prev = l._head->_prev;
        l._head->_prev->_next = _head;
        l._head->_prev = l._head;

        _size += l._size;
        l._size = 0;
        return;
    }

    template <typename T>
    inline void List<T>::swap(iterator pos1, iterator pos2)
    {
        Swap(*pos1, *pos2);
        return;
    }

    template <typename T>
    template <typename Cmp>
    void List<T>::sort(const Cmp &cmp, const unsigned version)
    {
        if (empty())
        {
            return;
        }
        switch (version)
        {
            case 0:
            {
                // 冒泡排序，对元素值进行操作
                bool isSorted = false;
                unsigned unSortedNum = _size, checkedNum;
                while (!isSorted)
                {
                    isSorted = true;
                    checkedNum = 0;
                    for (iterator it = begin(); checkedNum != unSortedNum - 1 && it != end();
                        ++checkedNum)
                    {
                        T &thisData = *it;
                        T &nextData = *++it;
                        if (cmp(nextData, thisData))
                        {
                            Swap(thisData, nextData);
                            isSorted = false;
                        }
                    }
                    --unSortedNum;
                }
            }
            case 1:
            {
                // 插入排序，对结点指针进行操作
                // 先将除了头结点外的结点摘出，然后一个一个进行插入排序
                ListNode<T> *first = _head->_next;
                _head->_prev->_next = nullptr;
                first->_prev = nullptr;
                _head->_next = _head->_prev = _head;

                ListNode<T> *tempNext = nullptr;
                for (ListNode<T> *p = first; p; p = tempNext)
                {
                    ListNode<T> *f = _head;
                    while (f->_next != _head && !cmp(p->_data, f->_next->_data))
                        f = f->_next;
                    tempNext = p->_next;
                    f->insert_as_next(p);
                    p->_next->_prev = f->_next = p;
                }
                return;
            }
        }
        return;
    }

    template <typename T>
    template <typename Cmp>
    void List<T>::unique(bool sorted, const Cmp &cmp)
    {
        if (empty())
        {
            return;
        }
        if (sorted)
        {
            for (iterator firstRepeat = begin(); firstRepeat != end();)
            {
                iterator lastRepeat = firstRepeat;
                for (; cmp(*lastRepeat, *firstRepeat) && lastRepeat != end(); ++lastRepeat);
                firstRepeat = erase(++iterator(firstRepeat), lastRepeat);
            }
        }
        else
        {
            for (ListNode<T> *last = _head->_next; last != _head; last = last->_next)
            {
                for (ListNode<T> *p = last->_next; p != _head; p = p->_next)
                {
                    if (cmp(p->data(), last->data()))
                    {
                        erase(p);
                    }
                }
            }
        }
        return;
    }

    template <typename T>
    void List<T>::reverse()
    {
        if (!empty())
        {
            // 将除了头结点外的其它结点摘出，
            // 再用头插法把结点一个一个插进去
            ListNode<T> *first = _head->_next, *tempNext = _head->_next->_next;
            first->_prev = nullptr;
            _head->_prev->_next = nullptr;
            _head->_next = _head->_prev = _head;

            for (ListNode<T> *p = first; p; p = tempNext)
            {
                tempNext = p->_next;
                _head->insert_as_next(p);
                _head->_next->_prev = p;
                _head->_next = p;
            }
            _head->_prev = first;
        }
        return;
    }
} // CZ

#endif // LIST_ALGORITHMS_H


