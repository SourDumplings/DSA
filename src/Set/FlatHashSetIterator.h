/*
 * @Author: SourDumplings
 * @Date: 2023-01-16 19:37:07
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#ifndef FLAT_HASH_SET_ITERATOR_H
#define FLAT_HASH_SET_ITERATOR_H

#include "FlatHashSet.h"
#include "../List/List.h"
#include "../Vector/Vector.h"

namespace CZ
{
    template <typename T>
    class FlatHashSet;

    template <typename T>
    class FlatHashSetIterator;

    template <typename T>
    bool operator==(const FlatHashSetIterator<T> &lhs, const FlatHashSetIterator<T> &rhs);
    template <typename T>
    bool operator!=(const FlatHashSetIterator<T> &lhs, const FlatHashSetIterator<T> &rhs);

    template <typename T>
    class FlatHashSetIterator: public AbstractBaseEntity
    {
        friend bool operator==<T>(const FlatHashSetIterator<T> &lhs, const FlatHashSetIterator<T> &rhs);
        friend bool operator!=<T>(const FlatHashSetIterator<T> &lhs, const FlatHashSetIterator<T> &rhs);

    public:
        typedef bi_iterator_tag iterator_category;

        FlatHashSetIterator(const FlatHashSet<T> *pFlatHashSet_, typename Vector<KVPair<T, bool>>::Rank bucketIndex_): _pFlatHashSet(pFlatHashSet_), _bucketIndex(bucketIndex_)
        {
            ASSERT_DEBUG(pFlatHashSet_, "pFlatHashSet_ is nullptr");
            ASSERT_DEBUG(bucketIndex_ < pFlatHashSet_->table_size(), "Wrong bucketIndex_ %u, pTable_->size() = %u", bucketIndex_, pFlatHashSet_->table_size());
        }

        const T &operator*() const
        {
            return (_pFlatHashSet->_table)[_bucketIndex].key();
        }
        const T *operator->() const
        {
            return &((_pFlatHashSet->_table)[_bucketIndex].key());
        }

        FlatHashSetIterator<T> &operator++()
        {
            ASSERT_RELEASE(*this != _pFlatHashSet->end(), "Error from FlatHashSetIterator::operator++: cannot move forward from table end iterator.");

            for (typename FlatHashSet<T>::Rank i = _bucketIndex; i <= _pFlatHashSet->_lastNonEmptyBucketIndex; ++i)
            {
                if ((_pFlatHashSet->_table)[i].value())
                {
                    _bucketIndex = i;
                    break;
                }
            }

            ASSERT_DEBUG(!(_bucketIndex == _pFlatHashSet->_lastNonEmptyBucketIndex && !(_pFlatHashSet->_table)[_bucketIndex].value()), "Error iterator!");
            return *this;
        }

        FlatHashSetIterator<T> operator++(int)
        {
            FlatHashSetIterator<T> temp = *this;
            ++(*this);
            return temp;
        }

        FlatHashSetIterator<T> &operator--()
        {
            ASSERT_RELEASE(*this != _pFlatHashSet->begin(), "Error from FlatHashSetIterator::operator++: cannot move backward from table begin iterator.");

            for (typename FlatHashSet<T>::Rank i = _bucketIndex; _pFlatHashSet->_firstNonEmptyBucketIndex <= i; --i)
            {
                if ((_pFlatHashSet->_table)[i].value())
                {
                    _bucketIndex = i;
                    break;
                }
            }

            ASSERT_DEBUG(!(_bucketIndex == _pFlatHashSet->_firstNonEmptyBucketIndex && !(_pFlatHashSet->_table)[_bucketIndex].value()), "Error iterator!");
            return *this;
        }

        FlatHashSetIterator<T> operator--(int)
        {
            FlatHashSetIterator<T> temp = *this;
            --(*this);
            return temp;
        }

        KVPair<T, bool> *get()
        {
            return &((_pFlatHashSet->_table)[_bucketIndex]);
        }
        
        KVPair<T, bool> *get() const
        {
            return &((_pFlatHashSet->_table)[_bucketIndex]);
        }

        const char *c_str() const noexcept override
        {
            std::ostringstream oss;
            oss << this->get_entity_name() << "(" << (_pFlatHashSet->_table)[_bucketIndex].key() << ")";
            return this->get_c_str_from_stream(oss);
        }

        HashRank hash() const noexcept override
        {
            return (Hash<const FlatHashSet<T> *>()(_pFlatHashSet) + Hash<typename Vector<KVPair<T, bool>>::Rank>()(_bucketIndex)) % CZ_MAX_HASH_VALUE;
        }

        const char *get_entity_name() const noexcept override
        {
            return "FlatHashSetIterator";
        }

    private:
        const FlatHashSet<T> *_pFlatHashSet;              // 对应的哈希表指针
        typename Vector<KVPair<T, bool>>::Rank _bucketIndex; // 桶索引
    };

    template <typename T>
    bool operator==(const FlatHashSetIterator<T> &lhs, const FlatHashSetIterator<T> &rhs)
    {
        return lhs._pFlatHashSet == rhs._pFlatHashSet && lhs._bucketIndex == rhs._bucketIndex;
    }

    template <typename T>
    bool operator!=(const FlatHashSetIterator<T> &lhs, const FlatHashSetIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }
} // namespace CZ

#endif