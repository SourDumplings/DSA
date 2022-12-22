/*
 @Date    : 2018-06-06 19:33:49
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树的类模板一些接口
 */

#ifndef BIN_TREE_INTERFACES_H
#define BIN_TREE_INTERFACES_H

#include "BinTree.h"

namespace CZ
{
    template <typename T>
    const char *BinTree<T>::get_entity_name() const
    {
        return "BinTree";
    }
} // CZ

#endif // BIN_TREE_INTERFACES_H

