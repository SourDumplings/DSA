/**
 * @projectName DSA
 * @author SourDumplings
 * @version 1.0.0
 * @date 2021/2/24 23:07
 */

/*
 * 线段树是一种非常灵活的数据结构，它可以用于解决多种范围查询问题，
 * 比如在对数时间内从数组中找到最小值、最大值、总和、最大公约数、最小公倍数等满足交换律的二元运算，空间复杂度 O(n)
 * 满足交换律是指，交换谁前谁后，二元运算结果一样
 * 其基本思想是父节点维持左右子节点对应的二元运算结果，即 Val(node) = F（Val(node.left), Val(node.right)）
 * 在实现上可以用二叉树实现, 但最好用数组（列表）实现，效率更高
 *
 * 例如对于维持和的线段树，原数组 [2, 4, 5, 7, 8, 9]，线段树如下所示，括号中为存储列表的索引：
 *                           35(1)
 *                    /              \
 *                  29(2)            6(3)
 *               /        \         /     \
 *             12(4)      17(5)   2(6)    4(7)
 *            /    \     /     \
 *           5(8) 7(9)  8(10)  9(11)
 * 可以发现，原数组索引加上原数组大小即可得到该元素在存储列表中的叶结点索引
 *
 * */

#ifndef DSA_SEGMEMTTREE_H
#define DSA_SEGMEMTTREE_H

#include "../../Vector/Vector.h"

#include <functional>

namespace CZ
{
    enum SegmentTreeImplementation
    {
        ARRAY_IMPL,
        TREE_IMPL
    };

    template <typename T, typename F = std::plus<T>>
    class SegmentTree : public AbstractBaseContainer<T>
    {
    public:
        using Rank = typename AbstractBaseContainer<T>::Rank;

        // 构造函数
        SegmentTree(const Vector<T> data, // 需要存储的值列表，即原列表
                    const F &f = F());    // 需要维护的结果所需的二元运算器对象，默认为相加函数)
        // 更新原列表索引为 index 处的值为 val
        // 计算复杂度 O(log(_n))
        void update(Rank index, const T &val);
        // 得到原数组 [lo, hi] 范围运算结果
        // 需要传入起始值，用于累计运算
        // 例如对于加和来说，起始值为 0，对于乘积和最小公倍数来说，起始值为 1
        // 计算复杂度为对数量级 O(log(_n))
        T range_res(Rank lo, Rank hi, T start_val);

        Rank size() const override;
        void clear() override;
        const char *c_str() const override;
        HashRank hash() const override;

        const char *get_entity_name() const override;

    private:
        Rank _n;              // 管理的原列表总数据数
        Vector<T> _tree_data; // 如果是列表实现，存储列表，有效下标索引从 1 开始，原列表下标
        const F &_f;          // 二元处理函数
    };
}

#include "SegmentTree_implementation.h"

#endif // DSA_SEGMEMTTREE_H
