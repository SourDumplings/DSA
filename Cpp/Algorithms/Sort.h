/*
 @Date    : 2018-05-11 14:25:00
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
排除函数模板接口，传入的迭代器必须是支持随机访问的
 */

#ifndef SORT_H
#define SORT_H

#include "Stable_sort.h"

#include <functional>

namespace CZ
{
    // 对于不稳定排序
    enum UnstableSortMethod
    {

    };

    // 对于指定使用稳定排序方法
    template <typename It, typename Cmp>
    void Sort(const It &begin, const It &end, const Cmp &cmp,
        const StableSortMethod &method = BUBBLE_SORT, const unsigned version = 0)
    {
        Stable_sort(begin, end, cmp, method, version);
        return;
    }

    template <typename It>
    void Sort(const It &begin, const It &end,
        const StableSortMethod &method = BUBBLE_SORT, const unsigned version = 0)
    {
        Sort(begin, end, std::less<const decltype(*begin)>(), method, version);
        return;
    }
} // CZ

#endif // SORT_H


