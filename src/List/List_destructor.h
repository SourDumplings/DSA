/*
 @Date    : 2018-05-17 18:57:11
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的析构函数
 */

#ifndef LIST_DESTRUCTOR_H
#define LIST_DESTRUCTOR_H

#include "List.h"

namespace DSA
{
    template <typename T>
    void List<T>::free()
    {
        clear();
        delete _head;
    }

    template <typename T>
    List<T>::~List()
    {
        free();
    }
} // DSA

#endif // LIST_DESTRUCTOR_H


