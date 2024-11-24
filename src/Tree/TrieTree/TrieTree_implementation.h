#if !defined(TRIE_TREE_IMPLEMENTATION_H)
#define TRIE_TREE_IMPLEMENTATION_H

#include "TrieTree.h"

namespace DSA
{
    template <typename T>
    TrieTree<T>::TrieTree(std::nullptr_t) : TrieTree<T>()
    {
    }
	
	template <typename T>
	TrieTree<T>::TrieTree(TrieTreeNode<T>* pRoot) : Tree<T>(pRoot)
	{
	}

	template <typename T>
	TrieTree<T>::TrieTree(const TrieTree<T>& t)
	{
		this->_pRoot = copy_from(t.root());
		this->_size = t.size();
	}

	template <typename T>
	TrieTree<T>::TrieTree(TrieTree<T>&& t) noexcept : Tree<T>(t)
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

        pNode = reinterpret_cast<TrieTreeNode<T>*>(this->secede(pNode));
        Rank res = pNode->get_size();
        delete pNode;
        return res;
    }

	template <typename T>
	TrieTreeNode<T>* TrieTree<T>::copy_from(TreeNode<T>* pRoot)
	{
		if (pRoot == nullptr)
		{
			return nullptr;
		}
		TrieTreeNode<T>* copiedRoot = new TrieTreeNode<T>(pRoot->data(), nullptr);
		for (auto& c : pRoot->children())
		{
			TrieTreeNode<T>* pChild = copy_from(c);
			if (pChild)
			{
				pChild->set_father(copiedRoot);
			}
			copiedRoot->children().push_back(pChild);
		}
		return copiedRoot;
	}
}


#endif // TRIE_TREE_IMPLEMENTATION_H
