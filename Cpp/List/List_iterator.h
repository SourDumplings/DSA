/*
 @Date    : 2018-05-17 12:33:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
双向列表迭代器模板类
 */

#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "ListNode.h"

namespace CZ
{
    template <typename T>
    class List_iterator
    {
    public:
        // 构造函数
        List_iterator(ListNode<T> *node_): _node(node_) {}

        // 操作符
        ListNode<T> &operator*()
        { return *_node; }
        const ListNode<T> &operator*() const
        { return *_node; }
        ListNode<T>* operator++()
        {
            _node = _node->next();
            return _node;
        }
        ListNode<T>* operator++(int)
        {
            ListNode<T> *temp = _node;
            _node = _node->next();
            return temp;
        }
        ListNode<T>* operator--()
        {
            _node = _node->prev();
            return _node;
        }
        ListNode<T>* operator--(int)
        {
            ListNode<T> *temp = _node;
            _node = _node->prev();
            return temp;
        }
    private:
        ListNode<T> *_node;
    };

} // CZ

#endif // LIST_ITERATOR_H


