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
        // 构造函数
        ListIterator(ListNode<T> *node_): _node(node_) {}

        // 操作符
        T& operator*()
        { return _node->data(); }
        const T& operator*() const
        { return _node->data(); }
        ListIterator<T>& operator++()
        {
            _node = _node->next();
            return *this;
        }
        ListIterator<T> operator++(int)
        {
            ListIterator<T> temp = *this;
            _node = _node->next();
            return temp;
        }
        ListIterator<T>& operator--()
        {
            _node = _node->prev();
            return *this;
        }
        ListIterator<T> operator--(int)
        {
            ListIterator<T> temp = *this;
            _node = _node->prev();
            return temp;
        }

        ListNode<T>* get() { return _node; }
        ListNode<T>* get() const { return _node; }
    private:
        ListNode<T> *_node;
    };

    template <typename T>
    bool operator==(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
    {
        return lhs._node == rhs._node;
    }
    template <typename T>
    bool operator!=(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }


} // CZ

#endif // LISTITERATOR_H


