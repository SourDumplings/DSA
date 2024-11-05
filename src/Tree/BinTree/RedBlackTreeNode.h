/*
 @Date    : 2018-07-19 21:42:35
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树结点类模板
 */

#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

#include "BSTNode.h"

namespace CZ
{
    template <typename T>
    class RedBlackTree;

    template <typename T>
    class RedBlackTreeNode : public BSTNode<T>
    {
        friend class RedBlackTree<T>;

    public:
        using Rank = typename BSTNode<T>::Rank;

        // 构造函数，默认构造的结点为红结点，黑高度为 0
        RedBlackTreeNode(const T &data = T(), RedBlackTreeNode *father_ = nullptr) : BSTNode<T>(data, father_), _red(true), _blackHeight(0) {}

        bool insert_child_by_data(const T &data) override
        {
            RedBlackTreeNode<T> *pNode = new RedBlackTreeNode<T>(data);
            TreeNode<T> *pRes = this->insert_child(pNode);
            if (pNode && pRes == nullptr)
            {
                delete pNode;
                return false;
            }
            return true;
        }

        const char *get_entity_name() const override
        {
            return "RedBlackTreeNode";
        }

    private:
        bool _red;         // 颜色
        Rank _blackHeight; // 黑高度
    };
} // CZ

#endif // RED_BLACK_TREE_NODE_H
