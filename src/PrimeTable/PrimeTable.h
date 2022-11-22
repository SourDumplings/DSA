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

#include "../Base/AbstractBaseContainer.h"
#include "../Vector/Vector.h"

namespace CZ
{
    class PrimeTable : public AbstractBaseContainer<uint32_t>
    {
    public:
        using Rank = typename AbstractBaseContainer<uint32_t>::Rank;

        // 构造存放最大素数不超过upperLimit_的素数表
        PrimeTable(Rank upperLimit_);
        // 素数表中素数的个数
        Rank size() const override;
        // 素数表的上界
        Rank upper_limit() const;
        void rebuild(Rank upperLimit_);
        // 返回第n个素数
        Rank get_prime(Rank n) const;
        // 判断素数
        bool is_prime(Rank num);

        // 输出信息
        void print_info(const char *name = "") const;

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

        void clear() override;

    private:
        // 素数表大小，即素数的上界（所有存的素数都不大于它）
        Rank _upperLimit;
        // 素数的个数
        Rank _size;
        Vector<bool> _table;

        // 利用埃氏筛法构建素数表
        void _build_table();
    };
} // namespace CZ

#endif // PRIME_TABLE_H
