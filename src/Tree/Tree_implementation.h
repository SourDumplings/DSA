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

#include <iostream>
#include <utility>

namespace CZ
{
    template <typename T>
    Tree<T>::Tree(std::nullptr_t) : Tree<T>() {}

    template <typename T>
    Tree<T>::Tree(TreeNode<T> *pRoot_) : _pRoot(pRoot_)
    {
        if (pRoot_)
        {
            _size = pRoot_->get_size();
        }
        else
        {
            _size = 0;
        }
        // std::cout << "Tree constructor" << std::endl;
    }

    template <typename T>
    void Tree<T>::clear()
    {
        if (_pRoot)
        {
            delete _pRoot;
            _pRoot = nullptr;
        }
        _size = 0;
    }

    template <typename T>
    TreeNode<T> *Tree<T>::copy_from(TreeNode<T> *pRoot)
    {
        if (pRoot == nullptr)
        {
            return nullptr;
        }
        TreeNode<T> *copiedRoot = new TreeNode<T>(pRoot->data(), nullptr);
        for (auto &c : pRoot->children())
        {
            TreeNode<T> *child = copy_from(c);
            if (child)
            {
                child->set_father(copiedRoot);
            }
            copiedRoot->children().push_back(child);
        }
        return copiedRoot;
    }

    template <typename T>
    Tree<T>::Tree(const Tree<T> &t) : _pRoot(copy_from(t._pRoot)), _size(t._size) {}

    template <typename T>
    Tree<T>::Tree(Tree<T> &&t) noexcept : _pRoot(t._pRoot), _size(t._size)
    {
        t._pRoot = nullptr;
        t._size = 0;
    }

    template <typename T>
    Tree<T>::~Tree() { clear(); }

    template <typename T>
    inline typename Tree<T>::Rank Tree<T>::size() const { return _size; }

    template <typename T>
    inline TreeNode<T> *Tree<T>::root() const { return _pRoot; }

    template <typename T>
    inline typename Tree<T>::Rank Tree<T>::height() const
    {
        return _pRoot ? _pRoot->height() : 0;
    }

    template <typename T>
    inline bool Tree<T>::has_this_node(const TreeNode<T> *node) const
    {
        return _pRoot == node->get_root();
    }

    template <typename T>
    typename Tree<T>::Rank Tree<T>::depth(const TreeNode<T> *node) const
    {
        if (!node->father())
        {
            ASSERT_DEBUG(node == _pRoot, "Error from Tree depth: this node is not in this tree");
            return 1;
        }
        return depth(node->father()) + 1;
    }

    template <typename T>
    TreeNode<T> *Tree<T>::LCA(TreeNode<T> *a, TreeNode<T> *b) const
    {
        Rank dA, dB;
        dA = depth(a);
        dB = depth(b);

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
        while (dL != dH && l->father() != h)
        {
            --dL;
            l = l->father();
        }
        // 然后一起上升，啥时候父亲相等了就是lca了
        while (l->father() != h && l->father() != h->father())
        {
            l = l->father();
            h = h->father();
        }
        return l->father();
    }

    template <typename T>
    void Tree<T>::insert(TreeNode<T> *pFather, TreeNode<T> *pNode)
    {
        ASSERT_DEBUG(pFather, "father is nullptr, cannot be a father");
        ASSERT_DEBUG(pNode, "node is nullptr, cannot be a child");

        if (_pRoot)
        {
            ASSERT_DEBUG(pFather->get_root() == _pRoot, "this father is not a node in this tree");
            pFather->insert_child(pNode);
        }
        else
        {
            ASSERT_DEBUG(pFather == nullptr, "root node cannot have a father");
            _pRoot = pNode;
        }
        _size += pNode->get_size();
    }

    template <typename T>
    TreeNode<T> *Tree<T>::secede(TreeNode<T> *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        if (pNode == _pRoot)
        {
            _pRoot = nullptr;
            _size = 0;
            return pNode;
        }

        ASSERT_DEBUG(pNode->get_root() == _pRoot, "this node is not in this tree");

        TreeNode<T> *f = pNode->father();
        typename List<TreeNode<T> *>::Iterator nodePos;

        // 删掉目标结点
        if (f)
        {
            typename List<TreeNode<T> *>::Rank removedChildrenNum = f->children().remove(pNode);
            ASSERT_RELEASE(removedChildrenNum == 1, "error remove child node");
        }
        else
        {
            // 说明是摘除 root 结点
            ASSERT_DEBUG(pNode == _pRoot, "wrong node pointer");
            _pRoot = nullptr;
        }

        typename TreeNode<T>::Rank sizeLess = pNode->get_size();
        _size -= sizeLess;

        // 被删掉的目标结点解除其与父亲的关系
        pNode->set_father(nullptr);

        return pNode;
    }

    template <typename T>
    void Tree<T>::update_size()
    {
        if (_pRoot)
        {
            _size = _pRoot->get_size();
        }
        else
            _size = 0;
    }

    template <typename T>
    void Tree<T>::OutPut::operator()(const T &data) const
    {
        std::cout << data << " ";
    }

    template <typename T>
    Tree<T> &Tree<T>::operator=(const Tree<T> &t)
    {
        if (&t != this)
        {
            _pRoot = copy_from(t._pRoot);
            _size = t._size;
        }
        return *this;
    }

    template <typename T>
    Tree<T> &Tree<T>::operator=(Tree<T> &&t) noexcept
    {
        if (&t != this)
        {
            _pRoot = t._pRoot;
            _size = t._size;
            t._pRoot = nullptr;
            t._size = 0;
        }
        return *this;
    }

    template <typename T>
    inline bool operator==(const Tree<T> &lhs, const Tree<T> &rhs)
    {
        if (lhs._pRoot == nullptr)
        {
            return rhs._pRoot == nullptr;
        }
        if (rhs._pRoot == nullptr)
        {
            return lhs._pRoot == nullptr;
        }

        return *(lhs._pRoot) == *(rhs._pRoot);
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
    const char *Tree<T>::get_entity_name() const
    {
        return "Tree";
    }

    template <typename T>
    HashRank Tree<T>::hash() const
    {
        HashRank res = Hash<CZString>()(get_entity_name());
        if (_pRoot)
        {
            res = (res + Hash<TreeNode<T>>()(*_pRoot)) % CZ_MAX_HASH_VALUE;
        }
        return res;
    }

    template <typename T>
    const char *Tree<T>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "[";
        Rank count = 0;
        level_order_traversal(_pRoot, [&](const T &data)
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
