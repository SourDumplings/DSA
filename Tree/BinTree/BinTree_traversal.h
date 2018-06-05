/*
 @Date    : 2018-06-03 14:38:16
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板的遍历算法
 */

#ifndef BIN_TREE_TRAVERSAL_H
#define BIN_TREE_TRAVERSAL_H

#include "BinTree.h"
#include "../../Stack/Stack.h"

namespace CZ
{
    namespace BinTreeTraversal
    {
        template <typename T, typename F>
        void pre_order_traversal_recursion(BinTreeNode<T> *root, const F &visit)
        {
            visit(root->data());
            if (root->left_child())
                pre_order_traversal_recursion(root->left_child(), visit);
            if (root->right_child())
                pre_order_traversal_recursion(root->right_child(), visit);
            return;
        }

        template <typename T, typename F>
        void pre_order_traversal_nonrecursion1(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T>*> S;
            S.push(root);
            while (!S.empty())
            {
                BinTreeNode<T> *f = S.top(); S.pop();
                visit(f->data());
                if (f->left_child()) S.push(f->left_child());
                if (f->right_child()) S.push(f->right_child());
            }
            return;
        }

        template <typename T, typename F>
        void pre_order_traversal_nonrecursion2(BinTreeNode<T> *root, const F &visit)
        {
            // 二叉树的先序遍历可以看做是从根结点一路向左访问
            // 遇到的所有结点只要有右儿子就将其入栈
            // 最左侧的结点被访问完后再弹栈，即从最深的右儿子开始再先序遍历
            Stack<BinTreeNode<T>*> S;
            BinTreeNode<T> *node = root;
            while (true)
            {
                while (node)
                {
                    visit(node->data());
                    if (node->right_child()) S.push(node->right_child());
                    node = node->left_child();
                }
                if (S.empty())
                {
                    break;
                }
                node = S.top(); S.pop();
            }
            return;
        }

        template <typename T, typename F>
        void in_order_traversal_recursion(BinTreeNode<T> *root, const F &visit)
        {
            if (root->left_child())
                in_order_traversal_recursion(root->left_child(), visit);
            visit(root->data());
            if (root->right_child())
                in_order_traversal_recursion(root->right_child(), visit);
            return;
        }

        template <typename T, typename F>
        void in_order_traversal_nonrecursion1(BinTreeNode<T> *root, const F &visit)
        {
            // 二叉树的中序遍历可以看做是从根结点一路向左入栈
            // 然后弹栈并访问，进入其右子树进行中序遍历
            Stack<BinTreeNode<T>*> S;
            while (true)
            {
                BinTreeNode<T> *leftMost = root;
                while (leftMost)
                {
                    S.push(leftMost);
                    leftMost = leftMost->left_child();
                }
                if (S.empty())
                {
                    break;
                }
                leftMost = S.top(); S.pop();
                visit(leftMost->data());
                // 转向右子树
                root = leftMost->right_child();
            }
            return;
        }

        template <typename T, typename F>
        void in_order_traversal_nonrecursion2(BinTreeNode<T> *root, const F &visit)
        {
            // 实际上为NONRECURSION_TRAVERSAL1的等价版本
            Stack<BinTreeNode<T>*> S;
            while (true)
            {
                if (root)
                {
                    S.push(root);
                    root = root->left_child();
                }
                else if (!S.empty())
                {
                    root = S.top(); S.pop();
                    visit(root->data());
                    root = root->right_child();
                }
                else
                    break;
            }
            return;
        }

        template <typename T, typename F>
        void in_order_traversal_nonrecursion3(BinTreeNode<T> *root, const F &visit)
        {
            // 不需要借助堆栈，（额外）空间复杂度由O(logn)降为O(1)
            // 但是由于要调用next()，牺牲了时间效率
            bool backTrace = false; // 记录前一步是否刚刚从右子树回溯，以免重复访问
            while (true)
            {
                if (root->left_child() && !backTrace)
                {
                    // 如果有左子树且不是刚刚回溯，则深入左子树
                    root = root->left_child();
                }
                else
                {
                    // 否则，无左子树或者刚刚回溯（相当于刚刚回溯）
                    visit(root->data());
                    if (root->right_child())
                    {
                        // 如果有右子树则进入右子树
                        root = root->right_child();
                        backTrace = false;
                    }
                    else
                    {
                        // 无右子树，则回溯，标记回溯为true
                        if (!(root = root->next()))
                        {
                            // 无后继，末结点的退出返回
                            break;
                        }
                        backTrace = true;
                    }
                }
            }
            return;
        }

