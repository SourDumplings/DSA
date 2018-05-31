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
    CZString::CZString(const char *str_): Vector<char>(str_, strlen(str_)) {}
    CZString::CZString(const std::string &str_): CZString(str_.c_str()) {}

    CZString::~CZString() { if (_tempStr) delete [] _tempStr; }

    CZString::CZString(const CZString &CZstring): Vector<char>(CZstring)
    {
        _tempStr = nullptr;
    }

    void CZString::clear()
    {
        Vector<char>::clear();
        if (_tempStr)
        {
            delete [] _tempStr;
        }
        _tempStr = nullptr;
        return;
    }

    void CZString::print_info(const char *name) const
    {
        printf("CZString %s is ", name);
        for (iterator it = begin(); it != end(); ++it)
        {
            putchar(*it);
        }
        printf("\nlength = %u\n\n", length());
        return;
    }

    inline CZString::Rank CZString::length() const { return size(); }

    const char* CZString::c_str() const
    {
        if (_tempStr)
        {
            delete [] _tempStr;
        }
        _tempStr = new char[length()+1];
        strncpy(_tempStr, &front(), length());
        _tempStr[length()] = '\0';
        return _tempStr;
    }

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
        strncpy(temp, &front()+pos, l);
        temp[l] = '\0';
        return CZString(temp);
    }

    inline CZString CZString::substr(Rank pos) const
    { return substr(pos, length() - pos); }

    inline CZString::operator const char*() const
    { return c_str(); }

    inline CZString::operator const std::string() const
    { return std::string(c_str()); }

    const CZString operator+(const CZString &lhs, const char rhs)
    {
        CZString temp(lhs);
        temp.push_back(rhs);
        return temp;
    }

    const CZString operator+(const CZString &lhs, const CZString &rhs)
    {
        CZString temp(lhs);
        temp.insert(temp.end(), rhs.begin(), rhs.end());
        return temp;
    }

    inline CZString& CZString::operator+=(const char rhs)
    { *this = *this + rhs; return *this; }

    inline CZString& CZString::operator+=(const CZString &rhs)
    { *this = *this + rhs; return *this; }

    inline std::ostream& operator<<(std::ostream &os, const CZString &rhs)
    { return os << rhs.c_str(); }

    std::istream& operator>>(std::istream &is, CZString &rhs)
    {
        std::string s;
        is >> s;
        rhs = s;
        return is;
    }
} // CZ

#endif // CZ_STRING_IMPLEMENTATION_H



