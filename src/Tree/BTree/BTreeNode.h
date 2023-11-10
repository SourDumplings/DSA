/*
 @Date    : 2018-07-01 21:45:40
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树结点类模板
 */

#ifndef B_TREE_NODE_H
#define B_TREE_NODE_H

#include "../../Base/AbstractBaseEntity.h"
#include "../../CZString/CZString.h"
#include "../../Vector/Vector.h"
#include <cstdio>
#include <iostream>
#include <sstream>

namespace CZ
{
    template <typename T>
    class BTree;

    template <typename T>
    class BTreeNode : public AbstractBaseEntity
    {
        friend class BTree<T>;

    public:
        using Rank = typename BTree<T>::Rank;

        // BTreeNode只能作为根节点创建，初始时有0个关键码和一个空孩子指针
        BTreeNode() : _father(nullptr)
        {
            _children.push_back(nullptr);
        }
        BTreeNode(const T &data, BTreeNode<T> *lc = nullptr, BTreeNode<T> *rc = nullptr) : _father(nullptr)
        {
            _keys.push_back(data);
            _children.push_back(lc);
            _children.push_back(rc);
            if (lc)
                lc->_father = this;
            if (rc)
                rc->_father = this;
        }
        ~BTreeNode() = default;

        void print_info(const char *name = "") const
        {
            printf("for btreenode %s: \n", name);

#ifdef DBEUG
            printf("it contains keys:");
            for (auto &item : _keys)
            {
                std::cout << " " << item;
            }
            printf("\nit has %u children\n\n", _children.size());
#endif

        }

        Rank depth() const;

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

    private:
        Vector<T> _keys; // 存放关键码的列表，长度总比孩子数少1
        // 若B树的阶数为m，每个结点的分支数在区间[上取整(m/2)，m]上，相应的关键码数在[上取整(m/2)-1，m-1]上
        Vector<BTreeNode<T> *> _children; // 孩子向量，其长度总比关键码数多1
        BTreeNode<T> *_father;

        BTreeNode<T> *get_root() const
        {
            BTreeNode<T> *r = this, *f = _father;
            while (f)
            {
                r = f;
                f = f->_father;
            }
            return r;
        }
    };

    template <typename T>
    const char *BTreeNode<T>::get_entity_name() const
    {
        return "BTreeNode";
    }

    template <typename T>
    HashRank BTreeNode<T>::hash() const
    {
        // 树结点的哈希值由其名字、数据列表的哈希值、深度以及子结点的哈希值共同决定
        HashRank res = (Hash<CZString>()(get_entity_name()) + _keys.hash() + depth()) % CZ_MAX_HASH_VALUE;
        for (const BTreeNode<T> *pC : _children)
        {
            if (pC)
            {
                res = (res + pC->hash()) % CZ_MAX_HASH_VALUE;
            }
        }
        return res;
    }

    template <typename T>
    const char *BTreeNode<T>::c_str() const
    {
#ifdef DEBUG
        std::ostringstream oss;
        oss << get_entity_name() << "[";
        for (typename Vector<T>::Rank i = 0; i != _keys.size(); ++i)
        {
            if (0 < i)
            {
                oss << ", ";
            }
            oss << _keys[i];
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
#else
        return this->get_entity_name();
#endif
    }

    template <typename T>
    typename BTreeNode<T>::Rank BTreeNode<T>::depth() const
    {
        Rank res = 1;
        const BTreeNode<T> *p = _father;
        while (p)
        {
            p = p->_father;
            ++res;
        }
        return res;
    }
} // CZ

#endif // B_TREE_NODE_H
