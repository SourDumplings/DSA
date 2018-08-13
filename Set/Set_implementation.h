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
            insert(*it, true);
        }
        return;
    }

    template <typename T>
    template <typename It>
    Set<T>::Set(const It &begin, const It &end) { _construct_from(begin, end); }

    template <typename T>
    Set<T>::Set(T *begin, T *end) { _construct_from(begin, end); }

    template <typename T>
    Set<T>::Set(const std::initializer_list<T> &l): Set(l.begin(), l.end()) {}

    template <typename T>
    inline typename Set<T>::Rank Set<T>::size() const { return _T.size(); }

    template <typename T>
    inline bool Set<T>::empty() const { return _T.empty(); }

    template <typename T>
    inline bool Set<T>::has_this_element(const T &value) const
    { return _T.search(value); }

    template <typename T>
    bool Set<T>::insert(const T &value, bool nonexcept)
    {
        if (!_T.search(value))
        {
            _T.insert(value);
        }
        else
        {
            if (nonexcept)
            {
                return false;
            }
            else
            {
                printf("Error from Set insert: this value is alreay in this set\n");
                throw std::exception();
            }
        }
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
    typename Set<T>::iterator Set<T>::begin() const
    {
        if (empty())
        {
            return nullptr;
        }

        RedBlackTreeNode<T> *node = _T.root();
        while (node->left_child())
        {
            node = node->left_child();
        }
        return node;
    }

    template <typename T>
    inline typename Set<T>::iterator Set<T>::begin()
    { return static_cast<const Set<T>&>(*this).begin(); }

    template <typename T>
    typename Set<T>::iterator Set<T>::last() const
    {
        if (empty())
        {
            return nullptr;
        }

        RedBlackTreeNode<T> *node = _T.root();
        while (node->right_child())
        {
            node = node->right_child();
        }
        return node;
    }

    template <typename T>
    inline typename Set<T>::iterator Set<T>::last()
    { return static_cast<const Set<T>&>(*this).last(); }

    template <typename T>
    void Set<T>::print_info(const char *name) const
    {
        printf("for set %s, it has %u elements\n", name, size());
        printf("it contains:");
        iterator b = begin(), l = last();
        for (iterator it = b; it.get(); ++it)
        {
            std::cout << " " << *it;
            if (it == l)
            {
                break;
            }
        }
        printf("\n\n");
        return;
    }
} // CZ

#endif // SET_IMPLEMENTATION_H

