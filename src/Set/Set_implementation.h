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
    Set<T>::Set() : _T(nullptr, false) {}

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
    Set<T>::Set(const It &begin, const It &end) : Set() { _construct_from(begin, end); }

    template <typename T>
    Set<T>::Set(const T *begin, const T *end) : Set() { _construct_from(begin, end); }

    template <typename T>
    Set<T>::Set(const std::initializer_list<T> &l) : Set(l.begin(), l.end()) {}

    template <typename T>
    Set<T>::Set(const Set<T> &s) { _construct_from(s.begin(), s.end()); }

    template <typename T>
    Set<T>::Set(Set<T> &&s) { _T = std::move(s._T); }

    template <typename T>
    inline typename Set<T>::Rank Set<T>::size() const { return _T.size(); }

    template <typename T>
    inline bool Set<T>::empty() const { return _T.empty(); }

    template <typename T>
    inline bool Set<T>::contains(const T &value) const
    {
        return _T.search(value);
    }

    template <typename T>
    inline bool Set<T>::insert(const T &value)
    {
        return _T.insert(value);
    }

    template <typename T>
    bool Set<T>::remove(const T &value, bool nonexcept)
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
                printf("Error from Set remove: this value is not in this set\n");
                throw std::exception();
            }
        }
        return true;
    }

    template <typename T>
    inline void Set<T>::clear() { _T.clear(); }

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
            if (s2.contains(*it))
            {
                ret.insert(*it);
            }
        }
        return ret;
    }

    template <typename T>
    Set<T>& Set<T>::operator=(const Set<T> &s)
    {
        if (&s != this)
        {
            _T = s._T;
        }
        return *this;
    }

    template <typename T>
    Set<T>& Set<T>::operator=(Set<T> &&s)
    {
        if (&s != this)
        {
            _T = std::move(s._T);
        }
        return *this;
    }
} // CZ

#endif // SET_IMPLEMENTATION_H