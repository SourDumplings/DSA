/*
 @Date    : 2018-04-09 19:31:43
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector类模板的动态操作方法
 */

#ifndef VECTOR_MODIFICATIONS_H
#define VECTOR_MODIFICATIONS_H

#include "Vector.h"

namespace CZ
{
    template <typename T>
    void Vector<T>::clear()
    {
        free();
        _size = _capacity = 0;
        return;
    }
}

#endif // VECTOR_MODIFICATIONS_H


