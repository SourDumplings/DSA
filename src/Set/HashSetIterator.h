/*
 * @Author: SourDumplings
 * @Date: 2023-01-04 18:37:07
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#ifndef HASH_SET_ITERATOR_H
#define HASH_SET_ITERATOR_H

#include "HashSet.h"
#include "../List/List.h"
#include "../Vector/Vector.h"

namespace CZ
{
    template <typename T>
    class HashSet;

    template <typename T>
    class HashSetIterator;

    template <typename T>
    bool operator==(const HashSetIterator<T> &lhs, const HashSetIterator<T> &rhs);
    template <typename T>
    bool operator!=(const HashSetIterator<T> &lhs, const HashSetIterator<T> &rhs);

    template <typename T>
    class HashSetIterator: public AbstractBaseEntity
    {
        friend bool operator==<T>(const HashSetIterator<T> &lhs, const HashSetIterator<T> &rhs);
        friend bool operator!=<T>(const HashSetIterator<T> &lhs, const HashSetIterator<T> &rhs);

    public:
        typedef bi_iterator_tag iterator_category;

        HashSetIterator(const HashSet<T> *pHashSet_, typename Vector<List<T>>::Rank bucketIndex_, ListIterator<T> listIterator_): _pHashSet(pHashSet_), _bucketIndex(bucketIndex_), _listIterator(listIterator_)
        {
            ASSERT_DEBUG(pHashSet_, "pHashSet_ is nullptr");
            ASSERT_DEBUG(bucketIndex_ < pHashSet_->table_size(), "Wrong bucketIndex_ %u, pTable_->size() = %u", bucketIndex_, pHashSet_->table_size());
        }

        const T &operator*() const
        {
            return *_listIterator;
        }
        const T *operator->() const
        {
            return &(*_listIterator);
        }

        HashSetIterator<T> &operator++()
        {
            ASSERT_RELEASE(*this != _pHashSet->end(), "Error from HashSetIterator::operator++: cannot move forward from table end iterator.");

            ++_listIterator;

            if (_bucketIndex == _pHashSet->_lastNonEmptyBucketIndex)
            {
                // 当前桶已经是最后一个非空桶
                return *this;
            }

            if (_listIterator != (_pHashSet->_table)[_bucketIndex].end())
            {
                // 不需要换桶
                return *this;
            }

            // 找到下一个非空桶
            do
            {
                ++_bucketIndex;
            } while (*this != _pHashSet->end() && (_pHashSet->_table)[_bucketIndex].empty());

            if (*this == _pHashSet->end())
            {
                // 已经到表的尾后迭代器了
                return *this;
            }

            // 找到了非空桶，返回指向第一个元素的迭代器即可
            _listIterator = (_pHashSet->_table)[_bucketIndex].begin();
            return *this;
        }

        HashSetIterator<T> operator++(int)
        {
            HashSetIterator<T> temp = *this;
            ++(*this);
            return temp;
        }

        HashSetIterator<T> &operator--()
        {
            ASSERT_RELEASE(*this != _pHashSet->begin(), "Error from HashSetIterator::operator++: cannot move backward from table begin iterator.");

            if (_listIterator != (_pHashSet->_table)[_bucketIndex].begin())
            {
                // 不需要换桶
                --_listIterator;
                return *this;
            }

            ASSERT_DEBUG(_pHashSet->_firstNonEmptyBucketIndex < _bucketIndex, "this bucket %d is already first nonempty bucket, cannot move forward.", _bucketIndex);

            // 找到上一个非空桶
            do
            {
                --_bucketIndex;
            } while (*this != _pHashSet->begin() && (_pHashSet->_table)[_bucketIndex].empty());

            // 找到了上一个非空桶，返回指向最后一个元素的迭代器即可
            _listIterator = --((_pHashSet->_table)[_bucketIndex].end());
            return *this;
        }

        HashSetIterator<T> operator--(int)
        {
            HashSetIterator<T> temp = *this;
            --(*this);
            return temp;
        }

        ListNode<T> *get() {
            return _listIterator.get();
        }
        ListNode<T> *get() const {
            return _listIterator.get();
        }

        operator const ListIterator<T>() const
        {
            return _listIterator;
        }

        operator ListIterator<T>() {
            return _listIterator;
        }

        const char *c_str() const override
        {
            std::ostringstream oss;
            oss << this->get_entity_name() << "(" << *_listIterator << ")";
            return this->get_c_str_from_stream(oss);
        }

        HashRank hash() const override
        {
            return (Hash<const HashSet<T> *>()(_pHashSet) + Hash<T>()(*_listIterator)) % CZ_MAX_HASH_VALUE;
        }

        const char *get_entity_name() const override
        {
            return "HashSetIterator";
        }

    private:
        const HashSet<T> *_pHashSet;              // 对应的哈希表指针
        typename Vector<List<T>>::Rank _bucketIndex; // 桶索引
        ListIterator<T> _listIterator;               // 链表迭代器
    };

    template <typename T>
    bool operator==(const HashSetIterator<T> &lhs, const HashSetIterator<T> &rhs)
    {
        return lhs._pHashSet == rhs._pHashSet && lhs._bucketIndex == rhs._bucketIndex && lhs._listIterator == rhs._listIterator;
    }

    template <typename T>
    bool operator!=(const HashSetIterator<T> &lhs, const HashSetIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }
} // namespace CZ

#endif