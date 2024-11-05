/*
 @Date    : 2018-06-01 09:01:48
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
并查集类模板
 */

#ifndef UNION_FIND_SET_H
#define UNION_FIND_SET_H

#include <initializer_list>
#include "../Base/AbstractBaseContainer.h"
#include "../Tree/Tree.h"

namespace CZ
{
    template <typename T>
    class UnionFindSet : public AbstractBaseContainer<T>
    {
    public:
        using UnionFindSetNode = TreeNode<T>;
        using Rank = typename Tree<T>::Rank;

        UnionFindSet(UnionFindSetNode *root = nullptr);
        UnionFindSet(const std::initializer_list<T> &l);

        Rank size() const override;
        UnionFindSetNode* root() const;
        bool is_family(const UnionFindSetNode *node) const;
        void print_info(const char *name = "") const;

        static bool are_family(const UnionFindSetNode *node1, const UnionFindSetNode *node2);

        void insert(UnionFindSetNode *newNode);
        void insert(const T &newData);
        void insert(T &&newData);
        UnionFindSetNode* remove(UnionFindSetNode *node);
        void clear() override;
        void merge(UnionFindSet<T> &&u);

        static UnionFindSetNode* merge(UnionFindSetNode *node1, UnionFindSetNode *node2);

        const char *get_entity_name() const override;
        const char *c_str() const override;
        HashRank hash() const override;
    private:
        Tree<T> _family;
    };
} // CZ

#include "UnionFindSet_implementation.h"

#endif // UNION_FIND_SET_H
