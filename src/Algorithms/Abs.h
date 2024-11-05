/*
 @Date    : 2018-06-18 16:48:57
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
取绝对值的函数，接受的类型有正负，必须可以与0比较
 */

#ifndef ABS_H
#define ABS_H

namespace CZ
{
    template <typename T>
    inline T Abs(const T num)
    { return num < 0 ? -num : num; }
} // CZ

#endif // ABS_H

