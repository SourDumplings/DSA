/*
 @Date    : 2018-06-01 09:16:39
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
并查集类模板的实现
 */

#ifndef UNION_FIND_SET_IMPLEMENTATION_H
#define UNION_FIND_SET_IMPLEMENTATION_H

#include "UnionFindSet.h"

#include <utility>
#include <iostream>
#include <cstdio>

namespace CZ
{
    template <typename T>
    UnionFindSet<T>::UnionFindSet(UnionFindSetNode *root) : _family(root) {}

    template <typename T>
    UnionFindSet<T>::UnionFindSet(const std::initializer_list<T> &l) : _family(new UnionFindSetNode(*l.begin()))
    {
        for (auto it = l.begin() + 1; it != l.end(); ++it)
        {
            _family.insert(_family.root(), new UnionFindSetNode(*it));
        }
    }

    template <typename T>
    inline typename UnionFindSet<T>::Rank UnionFindSet<T>::size() const { return _family.size(); }

    template <typename T>
    inline typename UnionFindSet<T>::UnionFindSetNode *UnionFindSet<T>::root() const
    {
        return _family.root();
    }

    template <typename T>
    inline bool UnionFindSet<T>::is_family(const UnionFindSetNode *node) const
    {
        return node->get_root() == root();
    }

    template <typename T>
    void UnionFindSet<T>::print_info(const char *name) const
    {
        printf("for UnionFindSet %s:\n", name);
        if (root())
        {
            std::cout << "root is " << root()->data() << ", size is " << size() << std::endl;
            printf("contains: ");
            std::cout << root()->data();
            for (auto &c : root()->children())
            {
                std::cout << " " << c->data();
            }
        }
        else
            printf("It is empty.");
        printf("\n\n");
        return;
    }

    template <typename T>
    inline bool UnionFindSet<T>::are_family(const UnionFindSetNode *node1, const UnionFindSetNode *node2)
    {
        return node1->get_root() == node2->get_root();
    }

    template <typename T>
    inline void UnionFindSet<T>::insert(UnionFindSetNode *newNode)
    {
        return _family.insert(root(), newNode);
    }

    template <typename T>
    inline void UnionFindSet<T>::insert(const T &newData)
    {
        return _family.insert(root(), new UnionFindSetNode(newData));
    }

    template <typename T>
    inline void UnionFindSet<T>::insert(T &&newData)
    {
        return _family.insert(root(), new UnionFindSetNode(std::move(newData)));
    }

    template <typename T>
    inline typename UnionFindSet<T>::UnionFindSetNode *UnionFindSet<T>::remove(UnionFindSetNode *node)
    {
        return _family.secede(node);
    }

    template <typename T>
    inline void UnionFindSet<T>::clear() { return _family.clear(); }

    template <typename T>
    void UnionFindSet<T>::merge(UnionFindSet<T> &&u)
    {
        if (this->empty())
        {
            _family = std::move(u._family);
        }
        else
        {
            for (auto &c : u._family.root()->children())
            {
                c->father() = nullptr;
                _family.insert(root(), c);
            }
            _family.insert(root(), u._family.root());
            u._family.root() = nullptr;
            u._family.clear();
        }
        return;
    }

    template <typename T>
    typename UnionFindSet<T>::UnionFindSetNode *UnionFindSet<T>::merge(UnionFindSetNode *node1,
                                                                       UnionFindSetNode *node2)
    {
        UnionFindSetNode *root1 = node1->get_root(), *root2 = node2->get_root();
        if (root1 != root2)
        {
            UnionFindSetNode *father = root1, *child = root2;
            if (root1->get_size() < root2->get_size())
            {
                father = root2;
                child = root1;
            }
            for (auto &c : child->children())
            {
                father->insert_child(c);
            }
            father->insert_child(child);
            return father;
        }
        else
            return root1;
    }

    template <typename T>
    const char *UnionFindSet<T>::get_entity_name() const
    {
        return "UnionFindSet";
    }

    template <typename T>
    const char *UnionFindSet<T>::c_str() const
    {
        std::ostringstream oss;
        oss << this->get_entity_name() << "[";
        if (root())
        {
            oss << "<" << root()->data() << ">: ";
            Rank count = 0;
            for (const TreeNode<T> *pC : root()->children())
            {
                if (pC == nullptr)
                {
                    continue;
                }
                
                if (0 < count)
                {
                    oss << ", ";
                }
                oss << pC->data();
                ++count;
            }
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T>
    HashRank UnionFindSet<T>::hash() const
    {
        return (Hash<CZString>()(get_entity_name()) + _family.hash()) % CZ_MAX_HASH_VALUE;
    }

} // CZ

#endif // UNION_FIND_SET_IMPLEMENTATION_H
