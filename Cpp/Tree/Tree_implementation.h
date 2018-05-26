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

namespace CZ
{
    template <typename T>
    Tree<T>::Tree(Shared_ptr<TreeNode<T>> root_): _root(root_), _height(root_->height()),
        _size(root_->get_size()) {}

    template <typename T>
    void Tree<T>::free(Shared_ptr<TreeNode<T>> root)
    {
        for (auto &c : root->children())
        {
            free(c);
        }
        delete root;
        return;
    }

    template <typename T>
    void Tree<T>::clear()
    {
        free(_root);
        _height = _size = 0;
        return;
    }

    template <typename T>
    Tree<T>::~Tree() { clear(); }

    template <typename T>
    inline bool Tree<T>::empty() const { return _size == 0; }

    template <typename T>
    inline typename Tree<T>::Rank Tree<T>::size() const { return _size; }

    template <typename T>
    inline Shared_ptr<TreeNode<T>> Tree<T>::root() const { return _root; }

    template <typename T>
    void Tree<T>::update_height_above(Shared_ptr<TreeNode<T>> node, const unsigned version)
    {
        Shared_ptr<TreeNode<T>> f = node->father();
        while (f)
        {
            switch (version)
            {
                case 0:
                {
                    if (node->height() >= f->height())
                    {
                        f->height() = node->height() + 1;
                        f = f->father();
                    }
                    else return;
                    break;
                }
                case 1:
                {
                    typename TreeNode<T>::Rank maxChildHeight = 0;
                    Shared_ptr<TreeNode<T>> tallestChild;
                    for (auto &c : f->children())
                    {
                        if (c->height() > maxChildHeight)
                        {
                            maxChildHeight = c->height();
                            tallestChild = c;
                        }
                    }
                    if (f->height() != maxChildHeight + 1)
                    {
                        f->height() = maxChildHeight + 1;
                        f = f->father();
                    }
                    else return;
                    break;
                }
            }

        }
        return;
    }

    template <typename T>
    void Tree<T>::insert_as_child(Shared_ptr<TreeNode<T>> father, Shared_ptr<TreeNode<T>> node)
    {
        try
        {
            if (father->get_root() != _root)
            {
                throw "this father is not a node in this tree";
            }
            if (node->get_root() == root)
            {
                throw "this node is already in this tree";
            }
            father->insert_child(node);
            update_height_above(father, 0);
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
    Tree<T> Tree<T>::remove(Shared_ptr<TreeNode<T>> node)
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
        Shared_ptr<TreeNode<T>> tallestChild, f = node->father();
        typename List<T>::iterator nodePos;

        for (typename List<T>::iterator it = f->children().begin(); it != f->children().end(); ++it)
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
            update_height_above(node, 1);
        }

        // 被删掉的目标结点作为根节点构造新子树
        node->father() = nullptr;
        Tree<T> newTree(node);
        return newTree;
    }

} // CZ

#include "Tree_traversal.h"

#endif // TREE_IMPLEMENTATION_H
