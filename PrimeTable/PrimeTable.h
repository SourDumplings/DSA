/*
 * @Author: SourDumplings
 * @Date: 2018-09-22 23:09:00
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
 */
/*
 @Date    : 2018-08-06 22:52:59
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
素数表类
用埃式筛法生成素数表
 */

#ifndef PRIME_TABLE_H
#define PRIME_TABLE_H

#include "../Vector/Vector.h"
#include <stdexcept>
#include <cstdio>
#include <iostream>

namespace CZ
{
class PrimeTable
{
public:
    using Rank = unsigned;

    // 构造存放最大素数不超过upperLimit_的素数表
    PrimeTable(Rank upperLimit_);
    // 素数表中素数的个数
    Rank size() const;
    // 素数表的上界
    Rank upper_limit() const;
    void rebuild(Rank upperLimit_);
    // 返回第n个素数
    Rank get_prime(Rank n) const;
    // 判断素数
    bool is_prime(Rank num);

    // 输出信息
    void print_info(const char *name = "") const;

private:
    // 素数表大小，即素数的上界（所有存的素数都不大于它）
    Rank _upperLimit;
    // 素数的个数
    Rank _size;
    Vector<bool> _table;

    // 利用埃氏筛法构建素数表
    void _build_table();
};

// 构造存放最大素数不超过upperLimit_的素数表
PrimeTable::PrimeTable(PrimeTable::Rank upperLimit_) : _upperLimit(upperLimit_),
                                                       _size(0), _table(_upperLimit + 1) { _build_table(); }

// 素数表中素数的个数
PrimeTable::Rank PrimeTable::size() const { return _size; }
// 素数表的上界
PrimeTable::Rank PrimeTable::upper_limit() const { return _upperLimit; }
void PrimeTable::rebuild(PrimeTable::Rank upperLimit_)
{
    _upperLimit = upperLimit_;
    _size = 0;
    _table.resize(_upperLimit + 1);
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
    PrimeTable::Rank ret;
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
    if (_upperLimit < 2)
    {
        printf("Error from PrimeTable _build_table: _upperLimit is too small\n");
        throw std::exception();
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
} // namespace CZ

#endif // PRIME_TABLE_H
