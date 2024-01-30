#if !defined(TRIE_TREE_IMPLEMENTATION_H)
#define TRIE_TREE_IMPLEMENTATION_H

#include "TrieTree.h"

namespace CZ
{
    template <typename T>
    TrieTree<T>::TrieTree() : Tree<T>(nullptr)
    {
    }

    template <typename T>
    TrieTree<T>::TrieTree(const Vector<T> &seq) : TrieTree<T>()
    {
        insert_seq(seq);
    }

    template <typename T>
    typename TrieTree<T>::Rank TrieTree<T>::insert_seq(const Vector<T> &seq)
    {
        if (seq.empty())
        {
            return 0;
        }

        if (this->empty())
        {
            this->_pRoot = new TrieTreeNode<T>(T());
            this->_size = 1;
        }

        Rank res = 0;
        // TrieTreeNode<T> *pRoot = dynamic_cast<TrieTreeNode<T>*>(this->root());
        TrieTreeNode<T> *pRoot = reinterpret_cast<TrieTreeNode<T>*>(this->root());
        res = pRoot->insert_child_by_seq(seq, 0);
        this->_size += res;
        return res;
    }

    template <typename T>
    TrieTreeNode<T> *TrieTree<T>::search_seq(const Vector<T> &seq) const
    {
        ASSERT_RELEASE(!seq.empty(), "Empty seq!");
        if (this->empty())
        {
            return nullptr;
        }

        // const TrieTreeNode<T> *pRoot = dynamic_cast<const TrieTreeNode<T>*>(this->root());
        const TrieTreeNode<T> *pRoot = reinterpret_cast<const TrieTreeNode<T>*>(this->root());
        return pRoot->search_seq_in_children(seq);
    }

    template <typename T>
    typename TrieTree<T>::Rank TrieTree<T>::remove_seq(const Vector<T> &seq)
    {
        TrieTreeNode<T> *pNode = search_seq(seq);
        if (pNode == nullptr)
        {
            return 0;
        }

        pNode = dynamic_cast<TrieTreeNode<T>*>(this->secede(pNode));
        Rank res = pNode->get_size();
        delete pNode;
        return res;
    }
}


#endif // TRIE_TREE_IMPLEMENTATION_H
