/*
 @Date    : 2018-05-17 11:34:31
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
双向列表模板类，
支持首尾增删改查O(1)，采用循环双链表实现
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
        using Rank = uint64_t;
        using RankPlus = int64_t;
        using Iterator = ListIterator<T>;

		// 构造函数
        List(Rank n = 0, T data = T());
        List(const T *begin, const T *end);
        List(Iterator begin, Iterator end);
        List(const std::initializer_list<T> &L);

        // 复制构造函数
        List(const List &l);

        // 移动构造函数
        List(List &&l);

		// 析构函数
        virtual ~List();

		// 数据访问接口
		Rank size() const;
		bool empty() const;
        Iterator begin();
        Iterator begin() const;
        Iterator end();
        Iterator end() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        T& at(RankPlus index);
        const T& at(RankPlus index) const;

        // 打印列表信息
        void print_info(const char *name = "") const;

		// 动态操作接口
        virtual void push_back(const T &data);
        virtual void push_back(T &&data);
        virtual void push_front(const T &data);
        virtual void push_front(T &&data);
        virtual void pop_back();
        virtual void pop_front();
        Iterator insert(Iterator pos, const T &data);
        Iterator insert(Iterator pos, T &&data);
        Iterator insert(Iterator pos, Iterator b, Iterator e);
        Iterator erase(Iterator pos);
        Iterator erase(Iterator b, Iterator e);
        void remove(const T &value); // 删除所有value值
        void clear();
        virtual void merge(const List<T> &l);
        virtual void merge(List<T> &&l);
        // 交换函数模板
        void swap(Iterator pos1, Iterator pos2);
        // 列表元素的排序算法，version 0为冒泡排序，对元素值进行操作，适用于元素值体积小的情况
        // version 1为插入排序，对链表结点进行操作，适用于元素体积较大的情况
        template <typename Cmp = std::less<const T&>>
        void sort(const Cmp &cmp = std::less<const T&>(), const unsigned version = 0);
        // 有序列表去重，可根据列表是否已经排好序选择不同的算法
        // 对于排好序的列表，算法时间复杂度为O(n)，否则为O(n^2)
        template <typename Cmp = std::equal_to<const T&>>
        void unique(bool sorted = false, const Cmp &cmp = std::equal_to<const T&>());
        // 列表元素逆置
        virtual void reverse();
        // 剪切函数，可以把另一个列表剪切到前一个列表的指定位置的前面，即为时间复杂度为O(1)的插入操作
        // 返回插入元素后插入的元素中最前面的结点的迭代器
        Iterator splice(Iterator pos, List<T> &l);

        // 操作符函数
        virtual List& operator=(const List &l);
        virtual List& operator=(List &&l);

    protected:
        void free();
        void init();
        void init_from(const T *begin, const T *end);
        void init_from(Iterator begin, Iterator end);

    private:
        Rank _size = 0;
        ListNode<T> *_head = nullptr; // 头哨兵结点
    };
} // CZ

#include "List_implementation.h"
#include "List_operations.h"

#endif // LIST_H


