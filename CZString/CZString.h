/*
 @Date    : 2018-05-30 08:41:20
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
字符串类
 */

#ifndef CZSTRING_H
#define CZSTRING_H

#include "../Vector/Vector.h"
#include <string>
#include <iostream>

namespace CZ
{
    class CZString: public Vector<char>
    {
    public:
        using Rank = Vector<char>::Rank;

        CZString(const char *str_ = "");
        CZString(const std::string &str_);
        ~CZString();

        void clear() override;

        CZString(const CZString &CZstring);

        void print_info(const char *name = "") const override;

        const char* c_str() const;
        Rank length() const;

        CZString substr(Rank pos = 0) const;
        CZString substr(Rank pos, Rank l) const;

        operator const char*() const;
        operator const std::string() const;

        CZString& operator+=(const char rhs);
        CZString& operator+=(const CZString &rhs);
    private:
        mutable char *_tempStr = nullptr;
    };
} // CZ

#include "CZString_implementation.h"

#endif // CZSTRING_H


