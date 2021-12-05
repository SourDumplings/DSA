/*
 @Date    : 2018-08-12 21:32:00
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
集合模板实现
 */

#ifndef SET_IMPLEMENTATION_H
#define SET_IMPLEMENTATION_H

#include "Set.h"
#include <stdexcept>
#include <cstdio>
#include <iostream>

namespace CZ
{
    template <typename T>
    Set<T>::Set() = default;

    template <typename T>
    template <typename It>
    void Set<T>::_construct_from(const It &begin, const It &end)
    {
        for (It it = begin; it != end; ++it)
        {
            insert(*it);
        }
        return;
    }

    template <typename T>
    template <typename It>
    Set<T>::Set(const It &begin, const It &end) { _construct_from(begin, end); }

    template <typename T>
    Set<T>::Set(T *begin, T *end) { _construct_from(begin, end); }

    template <typename T>
    Set<T>::Set(const std::initializer_list<T> &l) : Set(l.begin(), l.end()) {}

    template <typename T>
    inline typename Set<T>::Rank Set<T>::size() const { return _T.size(); }

    template <typename T>
    inline bool Set<T>::empty() const { return _T.empty(); }

    template <typename T>
    inline bool Set<T>::has_this_element(const T &value) const
    {
        return _T.search(value);
    }

    template <typename T>
    bool Set<T>::insert(const T &value)
    {
        RedBlackTreeNode<T> *p = _T.search(value);
        if (p)
        {
            return false;
        }

        _T.insert(value);
        return true;
    }

    template <typename T>
    bool Set<T>::remove(const T &value, bool nonexcept)
    {
        if (has_this_element(value))
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
                printf("Error from Set remove: this value is not in this set\n");
                throw std::exception();
            }
        }
        return true;
    }

    template <typename T>
    typename Set<T>::Iterator Set<T>::begin() const
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
    inline typename Set<T>::Iterator Set<T>::begin()
    {
        return static_cast<const Set<T> &>(*this).begin();
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::end() const
    {
        return Iterator(_T.root(), true, &_T);
    }

    template <typename T>
    inline typename Set<T>::Iterator Set<T>::end()
    {
        return static_cast<const Set<T> &>(*this).end();
    }

    template <typename T>
    const T &Set<T>::back() const
    {
        if (empty())
        {
            printf("Error from Set::front(): empty set.\n");
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
    inline T &Set<T>::back()
    {
        return const_cast<T &>(static_cast<const Set<T> &>(*this).back());
    }

    template <typename T>
    const T &Set<T>::front() const
    {
        if (empty())
        {
            printf("Error from Set::front(): empty set.\n");
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
    inline T &Set<T>::front()
    {
        return const_cast<T &>(static_cast<const Set<T> &>(*this).front());
    }

    template <typename T>
    void Set<T>::print_info(const char *name) const
    {
        printf("for set %s, it has %u elements\n", name, size());
        printf("it contains:");
        for (Iterator it = begin(); it != end(); ++it)
        {
            std::cout << " " << *it;
        }

        printf("\n\n");
        return;
    }

    template <typename T>
    Set<T> Set<T>::intersection(const Set<T> &s1, const Set<T> &s2)
    {
        Set<T> ret;
        for (Iterator it = s1.begin(); it != s1.end(); ++it)
        {
            if (s2.has_this_element(*it))
            {
                ret.insert(*it);
            }
        }
        return ret;
    }
} // CZ

#endif // SET_IMPLEMENTATION_H