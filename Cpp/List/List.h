/*
 @Date    : 2018-05-17 11:34:31
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
双向列表模板类，
支持首尾增删改查O(1)
支持双向迭代器
 */

#ifndef LIST_H
#define LIST_H

#include <functional>
#include "ListNode.h"
#include "List_iterator.h"

namespace CZ
{
    template <typename T>
    class List
    {
    public:
        using Rank = unsigned;
        using iterator = List_iterator<T>;

		// 构造函数
        List();

		// 析构函数
        ~List();

		// 数据访问接口
		Rank size();
		Rank size() const;
		bool empty();
		bool empty() const;
        iterator begin();
        iterator begin() const;
        iterator end();
        iterator end() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        T& head();
        const T& head() const;
        T& tail();
        const T& tail() const;

		// 动态操作接口
        void push_back(const T &data);
        void push_back(T &&data);
        void push_front(const T &data);
        void push_front(T &&data);
        void pop_back();
        void pop_front();
        void clear();

        template <typename Cmp>
        void sort(const Cmp &cmp = std::less<const T&>());

    private:
        Rank _size;
        ListNode<T> *_head = nullptr, *_tail = nullptr; // 首尾哨兵结点
    };
} // CZ

#endif // LIST_H