        template <typename T, typename F>
        void post_order_traversal_recursion(BinTreeNode<T> *root, const F &visit)
        {
            if (root->left_child())
                post_order_traversal_recursion(root->left_child(), visit);
            if (root->right_child())
                post_order_traversal_recursion(root->right_child(), visit);
            visit(root->data());
            return;
        }

        // 后序遍历的访问顺序为先是左侧最高可见叶结点（LHVFL）
        // 再深入其右兄（可能不存在）后序遍历
        // 最后是其父亲结点，于是一路尽量向左地向下走，一路将父结点和右兄压栈，直到走到叶结点
        template <typename T, typename F>
        void post_order_traversal_nonrecursion1(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T>*> S;
            S.push(root);
            while (!S.empty())
            {
                if (S.top() != root->father())
                {
                    // 如果栈顶结点不是当前结点的父结点，则必为右兄结点，
                    // 则需要深入右兄找到最侧最高可见叶结点(LHVFL)
                    BinTreeNode<T> *temp = nullptr;
                    while (temp = S.top())
                    {
                        if (temp->left_child())
                        {
                            if (temp->right_child())
                            {
                                S.push(temp->right_child());
                            }
                            S.push(temp->left_child());
                        }
                        else
                            // 如果没有左孩子的结点就直接将可能为空的右孩子入栈
                            S.push(temp->right_child());
                    }
                    S.pop(); // 弹出栈顶空结点
                }
                root = S.top()->data(); S.pop();
                visit(root);
            }
            return;
        }
    } // BinTreeTraversal

    template <typename T>
    template <typename F>
    void BinTree<T>::pre_order_traversal(BinTreeNode<T> *root, const F &visit,
        const BinTreeTraversalVersion &version)
    {
        if (!root)
        {
            return;
        }

        switch (version)
        {
            case RECURSION_TRAVERSAL:
            {
                BinTreeTraversal::pre_order_traversal_recursion(root, visit);
                break;
            }
            case NONRECURSION_TRAVERSAL1:
            {
                BinTreeTraversal::pre_order_traversal_nonrecursion1(root, visit);
                break;
            }
            case NONRECURSION_TRAVERSAL2:
            case NONRECURSION_TRAVERSAL3:
            {
                BinTreeTraversal::pre_order_traversal_nonrecursion2(root, visit);
                break;
            }
        }
    }

    template <typename T>
    template <typename F>
    void BinTree<T>::in_order_traversal(BinTreeNode<T> *root, const F &visit,
        const BinTreeTraversalVersion &version)
    {
        if (!root)
        {
            return;
        }

        switch (version)
        {
            case RECURSION_TRAVERSAL:
            {
                BinTreeTraversal::in_order_traversal_recursion(root, visit);
                break;
            }
            case NONRECURSION_TRAVERSAL1:
            {
                BinTreeTraversal::in_order_traversal_nonrecursion1(root, visit);
                break;
            }
            case NONRECURSION_TRAVERSAL2:
            {
                BinTreeTraversal::in_order_traversal_nonrecursion2(root, visit);
                break;
            }
            case NONRECURSION_TRAVERSAL3:
            {
                BinTreeTraversal::in_order_traversal_nonrecursion3(root, visit);
                break;
            }
        }
    }

    template <typename T>
    template <typename F>
    void BinTree<T>::post_order_traversal(BinTreeNode<T> *root, const F &visit,
        const BinTreeTraversalVersion &version)
    {
        if (!root)
        {
            return;
        }

        switch (version)
        {
            case RECURSION_TRAVERSAL:
            {
                BinTreeTraversal::post_order_traversal_recursion(root, visit);
                break;
            }
            case NONRECURSION_TRAVERSAL1:
            case NONRECURSION_TRAVERSAL2:
            case NONRECURSION_TRAVERSAL3:
            {
                BinTreeTraversal::post_order_traversal_nonrecursion1(root, visit);
                break;
            }
        }
        return;
    }
} // CZ

#endif // BIN_TREE_TRAVERSAL_H


