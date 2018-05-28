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
#include <stdexcept>
#include <iostream>
#include <utility>

namespace CZ
{
    template <typename T>
    Tree<T>::Tree(TreeNode<T> *root_): _root(root_)
    {
        if (root_)
        {
            _size = root_->get_size();
        }
        // std::cout << "Tree constructor" << std::endl;
    }

    template <typename T>
    void Tree<T>::free(TreeNode<T> *root)
    {
        if (root)
        {
            for (auto &c : root->children())
            {
                free(c);
            }
            delete root;
        }
        return;
    }

    template <typename T>
    void Tree<T>::clear()
    {
        free(_root);
        _root = nullptr;
        _size = 0;
        return;
    }

    template <typename T>
    TreeNode<T>* Tree<T>::copy_from(TreeNode<T> *root)
    {
        TreeNode<T> *copiedRoot = new TreeNode<T>(root->data(), nullptr, 0);
        for (auto &c : root->children())
        {
            TreeNode<T> *child = copy_from(c);
            child->father() = copiedRoot;
            copiedRoot->children().push_back(child);
            copiedRoot->height() = (child->height() >= copiedRoot->height()) ?
                child->height() + 1 : copiedRoot->height();
        }
        return copiedRoot;
    }

    template <typename T>
    Tree<T>::Tree(const Tree<T> &t): _size(t._size)
    {
        _root = copy_from(t._root);
    }

    template <typename T>
    Tree<T>::Tree(Tree<T> &&t): _root(t._root), _size(t._size)
    {
        t._root = nullptr;
        t._size = 0;
    }

    template <typename T>
    Tree<T>& Tree<T>::operator=(const Tree<T> &t)
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
    Tree<T>& Tree<T>::operator=(Tree<T> &&t)
    {
        if (&t != this)
        {
            _root = t._root;
            _size = t._size;

            t._root = nullptr;
            t._size = t._height = 0;
        }
        return *this;
    }

    template <typename T>
    Tree<T>::~Tree() { clear(); }

    template <typename T>
    inline bool Tree<T>::empty() const { return _size == 0; }

    template <typename T>
    inline typename Tree<T>::Rank Tree<T>::size() const { return _size; }

    template <typename T>
    inline TreeNode<T>* Tree<T>::root() const { return _root; }

    template <typename T>
    inline typename Tree<T>::Rank Tree<T>::height() const
    {
        return _root ? _root->height() : 0;
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

            if (father->get_root() != _root)
            {
                throw "this father is not a node in this tree";
            }
            if (node->father())
            {
                throw "this node has already had a father";
            }
            father->insert_child(node);
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
    Tree<T> Tree<T>::remove(TreeNode<T> *node)
    {
        try
        {
            if (node->get_root() != _root)
            {
                throw "this node is not in this tree";
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
        typename List<TreeNode<T>*>::iterator nodePos;

        for (typename List<TreeNode<T>*>::iterator it = f->children().begin(); it != f->children().end(); ++it)
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

        // 被删掉的目标结点作为根节点构造新子树
        node->father() = nullptr;
        Tree<T> newTree(node);
        return newTree;
    }

    template <typename T>
    void Tree<T>::OutPut::operator() (const T &data) const
    {
        std::cout << data << " ";
        return;
    }

} // CZ

#include "Tree_traversal.h"

#endif // TREE_IMPLEMENTATION_H
