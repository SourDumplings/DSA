/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 17:26:38
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树结点模板类
 * 
 * 模板参数：K关键码类型，V数据类型
 */

#ifndef B_PLUS_TREE_NODE_H
#define B_PLUS_TREE_NODE_H

#include "../../Vector/Vector.h"
#include <cstdio>
#include <iostream>

namespace CZ
{
template<typename K, typename V>
class BPlusTree;

template<typename K, typename V>
class BPlusTreeNode
{
    friend class BPlusTree<K, V>;

public:
    using Rank = unsigned;

    explicit BPlusTreeNode(const K &key,
                           BPlusTreeNode<K, V> *father_ = nullptr,
                           bool isLeaf_ = false,
                           V *pData = nullptr)
        : _father(father_), _isLeaf(isLeaf_)
    {
        _keys.push_back(key);
        if (_isLeaf)
        {
            _children.push_back(pData);
        }
        else
        {
            _children.push_back(nullptr);
        }
        _children.push_back(nullptr);
    }
    explicit BPlusTreeNode(BPlusTreeNode<K, V> *father_ = nullptr,
                           bool isLeaf_ = false)
        : _father(father_), _isLeaf(isLeaf_)
    {
    }

    ~BPlusTreeNode() = default;

    void print_info(const char *name = "") const
    {
        printf("for %s bPlusTreeNode %s: \n", _isLeaf ? "leaf" : "inner", name);

        printf("it contains %d keys:", _keys.size());
        for (const K &k : _keys)
        {
            std::cout << " " << k;
        }
        printf("\n\n");
    }

private:
    Vector<K> _keys; // 存放关键码的列表，长度总比孩子数少1
    // 若B树的阶数为m，每个结点的分支数在区间[上取整(m/2)，m]上，相应的关键码数在[上取整(m/2)-1，m-1]上

    // 孩子向量，其长度总比关键码数多1
    // 在叶结点中，该向量指向数据，只有最后一个元素指向下一个叶结点
    // 非叶结点（内部结点）中，该向量的元素指向子结点
    Vector<void *> _children;

    BPlusTreeNode<K, V> *_father;
    bool _isLeaf;

    BPlusTreeNode<K, V> *get_root() const
    {
        BPlusTreeNode<K, V> *r = this, *f = _father;
        while (f)
        {
            r = f;
            f = f->_father;
        }
        return r;
    }
};
} // namespace CZ

#endif // B_PLUS_TREE_NODE_H
