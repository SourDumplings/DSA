/*
 @Date    : 2018-05-16 09:57:15
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
列表结点类模板
数据包含在了结点内
 */

#ifndef LIST_NODE_H
#define LIST_NODE_H

namespace CZ
{
    template <typename T> class List;
    template <typename T> class ListIterator;

    template <typename T>
    class ListNode
    {
        friend class List<T>;
        friend class ListIterator<T>;
    public:
        // 构造函数
        ListNode();
        ListNode(const T &data_, ListNode<T> *prev_ = nullptr, ListNode<T> *next_ = nullptr);

        // 数据访问接口
        T& data();
        ListNode<T>* next() const;
        ListNode<T>* prev() const;
        const T& data() const;

        // 动态操作接口
        // 注意只会影响新插入的结点，改变新插入的那个结点的相应的指针
        ListNode<T>* insert_as_prev(const T &newData);
        ListNode<T>* insert_as_prev(T &&newData);
        ListNode<T>* insert_as_prev(ListNode<T> *newNode);
        ListNode<T>* insert_as_next(const T &newData);
        ListNode<T>* insert_as_next(T &&newData);
        ListNode<T>* insert_as_next(ListNode<T> *newNode);
    private:
        T _data;
        ListNode<T> *_prev = nullptr, *_next = nullptr;
    };
} // CZ



#include "ListNode_implementation.h"

#endif // LIST_NODE_H


