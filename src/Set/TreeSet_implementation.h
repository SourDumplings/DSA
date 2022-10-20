/*
 @Date    : 2018-08-12 21:32:00
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
集合模板实现
 */

#ifndef TREE_SET_IMPLEMENTATION_H
#define TREE_SET_IMPLEMENTATION_H

#include "TreeSet.h"
#include <stdexcept>
#include <cstdio>
#include <iostream>

namespace CZ
{
    template <typename T>
    TreeSet<T>::TreeSet() : _T(nullptr, false) {}

    template <typename T>
    template <typename It>
    void TreeSet<T>::_construct_from(const It &begin, const It &end)
    {
        for (It it = begin; it != end; ++it)
        {
            insert(*it);
        }
        return;
    }

    template <typename T>
    template <typename It>
    TreeSet<T>::TreeSet(const It &begin, const It &end) : TreeSet() { _construct_from(begin, end); }

    template <typename T>
    TreeSet<T>::TreeSet(const T *begin, const T *end) : TreeSet() { _construct_from(begin, end); }

    template <typename T>
    TreeSet<T>::TreeSet(const std::initializer_list<T> &l) : TreeSet(l.begin(), l.end()) {}

    template <typename T>
    TreeSet<T>::TreeSet(const TreeSet<T> &s) : _T(s._T) {}

    template <typename T>
    TreeSet<T>::TreeSet(TreeSet<T> &&s) : _T(std::move(s._T)) {}

    template <typename T>
    inline typename TreeSet<T>::Rank TreeSet<T>::size() const { return _T.size(); }

    template <typename T>
    inline bool TreeSet<T>::empty() const { return _T.empty(); }

    template <typename T>
    inline bool TreeSet<T>::contains(const T &value) const
    {
        return _T.search(value);
    }

    template <typename T>
    inline bool TreeSet<T>::insert(const T &value)
    {
        return _T.insert(value);
    }

    template <typename T>
    bool TreeSet<T>::remove(const T &value, bool nonexcept)
    {
        if (contains(value))
        {
            _T.remove(value);
        }
        else
        {
            if (nonexcept)
            {
                return false;
            }
            else
            {
                printf("Error from TreeSet remove: this value is not in this Treeset\n");
                throw std::exception();
            }
        }
        return true;
    }

    template <typename T>
    inline void TreeSet<T>::clear() { _T.clear(); }

    template <typename T>
    typename TreeSet<T>::Iterator TreeSet<T>::begin() const
    {
        if (empty())
        {
            return Iterator(_T.root(), true, &_T);
        }

        RedBlackTreeNode<T> *pNode = _T.root();
        while (pNode->left_child())
        {
            pNode = pNode->left_child();
        }
        return Iterator(pNode, false, &_T);
    }

    template <typename T>
    inline typename TreeSet<T>::Iterator TreeSet<T>::begin()
    {
        return static_cast<const TreeSet<T> &>(*this).begin();
    }

    template <typename T>
    inline typename TreeSet<T>::Iterator TreeSet<T>::end() const
    {
        return Iterator(_T.root(), true, &_T);
    }

    template <typename T>
    inline typename TreeSet<T>::Iterator TreeSet<T>::end()
    {
        return static_cast<const TreeSet<T> &>(*this).end();
    }

    template <typename T>
    const T &TreeSet<T>::back() const
    {
        if (empty())
        {
            printf("Error from TreeSet::front(): empty Treeset.\n");
            throw std::exception();
        }

        RedBlackTreeNode<T> *pNode = _T.root();
        while (pNode->right_child())
        {
            pNode = pNode->right_child();
        }
        return pNode->data();
    }

    template <typename T>
    inline T &TreeSet<T>::back()
    {
        return const_cast<T &>(static_cast<const TreeSet<T> &>(*this).back());
    }

    template <typename T>
    const T &TreeSet<T>::front() const
    {
        if (empty())
        {
            printf("Error from TreeSet::front(): empty Treeset.\n");
            throw std::exception();
        }

        RedBlackTreeNode<T> *pNode = _T.root();
        while (pNode->left_child())
        {
            pNode = pNode->left_child();
        }
        return pNode->data();
    }

    template <typename T>
    inline T &TreeSet<T>::front()
    {
        return const_cast<T &>(static_cast<const TreeSet<T> &>(*this).front());
    }

    template <typename T>
    void TreeSet<T>::print_info(const char *name) const
    {
        printf("for TreeSet %s, it has %u elements\n", name, size());
        printf("it contains:");
        for (Iterator it = begin(); it != end(); ++it)
        {
            std::cout << " " << *it;
        }

        printf("\n\n");
        return;
    }

    template <typename T>
    TreeSet<T> TreeSet<T>::intersection(const TreeSet<T> &s1, const TreeSet<T> &s2)
    {
        TreeSet<T> ret;
        for (Iterator it = s1.begin(); it != s1.end(); ++it)
        {
            if (s2.contains(*it))
            {
                ret.insert(*it);
            }
        }
        return ret;
    }

    template <typename T>
    TreeSet<T> &TreeSet<T>::operator=(const TreeSet<T> &s)
    {
        if (&s != this)
        {
            _T = s._T;
        }
        return *this;
    }

    template <typename T>
    TreeSet<T> &TreeSet<T>::operator=(TreeSet<T> &&s)
    {
        if (&s != this)
        {
            _T = std::move(s._T);
        }
        return *this;
    }
} // CZ

#endif // TreeSET_IMPLEMENTATION_H