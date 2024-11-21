/*
 @Date    : 2018-07-03 22:52:19
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树的析构函数
 */

#ifndef B_TREE_DESTRUCTORS_H
#define B_TREE_DESTRUCTORS_H

#include "BTree.h"

namespace DSA
{
    template <typename T>
    BTree<T>::~BTree() { clear(); }
} // DSA

#endif // B_TREE_DESTRUCTORS_H
