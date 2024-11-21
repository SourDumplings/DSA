/*
 @Date    : 2018-05-08 14:55:13
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
斐波那契数生成类
 */

#ifndef FIB_H
#define FIB_H

#include "../Base/Assert.h"
#include "../Base/BaseDef.h"

#include <cstdint>

namespace DSA
{
    class DLL_EXPORT_IMPORT Fib
    {
    public:
        // 初始化为不小于n的最小斐波那契项，默认为第0项，O(log_phi(n))时间
        Fib(int64_t n = 0);

        int64_t get();
        int64_t next();
        int64_t prev();

        // 获取
    private:
        int64_t lastItem, thisItem; // lastItem = fib(k-1), thisItem = fib(k)。均为int型，很快就会溢出。
    };

    // 得到斐波那契数列的第n项，2个版本的方法
    DLL_EXPORT_IMPORT int64_t get_fib(int n, uint32_t version = 0);
} // DSA



#endif // FIB_H


