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
#include <iostream>
#include "../Algorithms/Match.h"

namespace CZ
{
    CZString::CZString(const char *str_) : Vector<char>(const_cast<char*>(str_), const_cast<char*>(str_) + strlen(str_)) {}
    CZString::CZString(const std::string &str_) : CZString(str_.c_str()) {}

    CZString::~CZString()
    {
    }

    CZString::CZString(const CZString &CZstring) : Vector<char>(CZstring)
    {
    }

    void CZString::print_info(const char *name) const
    {
        printf("CZString %s is ", name);
        for (Iterator it = begin(); it != end(); ++it)
        {
            putchar(*it);
        }
        printf("\nlength = %u\n\n", length());
        return;
    }

    CZString::Rank CZString::length() const { return size(); }

    const char *CZString::c_str() const
    {
        std::ostringstream oss;
        for (Iterator it = begin(); it != end(); ++it)
        {
            oss << *it;
        }
        return this->get_c_str_from_stream(oss);
    }

    CZString CZString::substr(Rank pos, Rank l) const
    {
        ASSERT_DEBUG(pos + l <= length(), "wrong, the length of this string is %u", length());
        char temp[l + 1];
        strncpy(temp, &front() + pos, l);
        temp[l] = '\0';
        return CZString(temp);
    }

    CZString CZString::substr(Rank pos) const
    {
        return substr(pos, length() - pos);
    }

    CZString CZString::prefix(Rank l) const
    {
        ASSERT_DEBUG(l <= length(), "Error from CZString prefix: prefix length is greater than full length");
        return substr(0, l);
    }

    CZString CZString::suffix(Rank l) const
    {
        Rank len = length();
        ASSERT_DEBUG(l <= len, "Error from CZString suffix: suffix length is greater than full length");
        return substr(len - l, l);
    }

    CZString::Rank CZString::index_of(const CZString &s) const
    {
        return static_cast<CZString::Rank>(Match(begin(), end(), s.begin(), s.end()));
    }

    CZString::operator const char *() const
    {
        return c_str();
    }

    CZString::operator const std::string() const
    {
        return std::string(c_str());
    }

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

    CZString &CZString::operator=(const CZString &s)
    {
        Vector<char>::operator=(static_cast<Vector<char>>(s));
        return *this;
    }

    CZString &CZString::operator=(CZString &&s)
    {
        Vector<char>::operator=(static_cast<Vector<char>>(s));
        return *this;
    }

    CZString &CZString::operator+=(const char rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    CZString &CZString::operator+=(const CZString &rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    std::istream &operator>>(std::istream &is, CZString &rhs)
    {
        std::string s;
        is >> s;
        rhs = s;
        return is;
    }

    const char *CZString::get_entity_name() const
    {
        return "CZString";
    }
} // CZ

#endif // CZ_STRING_IMPLEMENTATION_H
