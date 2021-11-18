/*
 @Date    : 2018-08-21 11:24:06
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树状数组模板
对于问题：
    操作A：将位置x的元素加上k
    操作B：求出位置[B, E)之内的元素和(共n个元素)
将两个操作反复执行多次，操作A执行Ma次，操作B执行Mb次
如果是普通数组则需要O(Ma + Mb * n)
树状数组能够在O((Ma + Mb) * logn)时间完成，即虽然牺牲了操作A但是操作B的效率大大提升
逻辑上，树状数组管理着一个存储数据的数组，称为原数组
原数组的秩从0开始，树状数组的数据从秩1开始
 */

#ifndef BINARY_INDEX_TREE_H
#define BINARY_INDEX_TREE_H

#include "../Vector/Vector.h"

namespace CZ
{
    template <typename T>
    class BinaryIndexTree
    {
    public:
        using Rank = uint64_t;

        BinaryIndexTree(const Rank size = 0); // 传入管理多少个元素，实际树状数组中多一个元素

        bool empty() const;
        Rank size() const;
        T sum(Rank l) const; // 返回原数组前l项的和
        T sum(Rank b, Rank e) const; // 返回原数组[b, e)的和
        T operator[](Rank pos) const;

        void print_info(const char *name = "") const;

        void resize(const Rank size);
        // 将原数组的pos位加x
        void add(const Rank pos, const T &x);
    private:
        Vector<T> _data;
        // 返回x的二进制形式中，从右起第一位的1保留，其余位全为0所对应的数
        Rank _low_bit(const Rank x) const;
    };
} // CZ

#include "BinaryIndexTree_implementation.h"

#endif // BINARY_INDEX_TREE_H
