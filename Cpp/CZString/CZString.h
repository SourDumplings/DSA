/*
 @Date    : 2018-05-30 08:41:20
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
字符串类
注意和std::string不同的是length()方法返回的是字符串长度，size()返回的是length() + 1
 */

#ifndef CZSTRING_H
#define CZSTRING_H

#include "../Vector/Vector.h"
#include <string>

namespace CZ
{
    class CZString: public Vector<char>
    {
    public:
        using Rank = Vector<char>::Rank;

        CZString(const char *str_);
        CZString(const std::string &str_);

        void print_info(const char *name = "") const;

        const char* c_str() const;
        Rank length() const;

        CZString substr(Rank pos = 0) const;
        CZString substr(Rank pos, Rank l) const;

        operator const char*() const;
        operator const std::string() const;
    };
} // CZ

#include "CZString_implementation.h"

#endif // CZSTRING_H


