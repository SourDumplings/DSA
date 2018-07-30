/*
 @Date    : 2018-07-30 22:08:39
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
堆
采用二叉树实现，可以定制比较器，默认为大顶堆
 */

#ifndef HEAP_H
#define HEAP_H

#include <utility>
#include "../Tree/BinTree/BinTree.h"
#include "../Iterator/SeqIterator.h"
#include <initializer_list>

namespace CZ
{
    using std::less;

    template <typename T, typename Cmp = less<const T&>>
    class Heap
    {
    public:
        using Rank = unsigned;
        Heap(const Rank size_ = 0);
        Heap(SeqIterator<T> begin, SeqIterator<T> end);
        Heap(T *begin, T *end);
        Heap(const std::initializer_list<T> &l);

        ~Heap();

        // 数据访问接口
        Rank size() const;
        const T& top() const;

        // 插入和删除，可以设置失败时抛出异常还是返回false
        bool insert(const T &value, const bool nonexcept = true, const bool repeatable = true);
        bool remove(const T &value, const bool nonexcept = true);

        void print_info(const char *name = "") const;
    private:
        Rank _size;
        BinTree<T> _tree;
    };
} // CZ

#endif // HEAP_H

