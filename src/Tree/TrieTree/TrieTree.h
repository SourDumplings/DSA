/**
 * @file TrieTree.h
 * @author  SourDumplings(changzheng300@foxmail.com)
 * @brief 前缀树，适用于对序列的存储与查找
 * @version 1.0.0
 * @date 2024-01-09
 *
 * @copyright Copyright (c) 2024 SourDumplings
 *
 * 
 * 根结点不存储数据，其对于长度为 L 的串，查询效率为 O(L)
 */

#if !defined(TRIE_TREE_H)
#define TRIE_TREE_H

#include "../Tree.h"
#include "TrieTreeNode.h"
#include "../../Vector/Vector.h"

namespace CZ
{
    template <typename T>
    class TrieTree : public Tree<T>
    {
    public:
        using Rank = typename Tree<T>::Rank;

        TrieTree(std::nullptr_t);
        TrieTree(TrieTreeNode<T>* pRoot = nullptr);
        TrieTree(const TrieTree<T>& t);
        TrieTree(TrieTree<T>&& t) noexcept;

        TrieTree(const Vector<T> &seq);

        ~TrieTree() override = default;

        /**
         * @brief 插入一个序列
         *
         * @param [in] seq
         * @return Rank 创建的树结点数量
         */
        Rank insert_seq(const Vector<T> &seq);

        /**
         * @brief 查找一个前缀序列
         *
         * @param [in] seq
         * @return TrieTreeNode<T>* 位于串链上的第一个多兄弟结点指针，如果全都是独子则为根结点指针
         */
        TrieTreeNode<T> *search_seq(const Vector<T> &seq) const;

        /**
         * @brief 删除前缀序列
         *
         * @param [in] seq
         * @return Rank 被删除的树结点数
         */
        Rank remove_seq(const Vector<T> &seq);

        const char *get_entity_name() const override
        {
            return "TrieTree";
        }

    private:
        using Tree<T>::insert;

        TrieTreeNode<T>* copy_from(TreeNode<T>* pRoot);
    };
}

#include "TrieTree_implementation.h"

#endif // TRIE_TREE_H

