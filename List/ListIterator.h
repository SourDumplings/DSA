/*
 @Date    : 2018-05-17 12:33:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
双向列表迭代器模板类
 */

#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include "ListNode.h"
#include "../Iterator/BiIterator.h"

namespace CZ
{
    template <typename T>
    class ListIterator;

    template <typename T>
    bool operator==(const ListIterator<T> &lhs, const ListIterator<T> &rhs);
    template <typename T>
    bool operator!=(const ListIterator<T> &lhs, const ListIterator<T> &rhs);

    template <typename T>
    class ListIterator
    {
        friend bool operator==<T>(const ListIterator<T> &lhs, const ListIterator<T> &rhs);
        friend bool operator!=<T>(const ListIterator<T> &lhs, const ListIterator<T> &rhs);
    public:
        typedef bi_iterator_tag iterator_category;

        // 构造函数
        ListIterator(ListNode<T> *node_ = nullptr): _it(node_) {}

        // 操作符
        T& operator*()
        { return _it->data(); }
        const T& operator*() const
        { return _it->data(); }
        BiIterator<ListNode<T>> operator->()
        { return _it; }
        const BiIterator<ListNode<T>> operator->() const
        { return _it; }

        ListIterator<T>& operator++()
        {
            _it = BiIterator<ListNode<T>>(_it->next());
            return *this;
        }
        ListIterator<T> operator++(int)
        {
            ListIterator<T> temp = *this;
            _it = BiIterator<ListNode<T>>(_it->next());
            return temp;
        }
        ListIterator<T>& operator--()
        {
            _it = BiIterator<ListNode<T>>(_it->prev());
            return *this;
        }
        ListIterator<T> operator--(int)
        {
            ListIterator<T> temp = *this;
            _it = BiIterator<ListNode<T>>(_it->prev());
            return temp;
        }

        ListNode<T>* get() { return _it.get(); }
        ListNode<T>* get() const { return _it.get(); }

        operator const BiIterator<ListNode<T>>() const
        { return _it; }

        operator BiIterator<ListNode<T>>() { return _it; }

    private:
        BiIterator<ListNode<T>> _it;
    };

    template <typename T>
    bool operator==(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
    {
        return lhs._it == rhs._it;
    }
    template <typename T>
    bool operator!=(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }


} // CZ

#endif // LISTITERATOR_H


