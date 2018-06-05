/*
 @Date    : 2018-06-04 10:34:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板的动态操作
 */

#ifndef BIN_TREE_MODIFICATIONS_H
#define BIN_TREE_MODIFICATIONS_H

#include "BinTree.h"
#include <stdexcept>

namespace CZ
{
    template <typename T>
    void BinTree<T>::insert(TreeNode<T> *father, TreeNode<T> *node)
    {
        return do_insert(dynamic_cast<BinTreeNode<T>*>(father),
            dynamic_cast<BinTreeNode<T>*>(node));
    }

    template <typename T>
    TreeNode<T>* BinTree<T>::remove(TreeNode<T> *node)
    { return do_remove(dynamic_cast<BinTreeNode<T>*>(node)); }

    template <typename T>
    void BinTree<T>::do_insert(BinTreeNode<T> *father, BinTreeNode<T> *node)
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

            if (father->get_root() != Tree<T>::root())
            {
                throw "this father is not a node in this tree";
            }
            if (node->father())
            {
                throw "this node has already had a father";
            }

            if (!father->left_child())
            {
                father->insert_as_left_child(node);
            }
            else if (!father->right_child())
            {
                father->insert_as_right_child(node);
            }
            else
            {
                throw "this father has two children, cannot have more";
            }
            Tree<T>::_size += node->get_size();
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            std::exception();
        }
        return;
    }

    template <typename T>
    BinTreeNode<T>* BinTree<T>::do_remove(BinTreeNode<T> *node)
    {
        if (!node)
        {
            return nullptr;
        }

        try
        {
            if (node->get_root() != Tree<T>::root())
            {
                throw "this node is not in this tree";
            }
            if (node == Tree<T>::root())
            {
                throw "cannot remove root";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }

        BinTreeNode<T> *f = dynamic_cast<BinTreeNode<T>*>(node->father());
        node == f->left_child() ? f->remove_left_child() : f->remove_right_child();

        Tree<T>::_size -= node->get_size();

        return node;
    }
} // CZ

#endif // BIN_TREE_MODIFICATIONS_H


