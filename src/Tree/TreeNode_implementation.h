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

#include "../CZString/CZString.h"
#include <stdexcept>
#include <cstdio>
#include <iostream>
#include <sstream>

namespace CZ
{
    template <typename T>
    TreeNode<T>::TreeNode(const T &data_, TreeNode<T> *father_,
                          typename TreeNode<T>::Rank height_) : _data(data_), _height(height_), _father(father_)
    {
        if (_father)
        {
            _father->insert_child(this);
        }
    }

    template <typename T>
    TreeNode<T>::~TreeNode() = default;

    template <typename T>
    inline TreeNode<T> *TreeNode<T>::father() const
    {
        return _father;
    }

    template <typename T>
    inline TreeNode<T> *&TreeNode<T>::father()
    {
        return _father;
    }

    template <typename T>
    TreeNode<T> *TreeNode<T>::get_root() const
    {
        if (!_father)
        {
            return const_cast<TreeNode<T> *>(this);
        }
        TreeNode<T> *r = _father;
        while (r->_father)
        {
            r = r->_father;
        }
        return r;
    }

    template <typename T>
    TreeNode<T> *TreeNode<T>::oldest_child() const
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
    inline const T &TreeNode<T>::data() const { return _data; }

    template <typename T>
    inline T &TreeNode<T>::data() { return _data; }

    template <typename T>
    bool TreeNode<T>::is_leaf() const
    {
        for (auto &c : _children)
        {
            if (c)
            {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    inline bool TreeNode<T>::are_brother(const TreeNode<T> *node1, const TreeNode<T> *node2)
    {
        return node1->_father == node2->_father;
    }

    template <typename T>
    inline const typename TreeNode<T>::Rank &TreeNode<T>::height() const { return _height; }

    template <typename T>
    inline typename TreeNode<T>::Rank &TreeNode<T>::height() { return _height; }

    template <typename T>
    inline const List<TreeNode<T> *> &TreeNode<T>::children() const
    {
        return _children;
    }

    template <typename T>
    inline List<TreeNode<T> *> &TreeNode<T>::children()
    {
        return _children;
    }

    template <typename T>
    void TreeNode<T>::update_height_above(const uint32_t version)
    {
        TreeNode<T> *f = _father;
        switch (version)
        {
        case 0:
        {
            Rank changedChildHeight = _height;
            while (f)
            {
                if (changedChildHeight >= f->_height)
                {
                    changedChildHeight = f->_height = changedChildHeight + 1;
                    f = f->father();
                }
                else
                    return;
            }
            break;
        }
        case 1:
        {
            while (f)
            {
                typename TreeNode<T>::Rank maxChildHeight = 0;
                for (auto &c : f->children())
                {
                    if (c && c->_height > maxChildHeight)
                    {
                        maxChildHeight = c->_height;
                    }
                }

                if (f->_height != maxChildHeight + 1)
                {
                    f->_height = maxChildHeight + 1;
                    f = f->father();
                }
                else
                    return;
            }
            break;
        }
        }
        return;
    }

    template <typename T>
    void TreeNode<T>::insert_child(TreeNode<T> *node)
    {
        _children.push_back(node);
        node->_father = this;
        node->update_height_above(0);
        return;
    }

    template <typename T>
    typename TreeNode<T>::Rank TreeNode<T>::get_size() const
    {
        Rank ret = 1;
        for (auto &c : _children)
        {
            if (c)
            {
                ret += c->get_size();
            }
        }
        return ret;
    }

    template <typename T>
    bool TreeNode<T>::equivalent(const TreeNode<T> &lhs, const TreeNode<T> &rhs)
    {
        if (lhs.data() == rhs.data())
        {
            if (lhs.children().empty() && rhs.children().empty())
            {
                return true;
            }
            else if (!lhs.children().empty() && !rhs.children().empty() &&
                     lhs.children().size() == rhs.children().size())
            {
                for (auto it1 = lhs.children().begin(), it2 = rhs.children().begin();
                     it1 != lhs.children().end(); ++it1, ++it2)
                {
                    if ((!*it1 && *it2) || (*it1 && !*it2))
                    {
                        return false;
                    }
                    else if (*it1 && *it2)
                    {
                        if (!equivalent(**it1, **it2))
                        {
                            return false;
                        }
                    }
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    }

    template <typename T>
    const char *TreeNode<T>::get_entity_name() const
    {
        return "TreeNode";
    }

    template <typename T>
    const char *TreeNode<T>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "(" << _data << ")";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T>
    HashRank TreeNode<T>::hash() const
    {
        // 树结点的哈希是综合了该结点的数据、孩子多少、结点高度和所有子结点的哈希值
        // 即树结点的哈希值由结点的数据和结构两方面决定
        HashRank res = Hash<CZString>()(c_str() + _children.size() + _height);
        for (TreeNode<T> * const &pc : _children)
        {
            if (pc)
            {
                res = (res + Hash<TreeNode<T>>()(*pc)) % CZ_MAX_HASH_VALUE;
            }
        }
        return res;
    }
} // CZ

#endif // TREE_NODE_IMPLEMENTATION_H
