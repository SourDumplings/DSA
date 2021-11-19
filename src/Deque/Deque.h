/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 14:03:24
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 双向队列模板类
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

namespace CZ
{
    template <typename T>
    class Deque
    {
    public:
        using Rank = uint32_t;
        using Iterator = DequeIterator<T>;
        using Node = T*;

        // 构造函数
        // 构造函数 1：容量为 c，规模为 s，所有元素初始为 v，缓冲区大小为 bufferSize_
        Deque(Rank s = 0, T v = T(), Rank bufferSize_ = 10);
        // 构造函数 2：迭代器区间的构造
        Deque(const Iterator &begin, const Iterator &end, Rank bufferSize_ = 10);
        Deque(const T *begin, const T *end, Rank bufferSize_ = 10);
        // 构造函数 3：初始化列表构造
        Deque(const std::initializer_list<T> &initL, Rank bufferSize_ = 10);

        // 复制构造函数
        Deque(const Deque<T> &dq);

        // 析构函数
        virtual ~Deque();

        // 打印所有元素，空格隔开，末尾换行，及容量和规模
        virtual void print_info(const char *name = "") const;

        // 数据访问接口
        Iterator begin();
        Iterator begin() const;
        Iterator end();
        Iterator end() const;
        Rank size() const;
        bool empty() const;

        // 操作符
        Deque<T>& operator=(const Deque<T> &dq);

        // 动态操作接口
        void push_back(const T &x);
        void push_back(T &&x);
        void push_front(const T &x);
        void push_front(T &&x);
    private:
        Rank _bufferSize;
        Rank _mapSize;
        Node* _bufferMap; // 缓冲区 map，默认左右都要有一个空隙
        Rank _size; // 元素个数
        Iterator _start; // 首元素迭代器，其中 cur 指向首元素
        Iterator _finish; // 尾元素迭代器，其中 cur 指向尾元素的后一个元素

        template<typename It>
        void init_from(const It &begin, const It &end, Rank bufferSize_ = 10);
        void expand();

        static const Rank MIN_BUFFER_SIZE = 5;
    };
}

#include "Deque_implementation.h"

#endif
