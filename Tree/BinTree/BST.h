/*
 @Date    : 2018-06-10 19:16:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉搜索树类模板
 */

#ifndef BST_H
#define BST_H

#include "BinTree.h"

#include <utility>

namespace CZ
{
    template <typename T, typename CMP = std::less<T>>
    class BST: public BinTree<T>
    {
    public:
        // 二叉搜索树的构造函数
        BST(std::nullptr_t);
        BST(BinTreeNode<T> *root = nullptr);
        BST(const BST<T> &t);
        BST(BST<T> &&t);
    };

} // CZ

#include "BST_implementation.h"

#endif // BST_H


