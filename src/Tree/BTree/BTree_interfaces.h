/*
 @Date    : 2018-07-08 22:26:03
 @Author  : 酸饺子 (sourdumplings@qq.com)
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
#include "../../Queue/Queue.h"

namespace DSA
{
    template <typename T>
    inline typename BTree<T>::Rank BTree<T>::order() const
    {
        return _order;
    }

    template <typename T>
    inline typename BTree<T>::Rank BTree<T>::size() const
    {
        return _size;
    }

    template <typename T>
    inline BTreeNode<T> *BTree<T>::root() const
    {
        return _root;
    }

    template <typename T>
    inline typename BTree<T>::Rank BTree<T>::height() const
    {
        return get_height(_root);
    }

    template <typename T>
    typename BTree<T>::Rank BTree<T>::get_height(BTreeNode<T> *root) const
    {
        if (!root)
        {
            return 0;
        }
        Rank ret = 1;
        for (auto &c : root->_children)
        {
            if (c)
            {
                Rank hc = get_height(c);
                if (ret < hc + 1)
                {
                    ret = hc + 1;
                }
            }
        }
        return ret;
    }

    template <typename T>
    inline typename BTree<T>::Rank BTree<T>::keys_num() const
    {
        return get_keys_num(_root);
    }

    template <typename T>
    typename BTree<T>::Rank BTree<T>::get_keys_num(BTreeNode<T> *v) const
    {
        if (!v)
        {
            return 0;
        }
        Rank ret = 1;
        for (auto &c : v->_children)
        {
            if (c)
            {
                ret += get_keys_num(c);
            }
        }
        return ret;
    }

    template <typename T>
    BTreeNode<T> *BTree<T>::search(const T &data) const
    {
        BTreeNode<T> *v = _root; // 从根结点开始
        _hot = nullptr;
        while (v && !v->_keys.empty())
        {
            // 对结点v的关键码向量进行二分查找，返回不大于data的最后一个元素
            typename Vector<T>::Iterator it =
                Search(v->_keys.begin(), v->_keys.end(), data, BINARY_SEARCH, 2);
            if (it < v->_keys.end() && v->_keys.begin() <= it && *it == data)
            {
                // 找到了该结点
                return v;
            }
            else
            {
                // 否则，转入对应子树逐层查找
                _hot = v;
                v = (v->_children)[it - v->_keys.begin() + 1];
            }
        }
        return nullptr; // 查找失败，抵达外部结点
    }

    template <typename T>
    const char *BTree<T>::c_str() const
    {
#ifdef DEBUG
        std::ostringstream oss;

        oss << get_entity_name() << "[";
        Queue<BTreeNode<T> *> Q;
        if (_root)
            Q.push(_root);
        while (!Q.empty())
        {
            BTreeNode<T> *v = Q.front();
            Q.pop();

            oss << '(';
            bool first = true;
            for (typename Vector<T>::Rank i = 0; i < v->_keys.size(); ++i)
            {
                if (!first)
                {
                    oss << ' ';
                }
                oss << (v->_keys)[i];
                first = false;
                if ((v->_children)[i])
                {
                    Q.push((v->_children)[i]);
                }
            }
            if (v->_children.back())
            {
                Q.push(v->_children.back());
            }
            oss << ')';
            if (!Q.empty())
            {
                oss << ", ";
            }
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
#else
        return this->get_entity_name();
#endif
    }

    template <typename T>
    HashRank BTree<T>::hash() const
    {
        HashRank res = Hash<DSAString>()(get_entity_name()) + _order;
        if (_root)
        {
            res = (res + _root->hash()) % DSA_MAX_HASH_VALUE;
        }

        return res;
    }

    template <typename T>
    const char *BTree<T>::get_entity_name() const
    {
        return "BTree";
    }
} // DSA

#endif // B_TREE_INTERFACES_H
