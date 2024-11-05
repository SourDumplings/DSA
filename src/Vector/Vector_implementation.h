/*
 @Date    : 2018-04-06 18:21:46
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
向量类模板的各个方法的实现接口
等效于将各个头文件引入Vector.h
由于模板的定义和声明必须都包含在头文件中
相当于间接实现了定义与声明的分离
 */

#ifndef VECTOR_IMPLEMENTATION_H
#define VECTOR_IMPLEMENTATION_H

#include "Vector_init_from.h"

#include "Vector_constructors.h"
#include "Vector_copy_constructor.h"
#include "Vector_move_constructor.h"
#include "Vector_destructor.h"

#include "Vector_print_info.h"

#include "Vector_interfaces.h"

#include "Vector_modifications.h"

#include "Vector_expand.h"
#include "Vector_shrink.h"

#endif

