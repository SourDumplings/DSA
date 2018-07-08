/*
 @Date    : 2018-07-08 22:26:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树数据的访问接口
 */

#ifndef B_TREE_INTERFACES_H
#define B_TREE_INTERFACES_H

#include "BTree.h"
#include "../../Algorithms/Search.h"

namespace CZ
{
    template <typename T>
    inline typename BTree<T>::Rank BTree<T>::order() const { return _order; }

    template <typename T>
    inline typename BTree<T>::Rank BTree<T>::size() const { return _size; }

    template <typename T>
    inline bool BTree<T>::empty() const { return _size == 0; }

    template <typename T>
    inline BTreeNode<T>* BTree<T>::root() const { return _root; }

    template <typename T>
    BTreeNode<T>* BTree<T>::search(const T &data) const
    {
        BTreeNode<T> *v = _root; // 从根结点开始
        _hot = nullptr;
        while (v)
        {
            // 对结点v的关键码向量进行二分查找，返回不大于data的最后一个元素
            typename Vector<T>::iterator it =
                search(v->_keys.begin(), v->keys.end(), data, BINARY_SEARCH, 2);
            if (v->_keys.begin() <= it && *it == data)
            {
                // 找到了该结点
                return v;
            }
            else
            {
                // 否则，转入对应子树逐层查找
                _hot = v;
                v = (v->_children)[it - _root->keys.begin() + 1];
            }
        }
        return nullptr; // 查找失败，抵达外部结点
    }
} // CZ

#endif // B_TREE_INTERFACES_H

