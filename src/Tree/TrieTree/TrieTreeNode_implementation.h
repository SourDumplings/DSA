#if !defined(TRIE_TREE_NODE_IMPLEMENTATION_H)
#define TRIE_TREE_NODE_IMPLEMENTATION_H

#include "TrieTreeNode.h"

namespace DSA
{
    template <typename T>
    typename TrieTreeNode<T>::Rank TrieTreeNode<T>::insert_child_by_seq(const Vector<T> &seq, typename Vector<T>::Rank idx)
    {
        ASSERT_DEBUG(idx <= seq.size(), "Wrong idx: %u, seq size: %u", idx, seq.size());

        if (idx == seq.size())
        {
            return 0;
        }

        const T &targetData = seq[idx];
        typename List<TreeNode<T> *>::Iterator it = this->children().begin();
        for (; it != this->children().end() && (*it)->data() < targetData; ++it);
        if (it == this->children().end()
            || targetData < (*it)->data()
        )
        {
            // 需要创建新孩子结点
            TrieTreeNode<T> *pNewChild = new TrieTreeNode<T>(targetData);
            pNewChild->set_father(this);
            this->children().insert(it, pNewChild);
            return 1 + pNewChild->insert_child_by_seq(seq, idx + 1);
        }

        // 孩子中已有目标数据，不需要创建新的孩子结点
        return dynamic_cast<TrieTreeNode<T>*>(*it)->insert_child_by_seq(seq, idx + 1);
    }

    template <typename T>
    TrieTreeNode<T> *TrieTreeNode<T>::search_seq_in_children(const Vector<T> &seq) const
    {
        ASSERT_RELEASE(!seq.empty(), "Empty seq!");

        TreeNode<T> *ret = nullptr;
        const TreeNode<T> *pFather = this;
        for (const T &targetData : seq)
        {
            if (pFather->children().empty())
            {
                return nullptr;
            }
            for (const TreeNode<T> *pChild : pFather->children())
            {
                if (pChild->data() == targetData)
                {
                    if (pChild->has_brothers()
                        || pFather == this
                    )
                    {
                        ret = const_cast<TreeNode<T>*>(pChild);
                    }
                    pFather = pChild;
                    break;
                }
                else if (targetData < pChild->data())
                {
                    return nullptr;
                }
            }
        }
        
        return dynamic_cast<TrieTreeNode<T>*>(ret);
    }
}

#endif // TRIE_TREE_NODE_IMPLEMENTATION_H
