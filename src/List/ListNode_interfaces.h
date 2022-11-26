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

#include "../CZString/CZString.h"
#include <iostream>

namespace CZ
{
    template <typename T>
    inline ListNode<T> *ListNode<T>::next() const { return _next; }

    template <typename T>
    inline ListNode<T> *ListNode<T>::prev() const { return _prev; }

    template <typename T>
    inline T &ListNode<T>::data() { return _data; }
    template <typename T>
    inline const T &ListNode<T>::data() const { return _data; }

    template <typename T>
    const char *ListNode<T>::get_entity_name() const
    {
        return "ListNode";
    }

    template <typename T>
    const char *ListNode<T>::c_str() const
    {
        std::ostringstream oss;
        oss << this->get_entity_name() << "(" << data() << ")";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T>
    HashRank ListNode<T>::hash() const
    {
        return (Hash<CZString>()(get_entity_name()) + Hash<T>()(data()) + Hash<ListNode<T> *>()(_prev)
            + Hash<ListNode<T> *>()(_next)) % CZ_MAX_HASH_VALUE;
    }
} // CZ

#endif // LIST_NODE_INTERFACES_H
