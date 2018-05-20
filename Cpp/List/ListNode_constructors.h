/*
 @Date    : 2018-05-16 10:08:35
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
列表结点类模板的构造函数
 */

#ifndef LIST_NODE_CONSTRUCTORS_H
#define LIST_NODE_CONSTRUCTORS_H

#include "ListNode.h"

namespace CZ
{
    template <typename T>
    inline ListNode<T>::ListNode() = default;

    template <typename T>
    inline ListNode<T>::ListNode(const T &data_, ListNode<T> *prev_, ListNode<T> *next_):
        _data(data_), _prev(prev_), _next(next_) {}
} // CZ

#endif // LIST_NODE_CONSTRUCTORS_H

