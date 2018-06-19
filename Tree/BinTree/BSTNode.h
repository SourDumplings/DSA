/*
 @Date    : 2018-06-13 19:05:36
 @Author  : 酸饺子 (changzheng300@foxmail.com)
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
    template <typename T> class BST;

    template <typename T>
    class BSTNode: public BinTreeNode<T>
    {
        friend class BST<T>;
    public:
        using Rank = typename BSTNode<T>::Rank;

        // 构造函数不能传入子女，只能传入数据和父结点
        BSTNode(const T &data = T(), BSTNode *father_ = nullptr);

        BSTNode* left_child() const;
        BSTNode*& left_child();
        BSTNode* right_child() const;
        BSTNode*& right_child();
        BSTNode* brother() const;
        BSTNode* uncle() const;
        // 中序遍历下的直接前驱和后继
        BSTNode* prev() const;
        BSTNode* next() const;
        BSTNode*& father();
        BSTNode* father() const;

        // 二叉搜索树结点对于插入和删除孩子结点的操作
        // 只能插入和删除这个结点的某个孩子，不满足搜索树条件则抛出异常
        void insert_child(BSTNode *node);
        BSTNode* remove_child(BSTNode *node);
        void insert_child(const T &data);
        BSTNode* remove_child(const T &data);
        BSTNode* zig(); // 顺时针旋转, 返回旋转后的原来位置的结点指针
        BSTNode* zag(); // 逆时针旋转, 返回旋转后的原来位置的结点指针
    private:
        // 将二叉树结点指定左右的动态操作隐藏
        void insert_as_left_child(BSTNode *newChild);
        void insert_as_right_child(BSTNode *newChild);
    };
} // CZ

#include "BSTNode_implementation.h"

#endif // BST_NODE_H


