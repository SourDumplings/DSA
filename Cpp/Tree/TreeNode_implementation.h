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
    TreeNode<T>::TreeNode(const T &data_, typename TreeNode<T>::Rank height_,
        Shared_ptr<TreeNode<T>> father_):
        _data(data_), _height(height_), _father(father_) {}

    template <typename T>
    TreeNode<T>::~TreeNode() = default;

    template <typename T>
    inline Shared_ptr<TreeNode<T>> TreeNode<T>::father() const
    { return _father; }

    template <typename T>
    Shared_ptr<TreeNode<T>> TreeNode<T>::get_root() const
    {
        Shared_ptr<TreeNode<T>> r = _father;
        while (r->_father)
        {
            r = r->_father;
        }
        return r;
    }

    template <typename T>
    Shared_ptr<TreeNode<T>> TreeNode<T>::oldest_child() const
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
    inline const T& TreeNode<T>::data() const { return _data; }

    template <typename T>
    inline T& TreeNode<T>::data() { return _data; }

    template <typename T>
    inline bool TreeNode<T>::is_leaf() const { return _children.empty() ? true : false; }

    template <typename T>
    inline const typename TreeNode<T>::Rank& TreeNode<T>::height() const { return _height; }

    template <typename T>
    inline typename TreeNode<T>::Rank& TreeNode<T>::height() { return _height; }

    template <typename T>
    inline const List<Shared_ptr<TreeNode<T>>>& TreeNode<T>::children() const
    { return _children; }

    template <typename T>
    inline List<Shared_ptr<TreeNode<T>>>& TreeNode<T>::children()
    { return _children; }

    template <typename T>
    typename TreeNode<T>::Rank TreeNode<T>::depth() const
    {
        typename TreeNode<T>::Rank ret = 0;
        Shared_ptr<TreeNode<T>> p = _father;
        while (p)
        {
            ++ret;
            p = p->_father;
        }
        return ret;
    }

    template <typename T>
    void TreeNode<T>::insert_child(Shared_ptr<TreeNode<T>> node)
    {
        _children.push_back(node);
        _height = (node->_height >= _height) ? node->_height + 1 : _height;
        node->_father = this;
        return;
    }

    template <typename T>
    typename TreeNode<T>::Rank TreeNode<T>::get_size() const
    {
        Rank ret = 1;
        for (auto &c : _children)
        {
            ret += c->get_size();
        }
        return ret;
    }
} // CZ

#endif // TREE_NODE_IMPLEMENTATION_H


