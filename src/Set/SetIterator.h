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
        // 如果是尾后迭代器，isEnd 为 true，随便传一个 node 的指针即可
        SetIterator(RedBlackTreeNode<T> *pNode_, bool isEnd_, const RedBlackTree<T> *pRBT_) : _it(pNode_), _isEnd(isEnd_), _pRBT(pRBT_) {}

        // 操作符
        const T &operator*() const
        {
            return _it->data();
        }
        BiIterator<RedBlackTreeNode<T>> operator->()
        {
            return _it;
        }
        const BiIterator<RedBlackTreeNode<T>> operator->() const
        {
            return _it;
        }

        SetIterator<T> &operator++()
        {
            if (_isEnd)
            {
                printf("Error from SetIterator::operator++: cannot move forward from end iterator.\n");
                throw std::exception();
            }

            if (!_it->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _it = BiIterator<RedBlackTreeNode<T>>(_pRBT->root());
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(_it->next());
            }
            return *this;
        }
        SetIterator<T> operator++(int)
        {
            if (_isEnd)
            {
                printf("Error from SetIterator::operator++: cannot move forward from end iterator.\n");
                throw std::exception();
            }

            SetIterator<T> temp = *this;
            if (!_it->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _it = BiIterator<RedBlackTreeNode<T>>(_pRBT->root());
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(_it->next());
            }
            return temp;
        }
        SetIterator<T> &operator--()
        {
            if (_isEnd)
            {
                _it = BiIterator<RedBlackTreeNode<T>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(_it->prev());
            }
            return *this;
        }
        SetIterator<T> operator--(int)
        {
            SetIterator<T> temp = *this;
            if (_isEnd)
            {
                _it = BiIterator<RedBlackTreeNode<T>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(_it->prev());
            }
            return temp;
        }

        RedBlackTreeNode<T> *get() { return _it.get(); }
        RedBlackTreeNode<T> *get() const { return _it.get(); }

        operator const BiIterator<RedBlackTreeNode<T>>() const
        {
            return _it;
        }

        operator BiIterator<RedBlackTreeNode<T>>() { return _it; }

    private:
        BiIterator<RedBlackTreeNode<T>> _it;
        bool _isEnd;                  // 是否是尾后迭代器
        const RedBlackTree<T> *_pRBT; // 对应的红黑树指针

        RedBlackTreeNode<T> *lastNode() const
        {
            RedBlackTreeNode<T> *pLastNode = _pRBT->root();
            while (pLastNode->right_child())
            {
                pLastNode = pLastNode->right_child();
            }
            return pLastNode;
        }
    };

    template <typename T>
    bool operator==(const SetIterator<T> &lhs, const SetIterator<T> &rhs)
    {
        return lhs._it == rhs._it && lhs._pRBT == rhs._pRBT && lhs._isEnd == rhs._isEnd;
    }
    template <typename T>
    bool operator!=(const SetIterator<T> &lhs, const SetIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }
} // CZ

#endif // SET_ITERATOR_H
