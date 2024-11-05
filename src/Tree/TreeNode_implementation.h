/*
 @Date    : 2018-05-25 15:43:22
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树结点类模板的实现
 */

#ifndef TREE_NODE_IMPLEMENTATION_H
#define TREE_NODE_IMPLEMENTATION_H

#include "TreeNode.h"

#include "../Algorithms/Max.h"
#include "../CZString/CZString.h"
#include <cstdio>
#include <iostream>
#include <sstream>

namespace CZ
{
    template <typename T>
    TreeNode<T>::TreeNode(const T &data_, TreeNode<T> *father_) : _data(data_), _father(father_)
    {
        if (_father)
        {
            _father->insert_child(this);
        }
    }

    template <typename T>
    TreeNode<T>::~TreeNode()
    {
        for (TreeNode<T> *pC : _children)
        {
            if (pC)
            {
                delete pC;
            }
        }
    }

    template <typename T>
    inline TreeNode<T> *TreeNode<T>::father() const
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
        ASSERT_DEBUG(!_children.empty(), "no children");
        return _children.front();
    }

    template <typename T>
    inline const T &TreeNode<T>::data() const
    {
        return _data;
    }

    template <typename T>
    inline T &TreeNode<T>::data()
    {
        return _data;
    }

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
    typename TreeNode<T>::Rank TreeNode<T>::height() const
    {
        Rank maxChildHeight = 0;
        for (const TreeNode<T> *pC : _children)
        {
            if (pC)
            {
                maxChildHeight = Max(maxChildHeight, pC->height());
            }
        }
        return maxChildHeight + 1;
    }

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
    TreeNode<T> *TreeNode<T>::insert_child(TreeNode<T> *pNode)
    {
        _children.push_back(pNode);
        pNode->_father = this;
        return pNode;
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
#ifdef DEBUG
        std::ostringstream oss;
        oss << get_entity_name() << "(" << _data << ")";
        return this->get_c_str_from_stream(oss);
#else
        return this->get_entity_name();
#endif
    }

    template <typename T>
    HashRank TreeNode<T>::hash() const
    {
        // 树结点的哈希是综合了该结点的数据、孩子多少、结点高度和所有子结点的哈希值
        // 即树结点的哈希值由结点的数据和结构两方面决定
        HashRank res = Hash<CZString>()(get_entity_name()) + _children.size();
        for (TreeNode<T> *const &pc : _children)
        {
            if (pc)
            {
                res = (res + Hash<TreeNode<T>>()(*pc)) % CZ_MAX_HASH_VALUE;
            }
        }
        return res;
    }

    template <typename T>
    TreeNode<T> *TreeNode<T>::set_father(TreeNode<T> *pNode)
    {
        TreeNode<T> *pOldFather = _father;
        _father = pNode;
        return pOldFather;
    }

    template <typename T>
    TreeNode<T> *TreeNode<T>::search_data_in_children(const T &data_) const
    {
        for (TreeNode<T> *pChild : children())
        {
            if (pChild == nullptr)
            {
                continue;
            }

            if (pChild->data() == data_)
            {
                return pChild;
            }
            
            TreeNode<T> *res = pChild->search_data_in_children(data_);
            if (res)
            {
                return res;
            }
        }
        return nullptr;
    }

    template <typename T>
    bool TreeNode<T>::has_brothers() const
    {
        if (father() == nullptr)
        {
            return false;
        }
        return 1 < father()->children().size();
    }
} // CZ

#endif // TREE_NODE_IMPLEMENTATION_H
