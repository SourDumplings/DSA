/*
 @Date    : 2018-06-01 09:01:48
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
并查集模板类
 */

#ifndef UNION_FIND_SET_H
#define UNION_FIND_SET_H

#include <initializer_list>
#include "../Tree/Tree.h"

namespace CZ
{
    template <typename T> class UnionFindSet;
    template <typename T> bool operator==(const UnionFindSet<T> &lhs, const UnionFindSet<T> &rhs);
    template <typename T> bool operator!=(const UnionFindSet<T> &lhs, const UnionFindSet<T> &rhs);

    template <typename T>
    class UnionFindSet
    {
        friend bool operator==<T>(const UnionFindSet<T> &lhs, const UnionFindSet<T> &rhs);
        friend bool operator!=<T>(const UnionFindSet<T> &lhs, const UnionFindSet<T> &rhs);
    public:
        using UnionFindSetNode = TreeNode<T>;
        using Rank = typename Tree<T>::Rank;

        UnionFindSet(UnionFindSetNode *root = nullptr);
        UnionFindSet(const std::initializer_list<T> &l);

        Rank size() const;
        bool empty() const;
        UnionFindSetNode* root() const;
        bool is_family(const UnionFindSetNode *node) const;
        void print_info(const char *name = "") const;

        static bool are_family(const UnionFindSetNode *node1, const UnionFindSetNode *node2);

        void insert(UnionFindSetNode *newNode);
        void insert(const T &newData);
        void insert(T &&newData);
        UnionFindSetNode* remove(UnionFindSetNode *node);
        void clear();
        void merge(UnionFindSet<T> &&u);

        static UnionFindSetNode* merge(UnionFindSetNode *node1, UnionFindSetNode *node2);
    private:
        Tree<T> _family;
    };
} // CZ

#include "UnionFindSet_implementation.h"

#endif // UNION_FIND_SET_H
