/*
 @Date    : 2018-04-06 17:29:33
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
向量类模板
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

namespace CZ
{
    using Rank = unsigned;
    const unsigned DEFAULT_CAPACITY = 0; // 默认初始容量

    template <typename T>
    class Vector
    {
    protected:
        Rank _size; // 规模
        unsigned _capacity = DEFAULT_CAPACITY; // 容量
        T* _elem; // 数据区

        //迭代器区间的复制
        void copyFrom(const T *begin, const T *end);
    public:
        // 构造函数
        // 构造函数1.容量为c，规模为s，所有元素初始为v
        Vector(unsigned s = DEFAULT_CAPACITY, T v = T());
        // 构造函数2.迭代器与元素个数构造
        Vector(const T *begin, Rank n);
        // 构造函数3.迭代器区间构造
        Vector(const T *begin, const T *end);
        // 构造函数4.不定参数个数的构造函数
        Vector(const std::initializer_list<T> &initL);

        // 复制构造函数
        Vector(const Vector<T> &V);


        // 析构函数
        ~Vector();

        // 打印所有元素，空格隔开，末尾换行，及容量和规模
        void printInfo(const char *name = "");

    };
}

// 引入模板类的所有方法的实现
#include "Vector_implementation.h"

#endif



