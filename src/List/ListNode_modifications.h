/*
 @Date    : 2018-05-16 10:16:45
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
列表结点类的动态操作接口
 */

#ifndef LIST_NODE_MODIFICATIONS_H
#define LIST_NODE_MODIFICATIONS_H

#include "ListNode.h"
#include <utility>

namespace DSA
{
    template <typename T>
    inline ListNode<T>* ListNode<T>::insert_as_prev(const T &newData)
    {
        ListNode<T>* newNode = new ListNode(newData, _prev, this);
        return newNode;
    }

    template <typename T>
    inline ListNode<T>* ListNode<T>::insert_as_prev(T &&newData)
    {
        ListNode<T>* newNode = new ListNode(std::move(newData), _prev, this);
        return newNode;
    }

    template <typename T>
    inline ListNode<T>* ListNode<T>::insert_as_prev(ListNode<T> *newNode)
    {
        newNode->_next = this;
        newNode->_prev = _prev;
        return newNode;
    }

    template <typename T>
    inline ListNode<T>* ListNode<T>::insert_as_next(const T &newData)
    {
        ListNode<T> *newNode = new ListNode(newData, this, _next);
        return newNode;
    }

    template <typename T>
    inline ListNode<T>* ListNode<T>::insert_as_next(T &&newData)
    {
        ListNode<T> *newNode = new ListNode(std::move(newData), this, _next);
        return newNode;
    }

    template <typename T>
    ListNode<T>* ListNode<T>::insert_as_next(ListNode<T> *newNode)
    {
        newNode->_prev = this;
        newNode->_next = _next;
        return newNode;
    }

} // DSA

#endif // LIST_NODE_MODIFICATIONS_H


