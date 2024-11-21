/*
 @Date    : 2018-08-12 22:18:48
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
集合迭代器类模板
 */

#ifndef TREE_SET_ITERATOR_H
#define TREE_SET_ITERATOR_H

#include "../Base/AbstractBaseEntity.h"
#include "../Iterator/BiIterator.h"
#include "../Tree/BinTree/RedBlackTreeNode.h"

namespace DSA
{
    template <typename T>
    class TreeSetIterator;

    template <typename T>
    bool operator==(const TreeSetIterator<T> &lhs, const TreeSetIterator<T> &rhs);
    template <typename T>
    bool operator!=(const TreeSetIterator<T> &lhs, const TreeSetIterator<T> &rhs);

    template <typename T>
    class TreeSetIterator : public AbstractBaseEntity
    {
        friend bool operator==<T>(const TreeSetIterator<T> &lhs, const TreeSetIterator<T> &rhs);
        friend bool operator!=<T>(const TreeSetIterator<T> &lhs, const TreeSetIterator<T> &rhs);

    public:
        typedef bi_iterator_tag iterator_category;

        // 构造函数
        // 如果是尾后迭代器，isEnd 为 true，随便传一个 node 的指针即可
        TreeSetIterator(RedBlackTreeNode<T> *pNode_, bool isEnd_, const RedBlackTree<T> *pRBT_) : _it(pNode_), _isEnd(isEnd_), _pRBT(pRBT_) {}

        // 操作符
        const T &operator*() const
        {
            return _it->data();
        }
        T *operator->()
        {
            return const_cast<T *>(&(_it->data()));
        }
        const T *operator->() const
        {
            return &(_it->data());
        }

        TreeSetIterator<T> &operator++()
        {
            ASSERT_DEBUG(!_isEnd, "Error from TreeSetIterator::operator++: cannot move forward from end iterator.");

            if (!_it->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _it = BiIterator<RedBlackTreeNode<T>>(dynamic_cast<RedBlackTreeNode<T> *>(_pRBT->root()));
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(dynamic_cast<RedBlackTreeNode<T> *>(_it->next()));
            }
            return *this;
        }
        TreeSetIterator<T> operator++(int)
        {
            ASSERT_DEBUG(!_isEnd, "Error from TreeSetIterator::operator++: cannot move forward from end iterator.");

            TreeSetIterator<T> temp = *this;
            if (!_it->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _it = BiIterator<RedBlackTreeNode<T>>(dynamic_cast<RedBlackTreeNode<T> *>(_pRBT->root()));
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(dynamic_cast<RedBlackTreeNode<T> *>(_it->next()));
            }
            return temp;
        }
        TreeSetIterator<T> &operator--()
        {
            if (_isEnd)
            {
                _it = BiIterator<RedBlackTreeNode<T>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(dynamic_cast<RedBlackTreeNode<T> *>(_it->prev()));
            }
            return *this;
        }
        TreeSetIterator<T> operator--(int)
        {
            TreeSetIterator<T> temp = *this;
            if (_isEnd)
            {
                _it = BiIterator<RedBlackTreeNode<T>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<T>>(dynamic_cast<RedBlackTreeNode<T> *>(_it->prev()));
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

        virtual const char *c_str() const
        {
            std::ostringstream oss;
            oss << this->get_entity_name() << "(" << *_it << ")";
            return this->get_c_str_from_stream(oss);
        }

        HashRank hash() const override
        {
            return (Hash<RedBlackTreeNode<T>>()(*_it) + Hash<bool>()(_isEnd) + Hash<const RedBlackTree<T> *>()(_pRBT)) % DSA_MAX_HASH_VALUE;
        }

        const char *get_entity_name() const override
        {
            return "TreeSetIterator";
        }

    private:
        BiIterator<RedBlackTreeNode<T>> _it;
        bool _isEnd;                  // 是否是尾后迭代器
        const RedBlackTree<T> *_pRBT; // 对应的红黑树指针

        RedBlackTreeNode<T> *lastNode() const
        {
            RedBlackTreeNode<T> *pLastNode = dynamic_cast<RedBlackTreeNode<T> *>(_pRBT->root());
            while (pLastNode->right_child())
            {
                pLastNode = dynamic_cast<RedBlackTreeNode<T> *>(pLastNode->right_child());
            }
            return pLastNode;
        }
    };

    template <typename T>
    bool operator==(const TreeSetIterator<T> &lhs, const TreeSetIterator<T> &rhs)
    {
        return lhs._it == rhs._it && lhs._pRBT == rhs._pRBT && lhs._isEnd == rhs._isEnd;
    }
    template <typename T>
    bool operator!=(const TreeSetIterator<T> &lhs, const TreeSetIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }
} // DSA

#endif // TREE_TreeSET_ITERATOR_H
