/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 14:03:24
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 双向队列类模板
 */

/*
以多个相同大小的数组作为缓冲区存储元素
使用指针数组作为缓冲区的 map
可以实现近常数时间复杂度的双向扩容
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <initializer_list>
#include "DequeIterator.h"
#include "../Base/AbstractSeqIterableContainer.h"
#include "../CZString/CZString.h"

namespace CZ
{
    template <typename T>
    class Deque : public AbstractSeqIterableContainer<T, DequeIterator<T>>
    {
    public:
        using Rank = typename AbstractSeqIterableContainer<T, DequeIterator<T>>::Rank;
        using RankPlus = typename AbstractSeqIterableContainer<T, DequeIterator<T>>::RankPlus;
        using Iterator = DequeIterator<T>;
        using Node = T *;

        static constexpr Rank DEFAULT_BUFFER_SIZE = 10;

        // 构造函数
        // 构造函数 1：容量为 c，规模为 s，所有元素初始为 v，缓冲区大小为 bufferSize_
        Deque(Rank s = 0);

        // 构造函数 2：迭代器区间的构造
        template <typename It>
        Deque(const It &begin, const It &end, Rank bufferSize_ = DEFAULT_BUFFER_SIZE);

        Deque(const T *begin, const T *end, Rank bufferSize_ = DEFAULT_BUFFER_SIZE);

        // 构造函数 3：初始化列表构造
        Deque(const std::initializer_list<T> &initL, Rank bufferSize_ = DEFAULT_BUFFER_SIZE);

        // 复制构造函数
        Deque(const Deque<T> &dq);

        // 析构函数
        virtual ~Deque();

        // 打印所有元素，空格隔开，末尾换行，及容量和规模
        virtual void print_info(const char *name = "") const;

        // 数据访问接口
        Iterator begin() override;
        Iterator begin() const override;
        Iterator end() override;
        Iterator end() const override;
        Rank size() const override;
        const T &back() const;
        T &back();
        const T &front() const;
        T &front();
        const T &at(RankPlus index) const;
        T &at(RankPlus index);

        // 操作符
        Deque<T> &operator=(const Deque<T> &dq);
        Deque<T> &operator=(Deque<T> &&dq);
        const T &operator[](Rank index) const;
        T &operator[](Rank index);

        // 动态操作接口
        // 增加元素的接口，必要时会扩容
        void push_back(const T &x);
        void push_back(T &&x);
        void push_front(const T &x);
        void push_front(T &&x);
        Iterator insert(Iterator itPos, const T &x);
        Iterator insert(Iterator itPos, T &&x);
        Iterator insert(Iterator itPos, const T *b, const T *e);
        Iterator insert(Iterator itPos, const Iterator &b, const Iterator &e);
        // 删除元素的接口，必要时会缩容
        void pop_back();
        void pop_front();
        Iterator erase(Iterator itPos);
        Iterator erase(const Iterator &b, const Iterator &e);
        void clear() override;       // 清理 Deque 容器，不会改变 bufferSize
        void remove(const T &value); // 移除所有值为 value 的元素

        const char *get_entity_name() const override;

    private:
        static const Rank MIN_BUFFER_SIZE = 5;

        const Rank _bufferSize;
        Rank _mapSize;
        Node *_bufferMap; // 缓冲区 map，默认左右都要有一个空隙
        Rank _size;       // 元素个数
        Iterator _begin;  // 首元素迭代器，其中 cur 指向首元素
        Iterator _end; // 尾元素迭代器，其中 cur 指向尾元素的后一个元素

        template <typename It>
        void init_from(const It &begin, const It &end);

        void free();

        void _expand();            // 双向伸展，2 倍扩容
        bool _need_shrink() const; // 判断是否需要缩容，如果有元素的 buffer 数小于总 buffer 数（bufferMap 的大小）的一半就返回 true
        void _shrink();            // 双向收缩，2 倍缩容，会判断是否需要缩容

        // 将 startIt 之后的所有元素向后移动 n 位（包括 startIt 所指向的元素），必要时扩容，返回由于后移形成的第一个空位的迭代器
        Iterator move_backward(Iterator startIt, Rank n);
        // 将 startIt 之后的所有元素向前移动 n 位（包括 startIt 所指向的元素），必要时缩容，返回被迁移的第一个元素的迭代器
        // 注意前移不会扩容，即前移不会超过第一个元素的位置
        // 前移元素会覆盖之前的元素
        Iterator move_forward(Iterator startIt, Rank n);
    };
}

#include "Deque_implementation.h"

#endif
