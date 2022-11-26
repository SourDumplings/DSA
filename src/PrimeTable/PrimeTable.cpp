/*
 * @Author: SourDumplings
 * @Date: 2021-11-01 16:09:58
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 素数表的实现
 */

#include "PrimeTable.h"

#include <stdexcept>
#include <cstdio>
#include <iostream>
#include "../CZString/CZString.h"

namespace CZ
{
    // 构造存放最大素数不超过upperLimit_的素数表
    PrimeTable::PrimeTable(PrimeTable::Rank upperLimit_) : _upperLimit(upperLimit_),
                                                           _size(0) { _build_table(); }

    // 素数表中素数的个数
    PrimeTable::Rank PrimeTable::size() const { return _size; }
    // 素数表的上界
    PrimeTable::Rank PrimeTable::upper_limit() const { return _upperLimit; }
    void PrimeTable::rebuild(PrimeTable::Rank upperLimit_)
    {
        _upperLimit = upperLimit_;
        _size = 0;
        _build_table();
        return;
    }
    // 返回第n个素数
    PrimeTable::Rank PrimeTable::get_prime(PrimeTable::Rank n) const
    {
        if (n > _size)
        {
            printf("Error from PrimeTable get_prime: this table doesn't have so many primes\n");
            throw std::exception();
        }
        PrimeTable::Rank ret = 0;
        for (PrimeTable::Rank i = 2, count = 0; i <= _upperLimit; ++i)
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
    // 判断素数
    bool PrimeTable::is_prime(PrimeTable::Rank num)
    {
        if (num > _upperLimit)
        {
            printf("Error from PrimeTable get_prime: this number is too large\n");
            throw std::exception();
        }
        return _table[num];
    }

    // 输出信息
    void PrimeTable::print_info(const char *name) const
    {
        printf("for PrimeTable %s:\n", name);
        std::cout << "it contains " << _size << " prime numbers, no greater than " << _upperLimit
                  << std::endl;
        printf("including:");
        for (Rank i = 2; i <= _upperLimit; ++i)
        {
            if (_table[i])
            {
                std::cout << " " << i;
            }
        }
        printf("\n\n");
        return;
    }

    void PrimeTable::_build_table()
    {
        clear();
        _table.resize(_upperLimit + 1);

        if (_upperLimit < 2)
        {
            return;
        }

        _table[0] = _table[1] = false;
        for (PrimeTable::Rank i = 2; i <= _upperLimit; ++i)
        {
            _table[i] = true;
        }
        for (PrimeTable::Rank i = 4; i <= _upperLimit; i += 2)
        {
            _table[i] = false;
        }

        for (PrimeTable::Rank i = 3; i * i <= _upperLimit; i += 2)
        {
            if (_table[i])
            {
                for (PrimeTable::Rank j = i * 2; j <= _upperLimit; j += i)
                {
                    _table[j] = false;
                }
            }
        }

        for (PrimeTable::Rank i = 2; i < _upperLimit; i++)
        {
            if (_table[i])
            {
                ++_size;
            }
        }

        return;
    }

    const char *PrimeTable::c_str() const
    {
        std::ostringstream oss;
        oss << this->get_entity_name() << "[";
        for (Rank i = 2; i <= _upperLimit; ++i)
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
        return (Hash<CZString>()(get_entity_name()) + _table.hash()) % CZ_MAX_HASH_VALUE;
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

}