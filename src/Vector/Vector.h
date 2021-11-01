/*
 @Date    : 2018-04-06 17:29:33
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
向量类模板
迭代器为随机访问迭代器
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include "../Iterator/RandomIterator.h"
#include "../Algorithms/Dict_compare.h"

namespace CZ
{
    template <typename T>
    class Vector
    {
    public:
        using Rank = unsigned;
        using RankPlus = int;
        using Iterator = RandomIterator<T>;

        // 构造函数
        // 构造函数1.容量为 c = 2 * s，规模为 s，所有元素初始为 v
        Vector(Rank s = 0, T v = T());
        // 构造函数2.迭代器与元素个数构造
        Vector(const Iterator &begin, Rank n);
        Vector(const T *begin, Rank n);
        // 构造函数3.迭代器区间构造
        Vector(const Iterator &begin, const Iterator &end);
        Vector(const T *begin, const T *end);
        // 构造函数4.不定参数个数的构造函数
        Vector(const std::initializer_list<T> &initL);

        // 复制构造函数
        Vector(const Vector<T> &V);
        // 移动构造函数
        Vector(Vector<T> &&V);

        // 析构函数
        virtual ~Vector();

        // 打印所有元素，空格隔开，末尾换行，及容量和规模
        virtual void print_info(const char *name = "") const;

        // 数据访问接口
        Iterator begin();
        Iterator end();
        Iterator begin() const;
        Iterator end() const;
        Rank size() const;
        Rank capacity();
        Rank capacity() const;
        const T& back() const;
        T& back();
        const T& front() const;
        T& front();
        bool empty();
        bool empty() const;
        const T& at(RankPlus index) const;
        T& at(RankPlus index);

        // 动态操作
        virtual void clear();
        void push_back(const T &x);
        void push_back(T &&x);
        void pop_back();
        Iterator insert(Iterator itPos, const T &x);
        Iterator insert(Iterator itPos, T &&x);
        Iterator insert(Iterator itPos, const T *b, const T *e);
        Iterator insert(Iterator itPos, const Iterator &b, const Iterator &e);
        Iterator erase(Iterator itPos);
        Iterator erase(Iterator itBegin, Iterator itEnd);
        void resize(Rank n);
        // 区间赋值
        void assign(const Iterator &begin, const Iterator &end);
        // 删除所有值为value的元素
        void remove(const T &value);

        // 操作符函数
        T& operator[](Rank i);
        const T& operator[](Rank i) const;
        Vector<T>& operator=(const Vector<T> &V);
        Vector<T>& operator=(Vector<T> &&V);
    protected:
        //迭代器区间的复制
        void init_from(const Iterator &begin, const Iterator &end);
        void init_from(const T *begin, const T *end);
        // 析构辅助方法
        void free();
        // 搬到大房子中，即扩容操作
        bool expand();
        // 装填因子过小时缩容
        bool shrink();

    private:
        Rank _size; // 规模
        Rank _capacity; // 容量
        T *_elem; // 数据区
    };
}

// 引入Vector类模板的所有方法的实现
#include "Vector_implementation.h"

// 引入Vector类模板所本身支持的操作
#include "Vector_operations.h"

#endif

