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
#include <iostream>

namespace CZ
{
    template <typename T>
    inline ListNode<T>* ListNode<T>::next() const { return _next; }

    template <typename T>
    inline ListNode<T>* ListNode<T>::prev() const { return _prev; }

    template <typename T>
    inline T& ListNode<T>::data() { return _data; }
    template <typename T>
    inline const T& ListNode<T>::data() const { return _data; }

    template <typename T>
    std::ostream& operator<<(std::ostream &os, const ListNode<T> &lN)
    { return os << lN.data(); }
} // CZ

#endif // LIST_NODE_INTERFACES_H


