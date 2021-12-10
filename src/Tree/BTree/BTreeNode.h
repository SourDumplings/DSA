/*
 @Date    : 2018-07-01 21:45:40
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树结点类模板
 */

#ifndef B_TREE_NODE_H
#define B_TREE_NODE_H

#include "../../Vector/Vector.h"
#include <cstdio>
#include <iostream>

namespace CZ
{
    template <typename T> class BTree;

    template <typename T>
    class BTreeNode
    {
        friend class BTree<T>;
    public:
        using Rank = uint32_t;
        // BTreeNode只能作为根节点创建，初始时有0个关键码和一个空孩子指针
        BTreeNode(): _father(nullptr)
        { _children.push_back(nullptr); }
        BTreeNode(const T &data, BTreeNode<T> *lc = nullptr, BTreeNode<T> *rc = nullptr):
            _father(nullptr)
        {
            _keys.push_back(data);
            _children.push_back(lc);
            _children.push_back(rc);
            if (lc) lc->_father = this;
            if (rc) rc->_father = this;
        }
        ~BTreeNode() = default;

        void print_info(const char *name = "") const
        {
            printf("for btreenode %s: \n", name);
            printf("it contains keys:");
            for (auto &item : _keys)
            {
                std::cout << " " << item;
            }
            printf("\nit has %u children\n\n", _children.size());
            return;
        }
    private:
        Vector<T> _keys; // 存放关键码的列表，长度总比孩子数少1
        // 若B树的阶数为m，每个结点的分支数在区间[上取整(m/2)，m]上，相应的关键码数在[上取整(m/2)-1，m-1]上
        Vector<BTreeNode<T>*> _children; // 孩子向量，其长度总比关键码数多1
        BTreeNode<T> *_father;

        BTreeNode<T>* get_root() const
        {
            BTreeNode<T> *r = this, *f = _father;
            while (f)
            {
                r = f;
                f = f->_father;
            }
            return r;
        }
    };
} // CZ

#endif // B_TREE_NODE_H


