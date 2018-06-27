/*
 @Date    : 2018-06-20 20:25:34
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
伸展树模板
 */

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "SplayTreeNode.h"
#include "BST.h"

namespace CZ
{
    template <typename T>
    class SplayTree: public BST<T>
    {
    public:
        SplayTree(std::nullptr_t);
        SplayTree(SplayTreeNode<T> *root = nullptr);
        SplayTree(const SplayTree<T> &t);
        SplayTree(SplayTree<T> &&t);

        SplayTreeNode<T>*& root();
        SplayTreeNode<T>* root() const;
        void print_info(const char *name = "") const override;
        SplayTreeNode<T>* search(const T &data) const;
        void insert(SplayTreeNode<T> *node);
        void insert(const T &data);
        SplayTreeNode<T>* secede(SplayTreeNode<T> *node);
        SplayTreeNode<T>* secede(const T &data);
        SplayTreeNode<T>* remove(SplayTreeNode<T> *node);
        SplayTreeNode<T>* remove(const T &data);
    protected:
        // 伸展调整算法，将目标结点v伸展至树根
        // 采用双层伸展算法，每次访问最深的叶结点伸展完毕后，树的高度接近折半
        // 采用双层伸展策略之后，伸展树的单次操作均可在O(nlogn)时间完成
        SplayTreeNode<T>* splay(SplayTreeNode<T> *v);
    };
} // CZ

#include "SplayTree_implementation.h"

#endif // SPLAY_TREE_H

