/*
 @Date    : 2018-05-26 13:36:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
数类模板的实现
 */

#ifndef TREE_IMPLEMENTATION_H
#define TREE_IMPLEMENTATION_H

#include "Tree.h"

#include "../CZString/CZString.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <utility>

namespace CZ
{
    template <typename T>
    Tree<T>::Tree(std::nullptr_t) : Tree<T>() {}

    template <typename T>
    Tree<T>::Tree(TreeNode<T> *root_) : _root(root_)
    {
        if (root_)
        {
            _size = root_->get_size();
        }
        // std::cout << "Tree constructor" << std::endl;
    }

    template <typename T>
    void Tree<T>::free_node(TreeNode<T> *root)
    {
        if (root)
        {
            for (auto &c : root->children())
            {
                free_node(c);
            }
            delete root;
        }
        return;
    }

    template <typename T>
    void Tree<T>::clear()
    {
        free_node(_root);
        _root = nullptr;
        _size = 0;
        return;
    }

    template <typename T>
    TreeNode<T> *Tree<T>::copy_from(TreeNode<T> *root)
    {
        if (!root)
        {
            return nullptr;
        }
        TreeNode<T> *copiedRoot = new TreeNode<T>(root->data(), nullptr, 1);
        for (auto &c : root->children())
        {
            TreeNode<T> *child = copy_from(c);
            if (child)
            {
                child->father() = copiedRoot;
                if (child->height() >= copiedRoot->height())
                {
                    copiedRoot->height() = child->height() + 1;
                }
            }
            copiedRoot->children().push_back(child);
        }
        return copiedRoot;
    }

    template <typename T>
    Tree<T>::Tree(const Tree<T> &t) : _root(copy_from(t._root)), _size(t._size) {}

    template <typename T>
    Tree<T>::Tree(Tree<T> &&t) : _root(t._root), _size(t._size)
    {
        t._root = nullptr;
        t._size = 0;
    }

    template <typename T>
    Tree<T> &Tree<T>::operator=(const Tree<T> &t)
    {
        if (&t != this)
        {
            clear();
            _root = copy_from(t._root);
            _size = t._size;
        }
        return *this;
    }

    template <typename T>
    Tree<T> &Tree<T>::operator=(Tree<T> &&t)
    {
        if (&t != this)
        {
            _root = t._root;
            _size = t._size;

            t._root = nullptr;
            t._size = 0;
        }
        return *this;
    }

    template <typename T>
    Tree<T>::~Tree() { clear(); }

    template <typename T>
    inline typename Tree<T>::Rank Tree<T>::size() const { return _size; }

    template <typename T>
    inline TreeNode<T> *Tree<T>::root() const { return _root; }

    template <typename T>
    inline TreeNode<T> *&Tree<T>::root() { return _root; }

    template <typename T>
    inline typename Tree<T>::Rank Tree<T>::height() const
    {
        return _root ? _root->height() : 0;
    }

    template <typename T>
    inline bool Tree<T>::has_this_node(const TreeNode<T> *node) const
    {
        return _root == node->get_root();
    }

    template <typename T>
    typename Tree<T>::Rank Tree<T>::depth(const TreeNode<T> *node) const
    {
        if (!node->_father)
        {
            if (node == _root)
            {
                return 1;
            }
            else
            {
                printf("Error from Tree depth: this node is not in this tree\n");
                throw std::exception();
            }
        }
        return depth(node->_father) + 1;
    }

    template <typename T>
    TreeNode<T> *Tree<T>::LCA(TreeNode<T> *a, TreeNode<T> *b) const
    {
        Rank dA, dB;
        try
        {
            dA = depth(a);
            dB = depth(b);
        }
        catch (std::exception())
        {
            printf("Error from Tree lca: these two nodes must in this tree both\n");
            throw std::exception();
        }

        Rank dH = dA, dL = dB;
        TreeNode<T> *h = a, *l = b;
        if (dB < dA)
        {
            dH = dB;
            dL = dA;
            h = b;
            l = a;
        }
        // 先上到同一层
        while (dL != dH && l->_father != h)
        {
            --dL;
            l = l->_father;
        }
        // 然后一起上升，啥时候父亲相等了就是lca了
        while (l->_father != h && l->_father != h->_father)
        {
            l = l->_father;
            h = h->_father;
        }
        return l->_father;
    }

