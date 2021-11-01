/*
 @Date    : 2018-08-12 22:18:48
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
集合迭代器类模板
 */

#ifndef SET_ITERATOR_H
#define SET_ITERATOR_H

#include "../Iterator/BiIterator.h"
#include "../Tree/BinTree/RedBlackTreeNode.h"

namespace CZ
{
    template <typename T>
    class SetIterator;

    template <typename T>
    bool operator==(const SetIterator<T> &lhs, const SetIterator<T> &rhs);
    template <typename T>
    bool operator!=(const SetIterator<T> &lhs, const SetIterator<T> &rhs);

    template <typename T>
    class SetIterator
    {
        friend bool operator==<T>(const SetIterator<T> &lhs, const SetIterator<T> &rhs);
        friend bool operator!=<T>(const SetIterator<T> &lhs, const SetIterator<T> &rhs);
    public:
        typedef bi_iterator_tag iterator_category;

        // 构造函数
        SetIterator(RedBlackTreeNode<T> *node_ = nullptr): _it(node_) {}

        // 操作符
        const T& operator*() const
        { return _it->data(); }
        BiIterator<RedBlackTreeNode<T>> operator->()
        { return _it; }
        const BiIterator<RedBlackTreeNode<T>> operator->() const
        { return _it; }

        SetIterator<T>& operator++()
        {
            _it = BiIterator<RedBlackTreeNode<T>>(_it->next());
            return *this;
        }
        SetIterator<T> operator++(int)
        {
            SetIterator<T> temp = *this;
            _it = BiIterator<RedBlackTreeNode<T>>(_it->next());
            return temp;
        }
        SetIterator<T>& operator--()
        {
            _it = BiIterator<RedBlackTreeNode<T>>(_it->prev());
            return *this;
        }
        SetIterator<T> operator--(int)
        {
            SetIterator<T> temp = *this;
            _it = BiIterator<RedBlackTreeNode<T>>(_it->prev());
            return temp;
        }

        RedBlackTreeNode<T>* get() { return _it.get(); }
        RedBlackTreeNode<T>* get() const { return _it.get(); }

        operator const BiIterator<RedBlackTreeNode<T>>() const
        { return _it; }

        operator BiIterator<RedBlackTreeNode<T>>() { return _it; }

    private:
        BiIterator<RedBlackTreeNode<T>> _it;
    };

    template <typename T>
    bool operator==(const SetIterator<T> &lhs, const SetIterator<T> &rhs)
    {
        return lhs._it == rhs._it;
    }
    template <typename T>
    bool operator!=(const SetIterator<T> &lhs, const SetIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }
} // CZ

#endif // SET_ITERATOR_H

