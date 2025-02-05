/*
 @Date    : 2018-07-30 22:08:39
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
堆，元素可重复
采用向量实现，可以定制比较器，默认为大顶堆
堆顶元素为_data[0]，对于_data[i]，由于完全二叉树的性质，其孩子结点为_data[i*2+1]和_data[i*2+2]
同理，对于结点_data[i]，其父结点为_data[(i-1)/2]
 */

#ifndef HEAP_H
#define HEAP_H

#include "../Base/AbstractBaseContainer.h"
#include "../Vector/Vector.h"
#include <initializer_list>

namespace DSA
{
    template <typename T, typename Cmp = std::less<const T &>>
    class Heap : public AbstractBaseContainer<T>
    {
    public:
        using Rank = typename AbstractBaseContainer<T>::Rank;

        Heap();
        Heap(const std::initializer_list<T> &l, const Cmp &cmp = Cmp());
        Heap(T *begin, T *end, const Cmp &cmp = Cmp());
        template <typename It>
        Heap(const It &begin, const It &end, const Cmp &cmp = Cmp());

        // 数据访问接口
        Rank size() const override;
        const T &top() const;

        // 插入和删除
        void insert(const T &value, const Cmp &cmp = Cmp());
        void pop(const Cmp &cmp = Cmp());
        void clear() override;

        void print_info(const char *name = "") const;

        HashRank hash() const override;
        const char *c_str() const override;

        const char *get_entity_name() const override;

    private:
        Vector<T> _data;

        void _build_heap(const Cmp &cmp = Cmp());        // 采用Floyd算法进行建堆，使得_data中的元素满足偏序化，时间复杂度O(n)
        void _perc_down(Rank i, const Cmp &cmp = Cmp()); // 下滤，即将_data[i]为根的子堆调整为最大堆
        void _perc_up(Rank i, const Cmp &cmp = Cmp());   // 将_data[i]元素进行上滤
    };
} // DSA

#include "Heap_implementation.h"

#endif // HEAP_H