    template <typename T>
    void Tree<T>::insert(TreeNode<T> *father, TreeNode<T> *node)
    {
        try
        {
            if (!father)
            {
                throw "father is nullptr, cannot be a father";
            }
            if (!node)
            {
                throw "node is nullptr, cannot be a child";
            }
            if (node->father())
            {
                throw "this node has already had a father";
            }

            if (_root)
            {
                if (father->get_root() != _root)
                {
                    throw "this father is not a node in this tree";
                }
                father->insert_child(node);
            }
            else
            {
                if (father)
                {
                    throw "root node cannot have a father";
                }
                _root = node;
            }
            _size += node->get_size();
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            std::exception();
        }
        return;
    }

    template <typename T>
    TreeNode<T> *Tree<T>::secede(TreeNode<T> *node)
    {
        if (!node)
        {
            return nullptr;
        }

        try
        {
            if (node->get_root() != _root)
            {
                throw "this node is not in this tree";
            }
            if (node == _root)
            {
                // 不能移除根结点
                throw "cannot remove root";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }

        // 找同父亲的兄弟姐妹结点中最高的
        // 同时找到要删除的目标结点的位置的迭代器
        typename TreeNode<T>::Rank maxChildHeight = 0;
        TreeNode<T> *tallestChild, *f = node->father();
        typename List<TreeNode<T> *>::Iterator nodePos;

        for (typename List<TreeNode<T> *>::Iterator it = f->children().begin(); it != f->children().end(); ++it)
        {
            if (*it == node)
            {
                nodePos = it;
            }
            if ((*it)->height() > maxChildHeight)
            {
                tallestChild = *it;
                maxChildHeight = tallestChild->height();
            }
        }

        // 删掉目标结点
        f->children().erase(nodePos);
        typename TreeNode<T>::Rank sizeLess = node->get_size();
        _size -= sizeLess;

        // 如果目标结点就是它父节点的最高的孩子
        // 则需要向上更新高度
        if (tallestChild == node)
        {
            node->update_height_above(1);
        }

        // 被删掉的目标结点解除其与父亲的关系
        node->father() = nullptr;

        return node;
    }

    template <typename T>
    void Tree<T>::update_size()
    {
        if (_root)
        {
            _size = _root->get_size();
        }
        else
            _size = 0;
        return;
    }

    template <typename T>
    void Tree<T>::OutPut::operator()(const T &data) const
    {
        std::cout << data << " ";
        return;
    }

    template <typename T>
    inline bool operator==(const Tree<T> &lhs, const Tree<T> &rhs)
    {
        if (lhs._root == nullptr)
        {
            return rhs._root == nullptr;
        }
        if (rhs._root == nullptr)
        {
            return lhs._root == nullptr;
        }

        return *(lhs._root) == *(rhs._root);
    }

    template <typename T>
    inline bool operator!=(const Tree<T> &lhs, const Tree<T> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T>
    inline bool Tree<T>::equivalent(const Tree<T> &lhs, const Tree<T> &rhs)
    {
        return TreeNode<T>::equivalent(*lhs.root(), *rhs.root());
    }

    template <typename T>
    inline const char *Tree<T>::get_entity_name() const
    {
        return "Tree";
    }

    template <typename T>
    HashRank Tree<T>::hash() const
    {
        HashRank res = Hash<CZString>()(get_entity_name());
        if (_root)
        {
            res = (res + Hash<TreeNode<T>>()(*_root)) % CZ_MAX_HASH_VALUE;
        }
        return res;
    }

    template <typename T>
    const char *Tree<T>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "[";
        Rank count = 0;
        level_order_traversal(_root, [&](const T &data)
                              {
                                if (0 < count)
                                {
                                    oss << ", ";
                                }
                                oss << data;
                                ++count; });
        oss << "]";
        return this->get_c_str_from_stream(oss);
    }
} // CZ

#include "Tree_traversal.h"

#endif // TREE_IMPLEMENTATION_H
