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
#include <initializer_list>
#include "ListNode.h"
#include "ListIterator.h"

namespace CZ
{
    template <typename T>
    class List
    {
    public:
        using Rank = unsigned;
        using iterator = ListIterator<T>;

		// 构造函数
        List(Rank n = 0, T data = T());
        List(const T *begin, Rank n);
        List(iterator begin, Rank n);
        List(const T *begin, const T *end);
        List(iterator begin, iterator end);
        List(const std::initializer_list<T> &L);

        // 复制构造函数
        List(const List &l);

        // 移动构造函数
        List(List &&l);

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

        // 打印列表信息
        void printInfo(const char *name = "");

		// 动态操作接口
        void push_back(const T &data);
        void push_back(T &&data);
        void push_front(const T &data);
        void push_front(T &&data);
        void pop_back();
        void pop_front();
        iterator insert(iterator pos, const T &data);
        iterator insert(iterator pos, T &&data);
        iterator erase(iterator pos);
        void clear();
        void merge(const List &l);
        void merge(List &&l);
        void unify();
        // 排序函数模板
        template <typename Cmp>
        void sort(const Cmp &cmp = std::less<const T&>());

        // 操作符函数
        List& operator=(const List &l);
        List& operator=(List &&l);

    protected:
        void free();
        void init();
        void init_from(const T *begin, const T *end);
        void init_from(iterator begin, iterator end);

    private:
        Rank _size = 0;
        ListNode<T> *_head = nullptr, *_tail = nullptr; // 首尾哨兵结点
    };
} // CZ

#include "List_implementation.h"
#include "List_operations.h"

#endif // LIST_H


