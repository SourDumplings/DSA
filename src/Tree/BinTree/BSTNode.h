/*
 @Date    : 2018-06-13 19:05:36
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉搜索树结点类模板
 */

#ifndef BST_NODE_H
#define BST_NODE_H

#include "BinTreeNode.h"

namespace CZ
{
    template <typename T>
    class BST;

    template <typename T>
    class BSTNode : public BinTreeNode<T>
    {
        friend class BST<T>;

    public:
        using Rank = typename BinTreeNode<T>::Rank;

        // 构造函数不能传入子女，只能传入数据和父结点
        BSTNode(const T &data = T(), BSTNode *father_ = nullptr);

        // 对于 BSTNode，结点数据不允许修改
        const T &data() const;

        // 二叉搜索树结点对于插入和删除孩子结点的操作
        // 只能插入和删除这个结点的某个孩子
        TreeNode<T> *insert_child(TreeNode<T> *pNode) override;
        virtual bool insert_child_by_data(const T &data);

        // 注意被删除后的孩子结点的生命周期将不再受父亲管理
        BSTNode *remove_child(BSTNode *pNode);
        BSTNode *remove_child_by_data(const T &data);

        const char *get_entity_name() const override;

        // 不得再使用 exchange_children 方法
        void exchange_children() = delete;
    };
} // CZ

#include "BSTNode_implementation.h"

#endif // BST_NODE_H
