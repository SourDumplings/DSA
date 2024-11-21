/*
 @Date    : 2018-06-06 19:33:49
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树的类模板一些接口
 */

#ifndef BIN_TREE_INTERFACES_H
#define BIN_TREE_INTERFACES_H

#include "BinTree.h"

namespace DSA
{
    template <typename T>
    const char *BinTree<T>::get_entity_name() const
    {
        return "BinTree";
    }
} // DSA

#endif // BIN_TREE_INTERFACES_H

