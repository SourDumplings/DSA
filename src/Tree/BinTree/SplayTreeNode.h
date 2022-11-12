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
    class SplayTreeNode: public BSTNode<T>
    {
    public:
        using Rank = typename BSTNode<T>::Rank;

        // 构造函数不能传入子女，只能传入数据和父结点
        SplayTreeNode(const T &data = T(), SplayTreeNode *father_ = nullptr):
            BSTNode<T>(data, father_) {}

        SplayTreeNode* left_child() const
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::left_child()); }
        SplayTreeNode*& left_child()
        { return (SplayTreeNode<T>*&)(BSTNode<T>::left_child()); }
        SplayTreeNode* right_child() const
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::right_child()); }
        SplayTreeNode*& right_child()
        { return (SplayTreeNode<T>*&)(BSTNode<T>::right_child()); }
        SplayTreeNode* brother() const
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::brother()); }
        SplayTreeNode* uncle() const
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::uncle()); }
        // 中序遍历下的直接前驱和后继
        SplayTreeNode* prev() const
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::prev()); }
        SplayTreeNode* next() const
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::next()); }
        SplayTreeNode*& father()
        { return (SplayTreeNode<T>*&)(BSTNode<T>::father()); }
        SplayTreeNode* father() const
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::father()); }
        SplayTreeNode* remove_child(SplayTreeNode *node)
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::remove_child(node)); }
        SplayTreeNode* remove_child(const T &data)
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::remove_child(data)); }
        SplayTreeNode* zig()  // 顺时针旋转, 返回旋转后的原来位置的结点指针
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::zig()); }
        SplayTreeNode* zag()  // 逆时针旋转, 返回旋转后的原来位置的结点指针
        { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::zag()); }

        const char *get_entity_name() const override
        { return "SplayTreeNode"; }
    };
} // CZ

#endif // SPLAY_TREE_NODE_H

