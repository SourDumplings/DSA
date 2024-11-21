/*
 @Date    : 2018-04-06 17:29:33
 @Author  : 酸饺子 (sourdumplings@qq.com)
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
#include "../Base/Assert.h"
#include "../Base/AbstractSeqIterableContainer.h"
#include "../Iterator/RandomIterator.h"
#include "../Algorithms/Dict_compare.h"

namespace DSA
{
    template <typename T>
    class Vector : public AbstractSeqIterableContainer<T, RandomIterator<T>>
    {
    public:
        using Iterator = RandomIterator<T>;
        using Rank = typename AbstractSeqIterableContainer<T, RandomIterator<T>>::Rank;
        using RankPlus = typename AbstractSeqIterableContainer<T, RandomIterator<T>>::RankPlus;

        // 构造函数
        // 构造函数 1：容量为 c = 2 * s，规模为 s，所有元素初始为默认值
        Vector(Rank s = 0);

        // 构造函数 2：迭代器区间构造
        Vector(const T *begin, const T *end);

        template <typename It>
        Vector(const It &begin, const It &end);

        // 构造函数 3：不定参数个数的构造函数
        Vector(const std::initializer_list<T> &initL);

        // 复制构造函数
        Vector(const Vector<T> &V);
        // 移动构造函数
        Vector(Vector<T> &&V) noexcept;

        // 析构函数
        ~Vector() override;

        // 打印所有元素，空格隔开，末尾换行，及容量和规模
        virtual void print_info(const char *name = "") const;

        // 数据访问接口
        Iterator begin() override;
        Iterator end()  override;
        Iterator begin() const override;
        Iterator end() const override;
        Rank size() const override;
        Rank capacity();
        Rank capacity() const;
        const T& back() const;
        T& back();
        const T& front() const;
        T& front();
        const T& at(RankPlus index) const;
        T& at(RankPlus index);

        // 动态操作
        void clear() override;
        void push_back(const T &x);
        void push_back(T &&x);
        void pop_back();
        Iterator insert(Iterator itPos, const T &x);
        Iterator insert(Iterator itPos, T &&x);
        Iterator insert(Iterator itPos, const T *b, const T *e);
        Iterator insert(Iterator itPos, const Iterator &b, const Iterator &e);
        Iterator erase(Iterator itPos);
        Iterator erase(Iterator itBegin, Iterator itEnd);

        /**
         * @brief 重新调整容器大小，如果是扩容，则扩容后原来的元素都会保序复制到容器的前端，结果上看是往后拓展了空间
         * 如果是缩容，则缩容后原来的元素都会保序尽可能复制到容器的前端，结果上看是从尾部截断了一段
         * 
         * @param [in] n 目标容器大小
         */
        void resize(Rank n);
        
        // 删除所有值为value的元素
        void remove(const T &value);
        void reverse();

        // 操作符函数
        T& operator[](Rank i);
        const T& operator[](Rank i) const;
        Vector<T>& operator=(const Vector<T> &V);
        Vector<T>& operator=(Vector<T> &&V) noexcept;

        const char *get_entity_name() const override;

    protected:
        T *_elem; // 数据区，[0, _size) 元素经过了构造，[_size, _capacity) 元素未经过构造

        //迭代器区间的复制
        template <typename It>
        void _init_from(const It &begin, const It &end);

        // 搬到大房子中，即扩容操作
        // 扩容后原来的元素都会保序复制到容器的前端，结果上看是往后拓展了空间
        bool _expand();

        bool _need_expand() const;
        
        // 装填因子过小时缩容
        // 缩容后原来的元素都会保序尽可能复制到容器的前端，结果上看是从尾部截断了一段
        bool _shrink();

        bool _need_shrink() const;

    private:
        Rank _size; // 规模
        Rank _capacity; // 容量
    };
}

// 引入Vector类模板的所有方法的实现
#include "Vector_implementation.h"

// 引入Vector类模板所本身支持的操作
#include "Vector_operations.h"

#endif

