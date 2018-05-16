/*
 @Date    : 2018-05-16 09:57:15
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
列表结点类模板
 */

#ifndef LIST_NODE_H
#define LIST_NODE_H

namespace CZ
{
    template <typename T>
    class ListNode
    {
    public:
        // 构造函数
        ListNode();
        ListNode(const T &data_, ListNode<T> *prev_ = nullptr, ListNode<T> *next_ = nullptr);
        ListNode(T &&data_, ListNode<T> *prev_ = nullptr, ListNode<T> *next_ = nullptr);

        // 数据访问接口
        ListNode<T>*& next();
        ListNode<T>*& prev();
        T& data();
        ListNode<T>*& next() const;
        ListNode<T>*& prev() const;
        const T& data() const;

        // 动态操作接口
        ListNode<T>* insert_as_prev(const T &newData);
        ListNode<T>* insert_as_next(const T &newData);
    private:
        T _data;
        ListNode<T> *_prev = nullptr, *_next = nullptr;
    };
} // CZ



#include "ListNode_implementation.h"

#endif // LIST_NODE_H


