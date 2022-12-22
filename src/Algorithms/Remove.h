/*
 @Date    : 2019-01-31 15:12:47
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Remove算法，类似于STL中的remove，将待删除的元素移到后面，常与erase搭配使用
返回保留元素序列的尾后迭代器
只能接受随机访问迭代器，必须传入单元谓词作为比较器判断删除条件
 */

#ifndef REMOVE_H
#define REMOVE_H

#include "../Base/Assert.h"
#include "../Iterator/Iterator_traits.h"
#include <utility>

namespace CZ
{
    namespace RemoveAccessories
    {
        template <typename It, typename F>
        It doRemove(const It begin, const It end, const F &is_remove)
        {
            using Rank = uint32_t;
            It it = begin;
            Rank i = 0;
            for (; it != end; ++it)
            {
                if (!is_remove(*it))
                {
                    *(begin + i) = *it;
                    ++i;
                }
            }
            return begin + i;
        }

        template <typename It, typename F>
        It test_iterator_for_remove(const It &begin, const It &end,
                                    random_iterator_tag, const F &is_remove)
        {
            return doRemove(begin, end, is_remove);
        }

        template <typename It, typename F>
        It test_iterator_for_remove(const It &begin, const It &end,
                                    seq_iterator_tag, const F &is_remove)
        {
            ASSERT_DEBUG(false, "iterator is seq_iterator, should be random_iterator");
            return nullptr;
        }

        template <typename It, typename F>
        It test_iterator_for_remove(const It &begin, const It &end,
                                    bi_iterator_tag, const F &is_remove)
        {
            ASSERT_DEBUG(false, "iterator is bi_iterator, should be random_iterator");
            return nullptr;
        }
    }

    template <typename It, typename F>
    inline It Remove(const It begin, const It end, const F &is_remove)
    {
        return RemoveAccessories::test_iterator_for_remove(begin, end,
                                                           typename Iterator_traits<It>::iterator_category(),
                                                           is_remove);
    }
}

#endif // REMOVE_H
