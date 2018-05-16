/*
 @Date    : 2018-05-16 10:11:47
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
列表结点类模板的数据访问接口
 */

#ifndef LIST_NODE_INTERFACES_H
#define LIST_NODE_INTERFACES_H

#include "ListNode.h"

namespace CZ
{
    template <typename T>
    ListNode<T>*& ListNode<T>::next() { return _next; }
    template <typename T>
    ListNode<T>*& ListNode<T>::next() const { return _next; }

    template <typename T>
    ListNode<T>*& ListNode<T>::prev() { return _prev; }
    template <typename T>
    ListNode<T>*& ListNode<T>::prev() const { return _prev; }

    template <typename T>
    T& ListNode<T>::data() { return _data; }
    template <typename T>
    const T& ListNode<T>::data() const { return _data; }
} // CZ

#endif // LIST_NODE_INTERFACES_H


