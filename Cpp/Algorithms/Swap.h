/*
 @Date    : 2018-05-10 21:07:58
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
交换函数模板
 */

#ifndef SWAP_H
#define SWAP_H

template <typename T>
void Swap(T &a, T &b)
{
    T temp(a);
    a = b;
    b = temp;
    return;
}

#endif // SWAP_H


