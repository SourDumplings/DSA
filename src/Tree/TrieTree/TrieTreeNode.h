/**
 * @file TrieTreeNode.h
 * @author  SourDumplings(changzheng300@foxmail.com)
 * @brief 前缀树结点，内部对孩子存储是有序的
 * @version 1.0.0
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024 SourDumplings
 * 
 *
 */

#if !defined(TRIE_TREE_NODE_H)
#define TRIE_TREE_NODE_H

#include "../TreeNode.h"
#include "../../Vector/Vector.h"
#include "../../Algorithms/Search.h"

namespace CZ
{
    template <typename T>
    class TrieTreeNode : public TreeNode<T>
    {
    public:
        using Rank = typename TreeNode<T>::Rank;

        TrieTreeNode(const T &data_, TrieTreeNode<T> *pFather_ = nullptr) : TreeNode<T>(data_, pFather_)
        {
        }
        ~TrieTreeNode() override = default;

        const char *get_entity_name() const override
        {
            return "TrieTreeNode";
        }

        /**
         * @brief 插入序列
         *
         * @param [in] seq
         * @param [in] idx 该结点的孩子所需插入的数据索引下标
         * @return Rank 创建的孩子结点数量
         */
        Rank insert_child_by_seq(const Vector<T> &seq, typename Vector<T>::Rank idx);

        /**
         * @brief 孩子结点中查找序列
         * 
         * @param [in] seq 
         * @return TrieTreeNode<T>* 位于串链上的最后一个多兄弟结点指针，如果全都是独子则为该结点的独子的指针，没找到则为 nullptr
         */
        TrieTreeNode<T> *search_seq_in_children(const Vector<T> &seq) const;

    private:
        using TreeNode<T>::insert_child;
    };
}

#include "TrieTreeNode_implementation.h"

#endif // TRIE_TREE_NODE_H
