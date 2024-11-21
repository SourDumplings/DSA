/*
 @Date    : 2018-06-03 14:38:16
 @Author  : 酸饺子 (sourdumplings@qq.com)
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

namespace DSA
{
    namespace BinTreeTraversalAccessories
    {
        template <typename T, typename F>
        void pre_order_traversal_recursion(BinTreeNode<T> *root, const F &visit)
        {
            visit(root->data());
            if (root->left_child())
            {
                pre_order_traversal_recursion(root->left_child(), visit);
            }
            if (root->right_child())
            {
                pre_order_traversal_recursion(root->right_child(), visit);
            }
        }

        template <typename T, typename F>
        void pre_order_traversal_nonrecursion1(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T> *> S;
            S.push(root);
            while (!S.empty())
            {
                BinTreeNode<T> *f = S.top();
                S.pop();
                visit(f->data());
                if (f->right_child())
                {
                    S.push(f->right_child());
                }
                if (f->left_child())
                {
                    S.push(f->left_child());
                }
            }
        }

        // 二叉树的先序遍历可以看做是从根结点一路向左访问
        // 遇到的所有结点只要有右儿子就将其入栈
        // 最左侧的结点被访问完后再弹栈，即从最深的右儿子开始再先序遍历
        template <typename T, typename F>
        void pre_order_traversal_nonrecursion2(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T> *> S;
            BinTreeNode<T> *node = root;
            while (true)
            {
                while (node)
                {
                    visit(node->data());
                    if (node->right_child())
                    {
                        S.push(node->right_child());
                    }
                    node = node->left_child();
                }
                if (S.empty())
                {
                    break;
                }
                node = S.top();
                S.pop();
            }
        }

        // Morris 遍历法，
        // 使用空余孩子指针记录相对根节点，不需要栈
        // 空间复杂度 O(1)，时间 O(n)
        // 参考：https://blog.csdn.net/danmo_wuhen/article/details/104339630
        // 由于 Morris 遍历过程中会改变树的结构，但不涉及父结点指针，故无需更新父结点指针
        template <typename T, typename F>
        void pre_order_traversal_nonrecursion3(BinTreeNode<T> *root, const F &visit)
        {
            BinTreeNode<T> *node = root;
            while (node)
            {
                if (node->left_child())
                {
                    BinTreeNode<T> *tmp = node->left_child();
                    // 去左子树的最右端
                    while (tmp->right_child() && tmp->right_child() != node)
                    {
                        tmp = tmp->right_child();
                    }

                    if (tmp->right_child() == nullptr)
                    {
                        // 第一次到达左子树的最右端
                        visit(node->data());
                        tmp->set_right_child(node);
                        node = node->left_child();
                    }
                    else
                    {
                        // 第二次到达左子树的最右端
                        // 说明左子树已经访问完毕，需要还原树结构
                        tmp->set_right_child(nullptr);
                        node = node->right_child();
                    }
                }
                else
                {
                    // 左子树为空，直接访问该结点即可
                    visit(node->data());
                    node = node->right_child();
                }
            }
        }

        template <typename T, typename F>
        void in_order_traversal_recursion(BinTreeNode<T> *root, const F &visit)
        {
            if (root->left_child())
            {
                in_order_traversal_recursion(root->left_child(), visit);
            }
            visit(root->data());
            if (root->right_child())
            {
                in_order_traversal_recursion(root->right_child(), visit);
            }
        }

        // 二叉树的中序遍历可以看做是从根结点一路向左入栈
        // 然后弹栈并访问，进入其右子树进行中序遍历
        template <typename T, typename F>
        void in_order_traversal_nonrecursion1(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T> *> S;
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
                leftMost = S.top();
                S.pop();
                visit(leftMost->data());
                // 转向右子树
                root = leftMost->right_child();
            }
        }

        // 实际上为NONRECURSION_TRAVERSAL1的等价版本
        template <typename T, typename F>
        void in_order_traversal_nonrecursion2(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T> *> S;
            while (true)
            {
                if (root)
                {
                    S.push(root);
                    root = root->left_child();
                }
                else if (!S.empty())
                {
                    root = S.top();
                    S.pop();
                    visit(root->data());
                    root = root->right_child();
                }
                else
                {
                    break;
                }
            }
        }

        // 不需要借助堆栈，（额外）空间复杂度由O(logn)降为O(1)
        // 但是由于要调用next()，牺牲了时间效率
        template <typename T, typename F>
        void in_order_traversal_nonrecursion3(BinTreeNode<T> *root, const F &visit)
        {
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
        }

        // Morris 遍历法
        // 参考：https://blog.csdn.net/danmo_wuhen/article/details/104339630
        // Morris 中序遍历和前序遍历相差不大，只是在访问位置上出现了变化
        // 空间复杂度 O(1)，时间 O(n)
        // 由于 Morris 遍历过程中会改变树的结构，但不涉及父结点指针，故无需更新父结点指针
        template <typename T, typename F>
        void in_order_traversal_nonrecursion4(BinTreeNode<T> *root, const F &visit)
        {
            BinTreeNode<T> *node = root;
            while (node)
            {
                if (node->left_child())
                {
                    BinTreeNode<T> *tmp = node->left_child();
                    // 去左子树的最右端
                    while (tmp->right_child() && tmp->right_child() != node)
                    {
                        tmp = tmp->right_child();
                    }

                    if (tmp->right_child() == nullptr)
                    {
                        // 第一次到达左子树的最右端
                        tmp->set_right_child(node);
                        node = node->left_child();
                    }
                    else
                    {
                        // 第二次到达左子树的最右端
                        // 说明左子树已经访问完毕，需要还原树结构
                        tmp->set_right_child(nullptr);
                        visit(node->data());
                        node = node->right_child();
                    }
                }
                else
                {
                    // 左子树为空，直接访问该结点即可
                    visit(node->data());
                    node = node->right_child();
                }
            }
        }

        template <typename T, typename F>
        void post_order_traversal_recursion(BinTreeNode<T> *root, const F &visit)
        {
            if (root->left_child())
            {
                post_order_traversal_recursion(root->left_child(), visit);
            }
            if (root->right_child())
            {
                post_order_traversal_recursion(root->right_child(), visit);
            }
            visit(root->data());
        }

        // 后序遍历的访问顺序为先是左侧最高可见叶结点（LHVFL）
        // 再深入其右兄弟（可能不存在）后序遍历
        // 最后是其父亲结点，于是一路尽量向左地向下走，一路将父结点和右兄弟压栈，直到走到叶结点
        template <typename T, typename F>
        void post_order_traversal_nonrecursion1(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T> *> S;
            S.push(root);

            while (!S.empty())
            {
                if (S.top() != root->father())
                {
                    // 如果栈顶结点不是当前结点的父结点，则必为右兄弟结点，
                    // 则需要深入右兄弟找到左侧最高可见叶结点(LHVFL)
                    BinTreeNode<T> *temp = nullptr;
                    while (static_cast<bool>(temp = S.top()))
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
                        {
                            // 如果没有左孩子的结点就直接将可能为空的右孩子入栈
                            S.push(temp->right_child());
                        }
                    }
                    S.pop(); // 弹出栈顶空结点
                }
                root = S.top();
                S.pop();
                visit(root->data());
            }
        }

        // 这种做法来自于王道，不需要借助父亲指针
        template <typename T, typename F>
        void post_order_traversal_nonrecursion2(BinTreeNode<T> *root, const F &visit)
        {
            Stack<BinTreeNode<T> *> S;
            BinTreeNode<T> *p = root, *lastVisited = nullptr;
            while (p || !S.empty())
            {
                if (p)
                {
                    // p不为空，则向左走到底，顺路压栈
                    S.push(p);
                    p = p->left_child();
                }
                else
                {
                    // p为空时，针对于栈顶元素，即目前的最左侧元素讨论
                    p = S.top();
                    if (p->right_child() && p->right_child() != lastVisited)
                    {
                        // 如果最左侧元素有右孩子并且右孩子不是刚刚访问过的那个，则将右孩子压栈
                        // 并转入其左侧
                        p = p->right_child();
                        S.push(p);
                        p = p->left_child();
                    }
                    else
                    {
                        // 否则，访问之，p置空，弹栈
                        visit(p->data());
                        lastVisited = p;
                        p = nullptr;
                        S.pop();
                    }
                }
            }
        }

        // 这种做法是相当于模拟了递归，类似于 pre_order_traversal_nonrecursion1
        template <typename T, typename F>
        void post_order_traversal_nonrecursion3(BinTreeNode<T> *root, const F &visit)
        {
            List<BinTreeNode<T> *> list;
            Vector<BinTreeNode<T> *> reverseVisitV;
            if (root)
            {
                list.push_front(root);
                while (!list.empty())
                {
                    BinTreeNode<T> *p = list.front();
                    reverseVisitV.push_back(p);
                    list.pop_front();
                    if (p->left_child())
                    {
                        list.push_front(p->left_child());
                    }
                    if (p->right_child())
                    {
                        list.push_front(p->right_child());
                    }
                }
            }
            typename Vector<T>::Rank n = reverseVisitV.size();
            typename Vector<T>::Rank l = static_cast<typename Vector<T>::Rank>(0);
            for (typename Vector<T>::Rank i = n - 1; i >= l; --i)
            {
                visit(reverseVisitV[i]->data());
                if (i == l)
                {
                    break;
                }
            }

        }

        // Morris 遍历法
        // 参考：https://blog.csdn.net/danmo_wuhen/article/details/104339630
        // 空间复杂度 O(1)，时间复杂度 O(n)
        // Morris 后序遍历较为复杂，因为右孩子需要在根节点之前输出
        // 需要逆转左子树右边界结点的父子关系，再恢复
        // 由于 Morris 遍历过程中会改变树的结构，但不涉及父结点指针，故无需更新父结点指针
        namespace Morris
        {
            template <typename T>
            BinTreeNode<T> *reverse_node(BinTreeNode<T> *node)
            {
                BinTreeNode<T> *p = nullptr;
                BinTreeNode<T> *q = nullptr;
                while (node)
                {
                    q = node->right_child();
                    node->set_right_child(p);
                    p = node;
                    node = q;
                }
                return p;
            }

            template <typename T, typename F>
            void visit_node_after_reverse(BinTreeNode<T> *node, const F &visit)
            {
                BinTreeNode<T> *tail = reverse_node(node);
                BinTreeNode<T> *cur = tail;
                while (cur)
                {
                    visit(cur->data());
                    cur = cur->right_child();
                }
                reverse_node(tail);
            }
        }

        template <typename T, typename F>
        void post_order_traversal_nonrecursion4(BinTreeNode<T> *root, const F &visit)
        {
            BinTreeNode<T> *node = root;
            while (node)
            {
                if (node->left_child())
                {
                    BinTreeNode<T> *tmp = node->left_child();
                    // 去左子树的最右端
                    while (tmp->right_child() && tmp->right_child() != node)
                    {
                        tmp = tmp->right_child();
                    }

                    if (tmp->right_child() == nullptr)
                    {
                        // 第一次到达左子树的最右端
                        tmp->set_right_child(node);
                        node = node->left_child();
                    }
                    else
                    {
                        // 第二次到达左子树的最右端
                        // 说明左子树已经访问完毕，需要还原树结构
                        tmp->set_right_child(nullptr);
                        Morris::visit_node_after_reverse(node->left_child(), visit);
                        node = node->right_child();
                    }
                }
                else
                {
                    // 左子树为空
                    node = node->right_child();
                }
            }
            Morris::visit_node_after_reverse(root, visit);
        }
    } // BinTreeTraversalAccessories

    template <typename T>
    template <typename F>
    void BinTree<T>::pre_order_traversal(BinTreeNode<T> *root, const F &visit,
                                         const BinTreeTraversalVersion &version)
    {
        if (root == nullptr)
        {
            return;
        }

        switch (version)
        {
        case RECURSION_TRAVERSAL:
        {
            BinTreeTraversalAccessories::pre_order_traversal_recursion(root, visit);
            break;
        }
        case NONRECURSION_TRAVERSAL1:
        {
            BinTreeTraversalAccessories::pre_order_traversal_nonrecursion1(root, visit);
            break;
        }
        case NONRECURSION_TRAVERSAL2:
        {
            BinTreeTraversalAccessories::pre_order_traversal_nonrecursion2(root,
                                                                visit);
            break;
        }
        case NONRECURSION_TRAVERSAL3:
        case NONRECURSION_TRAVERSAL4:
        {
            BinTreeTraversalAccessories::pre_order_traversal_nonrecursion3(root,
                                                                visit);
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
            BinTreeTraversalAccessories::in_order_traversal_recursion(root, visit);
            break;
        }
        case NONRECURSION_TRAVERSAL1:
        {
            BinTreeTraversalAccessories::in_order_traversal_nonrecursion1(root, visit);
            break;
        }
        case NONRECURSION_TRAVERSAL2:
        {
            BinTreeTraversalAccessories::in_order_traversal_nonrecursion2(root, visit);
            break;
        }
        case NONRECURSION_TRAVERSAL3:
        {
            BinTreeTraversalAccessories::in_order_traversal_nonrecursion3(root, visit);
            break;
        }
        case NONRECURSION_TRAVERSAL4:
        {
            BinTreeTraversalAccessories::in_order_traversal_nonrecursion4(root, visit);
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
            BinTreeTraversalAccessories::post_order_traversal_recursion(root, visit);
            break;
        }
        case NONRECURSION_TRAVERSAL1:
        {
            BinTreeTraversalAccessories::post_order_traversal_nonrecursion1(root,
                                                                 visit);
            break;
        }
        case NONRECURSION_TRAVERSAL2:
        {
            BinTreeTraversalAccessories::post_order_traversal_nonrecursion2(root,
                                                                 visit);
            break;
        }
        case NONRECURSION_TRAVERSAL3:
        {
            BinTreeTraversalAccessories::post_order_traversal_nonrecursion3(root,
                                                                 visit);
            break;
        }
        case NONRECURSION_TRAVERSAL4:
        {
            BinTreeTraversalAccessories::post_order_traversal_nonrecursion4(root,
                                                                 visit);
            break;
        }
        }
    }

    template <typename T>
    template <typename F>
    void BinTree<T>::level_order_traversal(BinTreeNode<T> *pRoot, const F &visit)
    {
        Queue<BinTreeNode<T> *> q;
        q.push(pRoot);
        while (!q.empty())
        {
            BinTreeNode<T> *pNode = q.front();
            q.pop();
            if (pNode)
            {
                visit(pNode->data());
                q.push(pNode->left_child());
                q.push(pNode->right_child());
            }
        }
    }
} // DSA

#endif // BIN_TREE_TRAVERSAL_H
