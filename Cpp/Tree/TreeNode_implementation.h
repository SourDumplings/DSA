/*
 @Date    : 2018-05-25 15:43:22
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树结点类模板的实现
 */

#ifndef TREE_NODE_IMPLEMENTATION_H
#define TREE_NODE_IMPLEMENTATION_H

#include "TreeNode.h"
#include <stdexcept>
#include <cstdio>

namespace CZ
{
    template <typename T>
    TreeNode<T>::TreeNode(const T &data_, unsigned height_, Shared_ptr<TreeNode<T>> father_):
        _data(data_), _height(height_), _father(father_) {}

    template <typename T>
    TreeNode<T>::~TreeNode() = default;

    template <typename T>
    inline Shared_ptr<TreeNode<T>> TreeNode<T>::father()
    { return _father; }

    template <typename T>
    inline const Shared_ptr<TreeNode<T>> TreeNode<T>::father() const
    { return _father; }

    template <typename T>
    const Shared_ptr<TreeNode<T>> TreeNode<T>::oldest_child() const
    {
        try
        {
            if (_children.empty())
            {
                throw "no children";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }
        return _children.front();
    }

    template <typename T>
    inline Shared_ptr<TreeNode<T>> TreeNode<T>::oldest_child()
    {
        return const_cast<Shared_ptr<TreeNode<T>>>
        (static_cast<const TreeNode<T>&>(*this).oldest_child());
    }

    template <typename T>
    inline const T& TreeNode<T>::data() const { return _data; }

    template <typename T>
    inline T& TreeNode<T>::data() { return _data; }

    template <typename T>
    inline bool TreeNode<T>::is_leaf() const { return _children.empty() ? true : false; }

    template <typename T>
    inline const unsigned& TreeNode<T>::height() const { return _height; }

    template <typename T>
    inline unsigned& TreeNode<T>::height() { return _height; }
} // CZ

#endif // TREE_NODE_IMPLEMENTATION_H


