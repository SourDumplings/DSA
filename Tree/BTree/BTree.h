/*
 @Date    : 2018-07-01 22:42:14
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树模板
 */

#ifndef B_TREE_H
#define B_TREE_H

#include "BTreeNode.h"

namespace CZ
{
    template <typename T>
    class BTree
    {
    public:
        using Rank = unsigned;

        BTree();
        ~BTree();
    protected:
        Rank _size; // 存放的关键码总数
        Rank _order; // B树的阶次，至少为3，创建时就指定，一般不能修改
        BTreeNode<T> *_root; // 根结点的指针
        BTreeNode<T> *_hot; // search()方法最后一次访问（除非树空）的非空结点的指针

    };
} // CZ

#endif // B_TREE_H


