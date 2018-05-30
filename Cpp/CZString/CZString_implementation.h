/*
 @Date    : 2018-05-30 08:47:58
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
字符串类的实现
 */

#ifndef CZ_STRING_IMPLEMENTATION_H
#define CZ_STRING_IMPLEMENTATION_H

#include "CZString.h"
#include <cstring>
#include <cstdio>
#include <stdexcept>

namespace CZ
{
    CZString::CZString(const char *str_): Vector<char>(str_, strlen(str_) + 1) {}
    CZString::CZString(const std::string &str_): CZString(str_.c_str()) {}

    void CZString::print_info(const char *name) const
    {
        printf("CZString %s is %s\n", name, c_str());
        printf("size = %u, length = %u\n\n", size(), length());
        return;
    }

    inline const char* CZString::c_str() const
    { return &front(); }

    inline CZString::Rank CZString::length() const { return size() - 1; }

    CZString CZString::substr(Rank pos, Rank l) const
    {
        try
        {
            if (pos + l > length())
            {
                throw "wrong, the length of this string is";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s %u\n", errMsg, length());
            throw std::exception();
        }
        char temp[l+1];
        strncpy(temp, c_str()+pos, l);
        temp[l] = '\0';
        return CZString(temp);
    }

    inline CZString CZString::substr(Rank pos) const
    { return substr(pos, length() - pos); }

    inline CZString::operator const char*() const
    { return c_str(); }

    inline CZString::operator const std::string() const
    { return std::string(c_str()); }


} // CZ

#endif // CZ_STRING_IMPLEMENTATION_H



