/*
 @Date    : 2018-05-20 21:01:12
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的复制构造函数
 */

#ifndef LIST_COPY_CONSTRUCTOR_H
#define LIST_COPY_CONSTRUCTOR_H

#include "List.h"

namespace DSA
{
    template <typename T>
    List<T>::List(const List<T> &l)
    {
        init_from(l.begin(), l.end());
    }
} // DSA

#endif // LIST_COPY_CONSTRUCTOR_H
