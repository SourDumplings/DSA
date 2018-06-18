/*
 @Date    : 2018-06-18 11:43:32
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
AVL树结点类模板
几乎全部是直接继承BSTNode的方法，只是修改了一些方法的返回类型而已
 */

#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include "BSTNode.h"
#include "../../Algorithms/Abs.h"

namespace CZ
{
    template <typename T>
    class AVLTreeNode: public BSTNode<T>
    {
    public:
        using Rank = typename BSTNode<T>::Rank;

        AVLTreeNode(const T &data = T(), AVLTreeNode *father_ = nullptr):
            BSTNode<T>(data, father_) {}

        bool is_balance() const
        {
            Rank lH = left_child() ? left_child()->height() : 0,
                rH = right_child() ? right_child()->height() : 0;
            return Abs(static_cast<int>(lH - rH)) < 2;
        }
        AVLTreeNode<T>* taller_child() const
        {
            Rank lH = left_child() ? left_child()->height() : 0,
                rH = right_child() ? right_child()->height() : 0;
            return lH < rH ? right_child() : left_child();
        }

        AVLTreeNode* left_child() const
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::left_child()); }
        AVLTreeNode*& left_child()
        { return (AVLTreeNode*&)(BSTNode<T>::left_child()); }
        AVLTreeNode* right_child() const
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::right_child()); }
        AVLTreeNode*& right_child()
        { return (AVLTreeNode*&)(BSTNode<T>::right_child()); }
        AVLTreeNode* brother() const
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::brother()); }
        AVLTreeNode* uncle() const
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::uncle()); }
        // 中序遍历下的直接前驱和后继
        AVLTreeNode* prev() const
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::prev()); }
        AVLTreeNode* next() const
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::next()); }
        AVLTreeNode*& father()
        { return (AVLTreeNode<T>*&)(BSTNode<T>::father()); }
        AVLTreeNode* father() const
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::father()); }

        // 树结点本身不负责旋转，旋转交给AVL树模板类，故直接继承BST的算法即可
        AVLTreeNode* remove_child(AVLTreeNode *node)
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::remove_child(node)); }
        AVLTreeNode* remove_child(const T &data)
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::remove_child(data)); }
        AVLTreeNode* remove_left_child()
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::remove_left_child()); }
        AVLTreeNode* remove_right_child()
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::remove_right_child()); }
        AVLTreeNode* zig() // 顺时针旋转, 返回旋转后的原来位置的结点指针
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::zig()); }
        AVLTreeNode* zag() // 逆时针旋转, 返回旋转后的原来位置的结点指针
        { return reinterpret_cast<AVLTreeNode<T>*>(BSTNode<T>::zag()); }
    };
} // CZ

#endif // AVL_TREE_NODE_H
