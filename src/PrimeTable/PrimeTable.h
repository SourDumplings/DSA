/*
 * @Author: SourDumplings
 * @Date: 2018-09-22 23:09:00
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

/*
素数表类
用埃式筛法生成素数表
 */

#ifndef PRIME_TABLE_H
#define PRIME_TABLE_H

#include "../Base/AbstractBaseContainer.h"
#include "../Vector/Vector.h"

namespace CZ
{
    class PrimeTable: public AbstractBaseContainer<uint32_t>
    {
    public:
        using Rank = typename Vector<bool>::Rank;

        static PrimeTable& get_instance(Rank upperLimit_ = MIN_UPPER_LIMIT);

        // 素数表中素数的个数
        Rank size() const override { return _size; }

        // 素数表的上界
        Rank upper_limit() const { return _table.size(); }

        // 返回第n个素数
        Rank get_prime(Rank n);
        Rank get_prime(Rank n) const;

        // 判断素数
        bool is_prime(Rank num);
        bool is_prime(Rank num) const;

        // 输出信息
        void print_info(const char *name = "") const;

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

        void clear() override;

    private:
        static constexpr Rank MIN_UPPER_LIMIT = 256;

        // 素数的个数
        Rank _size;
        Vector<bool> _table;

        PrimeTable() = delete;
        PrimeTable(const PrimeTable&) = delete;
        PrimeTable(PrimeTable&&) = delete;

        // 构造存放最大素数不超过upperLimit_的素数表
        PrimeTable(Rank upperLimit_);

        // 利用埃氏筛法构建素数表
        void _build_table();

        // 扩展素数表
        void _expand(Rank upperLimit_);
    };
} // namespace CZ

#endif // PRIME_TABLE_H
