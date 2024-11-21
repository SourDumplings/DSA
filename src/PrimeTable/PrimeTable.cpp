/*
 * @Author: SourDumplings
 * @Date: 2021-11-01 16:09:58
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 素数表的实现
 */

#include "PrimeTable.h"

#include <cstdio>
#include <iostream>
#include "../DSAString/DSAString.h"

namespace DSA
{
    PrimeTable::PrimeTable(PrimeTable::Rank upperLimit_)
        : AbstractBaseContainer<uint32_t>()
        , _size(0)
    {
        ASSERT_RELEASE(MIN_UPPER_LIMIT <= upperLimit_, "Too small upper limit %u, at least %u"
            , upperLimit_
            , MIN_UPPER_LIMIT
        );
        _table.resize(upperLimit_);
        _build_table();
    }

    void PrimeTable::_expand(PrimeTable::Rank upperLimit_)
    {
        if (upperLimit_ <= upper_limit())
        {
            return;
        }

        _table.resize(upperLimit_);
        _build_table();
    }

    PrimeTable::Rank PrimeTable::get_prime(PrimeTable::Rank n) const
    {
        ASSERT_RELEASE(n <= _size, "Too large n = %u requested, this table only contains %u primes."
            , n
            , _size
        );

        PrimeTable::Rank ret = 0;
        for (PrimeTable::Rank i = 2, count = 0; i < upper_limit(); ++i)
        {
            if (_table[i])
            {
                ++count;
            }
            if (count == n)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    PrimeTable::Rank PrimeTable::get_prime(PrimeTable::Rank n)
    {
        while (_size < n)
        {
            _expand(upper_limit() * 2);
        }

        return static_cast<const PrimeTable &>(*this).get_prime(n);
    }

    bool PrimeTable::is_prime(PrimeTable::Rank num) const
    {
        ASSERT_RELEASE(num < upper_limit(), "Too large num = %u requested, upper limit is %u."
            , num
            , upper_limit()
        );

        return _table[num];
    }

    bool PrimeTable::is_prime(PrimeTable::Rank num)
    {
        while (upper_limit() <= num)
        {
            _expand(num * 2);
        }

        return static_cast<const PrimeTable &>(*this).is_prime(num);
    }

    // 输出信息
    void PrimeTable::print_info(const char *name) const
    {
        printf("for PrimeTable %s:\n", name);
        std::cout << "it contains " << _size << " prime numbers, no greater than " << upper_limit()
            << std::endl;
        printf("including:");
        for (Rank i = 2; i < upper_limit(); ++i)
        {
            if (_table[i])
            {
                std::cout << " " << i;
            }
        }
        printf("\n\n");
    }

    void PrimeTable::_build_table()
    {
        _table[0] = _table[1] = false;
        for (PrimeTable::Rank i = 2; i < upper_limit(); ++i)
        {
            _table[i] = true;
        }

        for (PrimeTable::Rank i = 4; i < upper_limit(); i += 2)
        {
            _table[i] = false;
        }

        for (PrimeTable::Rank i = 3; i * i < upper_limit(); i += 2)
        {
            if (_table[i])
            {
                for (PrimeTable::Rank j = i * 2; j < upper_limit(); j += i)
                {
                    _table[j] = false;
                }
            }
        }

        _size = 0;
        for (PrimeTable::Rank i = 2; i < upper_limit(); i++)
        {
            if (_table[i])
            {
                ++_size;
            }
        }

    }

    const char *PrimeTable::c_str() const
    {
        std::ostringstream oss;
        oss << this->get_entity_name() << "[";
        for (Rank i = 2; i < upper_limit(); ++i)
        {
            if (_table[i])
            {
                if (2 < i)
                {
                    oss << ", ";
                }
                oss << i;
            }
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
    }

    HashRank PrimeTable::hash() const
    {
        return (Hash<DSAString>()(get_entity_name()) + _table.hash()) % DSA_MAX_HASH_VALUE;
    }

    const char *PrimeTable::get_entity_name() const
    {
        return "PrimeTable";
    }

    void PrimeTable::clear()
    {
        _size = 0;
        _table.clear();
    }

    PrimeTable &PrimeTable::get_instance(Rank upperLimit_)
    {
        static PrimeTable instance(upperLimit_);
        return instance;
    }

}