/*
 @Date    : 2018-07-19 21:42:35
 @Author  : 酸饺子 (changzheng300@foxmail.com)
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
    template <typename T> class RedBlackTree;

    template <typename T>
    class RedBlackTreeNode: public BSTNode<T>
    {
        friend class RedBlackTree<T>;
    public:
        using Rank = typename BSTNode<T>::Rank;

        // 构造函数，默认构造的结点为红结点，黑高度为1
        RedBlackTreeNode(const T &data = T(), RedBlackTreeNode *father_ = nullptr):
            BSTNode<T>(data, father_), _red(true), _blackHeight(0) {}

        RedBlackTreeNode* left_child() const
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::left_child()); }
        RedBlackTreeNode*& left_child()
        { return (RedBlackTreeNode*&)(BSTNode<T>::left_child()); }
        RedBlackTreeNode* right_child() const
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::right_child()); }
        RedBlackTreeNode*& right_child()
        { return (RedBlackTreeNode*&)(BSTNode<T>::right_child()); }
        RedBlackTreeNode* brother() const
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::brother()); }
        RedBlackTreeNode* uncle() const
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::uncle()); }
        // 中序遍历下的直接前驱和后继
        RedBlackTreeNode* prev() const
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::prev()); }
        RedBlackTreeNode* next() const
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::next()); }
        RedBlackTreeNode*& father()
        { return (RedBlackTreeNode<T>*&)(BSTNode<T>::father()); }
        RedBlackTreeNode* father() const
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::father()); }

        const char *get_entity_name() const override
        {
            return "RedBlackTreeNode";
        }

    private:
        // 树结点本身不负责旋转，旋转交给AVL树类模板，故直接继承BST的算法即可
        RedBlackTreeNode* remove_child(RedBlackTreeNode *node)
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::remove_child(node)); }
        RedBlackTreeNode* remove_child(const T &data)
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::remove_child(data)); }
        RedBlackTreeNode* zig() // 顺时针旋转, 返回旋转后的原来位置的结点指针
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::zig()); }
        RedBlackTreeNode* zag() // 逆时针旋转, 返回旋转后的原来位置的结点指针
        { return static_cast<RedBlackTreeNode<T>*>(BSTNode<T>::zag()); }
        void remove_left_child() { return BSTNode<T>::remove_left_child(); }
        void remove_right_child() { return BSTNode<T>::remove_right_child(); }

        bool _red; // 颜色
        Rank _blackHeight; // 黑高度
    };
} // CZ

#endif // RED_BLACK_TREE_NODE_H
