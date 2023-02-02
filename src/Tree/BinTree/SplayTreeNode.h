/*
 @Date    : 2018-06-20 20:14:53
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
伸展树结点模板，完全继承了二叉搜索树结点类
 */

#ifndef SPLAY_TREE_NODE_H
#define SPLAY_TREE_NODE_H

#include "BSTNode.h"

namespace CZ
{
    template <typename T>
    class SplayTreeNode : public BSTNode<T>
    {
    public:
        using Rank = typename BSTNode<T>::Rank;

        // 构造函数不能传入子女，只能传入数据和父结点
        SplayTreeNode(const T &data = T(), SplayTreeNode *father_ = nullptr) : BSTNode<T>(data, father_) {}

        const char *get_entity_name() const override
        {
            return "SplayTreeNode";
        }

        bool insert_child_by_data(const T &data) override
        {
            SplayTreeNode<T> *pNode = new SplayTreeNode<T>(data);
            TreeNode<T> *pRes = this->insert_child(pNode);
            if (pNode && pRes == nullptr)
            {
                delete pNode;
                return false;
            }
            return true;
        }
    };
} // CZ

#endif // SPLAY_TREE_NODE_H
