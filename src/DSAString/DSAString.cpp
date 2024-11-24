/*
 @Date    : 2018-05-30 08:47:58
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
字符串类的实现
 */

#ifndef DSA_STRING_IMPLEMENTATION_H
#define DSA_STRING_IMPLEMENTATION_H

#include "DSAString.h"

#include <cstring>
#include <cstdio>
#include <iostream>
#include "../Algorithms/Match.h"

namespace DSA
{
    DSAString::DSAString(const char *str_) : Vector<char>(const_cast<char*>(str_), const_cast<char*>(str_) + strlen(str_)) {}
    DSAString::DSAString(const std::string &str_) : DSAString(str_.c_str()) {}

    DSAString::DSAString(const char* begin, const char* end) : Vector<char>(begin, end) {}

    template <typename It>
    DSAString::DSAString(const It& begin, const It& end) : Vector<char>(begin, end) {}

    DSAString::~DSAString()
    {
    }

    DSAString::DSAString(const DSAString &s) : Vector<char>(s)
    {
    }

    DSAString::DSAString(DSAString &&s) noexcept : Vector<char>(std::forward<Vector<char>>(s))
    {
    }

    DSAString::DSAString(Rank n, char c): Vector<char>(n)
    {
        memset(_elem, c, size());
    }

    void DSAString::print_info(const char *name) const
    {
        printf("DSAString %s is ", name);
        for (Iterator it = begin(); it != end(); ++it)
        {
            putchar(*it);
        }
        printf("\nlength = %u\n\n", length());
    }

    DSAString::Rank DSAString::length() const { return size(); }

    const char *DSAString::c_str() const
    {
        std::ostringstream oss;
        for (Iterator it = begin(); it != end(); ++it)
        {
            oss << *it;
        }
        return this->get_c_str_from_stream(oss);
    }

    DSAString DSAString::substr(Rank pos, Rank l) const
    {
        ASSERT_DEBUG(pos + l <= length(), "wrong, the length of this string is %u", length());
        return DSAString(begin() + pos, begin() + pos + l);
    }

    DSAString DSAString::substr(Rank pos) const
    {
        return substr(pos, length() - pos);
    }

    DSAString DSAString::prefix(Rank l) const
    {
        ASSERT_DEBUG(l <= length(), "Error from DSAString prefix: prefix length is greater than full length");
        return substr(0, l);
    }

    DSAString DSAString::suffix(Rank l) const
    {
        Rank len = length();
        ASSERT_DEBUG(l <= len, "Error from DSAString suffix: suffix length is greater than full length");
        return substr(len - l, l);
    }

    DSAString::Rank DSAString::index_of(const DSAString &s) const
    {
        return static_cast<DSAString::Rank>(Match(begin(), end(), s.begin(), s.end()));
    }

    DSAString::operator const char *() const
    {
        return c_str();
    }

    DSAString::operator const std::string() const
    {
        return std::string(c_str());
    }

    const DSAString operator+(const DSAString &lhs, const char rhs)
    {
        DSAString temp(lhs);
        temp.push_back(rhs);
        return temp;
    }

    const DSAString operator+(const DSAString &lhs, const DSAString &rhs)
    {
        DSAString temp(lhs);
        temp.insert(temp.end(), rhs.begin(), rhs.end());
        return temp;
    }

    DSAString &DSAString::operator=(const DSAString &s)
    {
        Vector<char>::operator=(s);
        return *this;
    }

    DSAString &DSAString::operator=(DSAString &&s) noexcept
    {
        Vector<char>::operator=(std::forward<DSAString>(s));
        return *this;
    }

    DSAString &DSAString::operator+=(const char rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    DSAString &DSAString::operator+=(const DSAString &rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    std::istream &operator>>(std::istream &is, DSAString &rhs)
    {
        std::string s;
        is >> s;
        rhs = s;
        return is;
    }

    const char *DSAString::get_entity_name() const
    {
        return "DSAString";
    }

    typename DSAString::Rank DSAString::replace_char(char oldChar, char newChar)
    {
        if (oldChar == newChar)
        {
            return 0;
        }
        
        Rank replacedNum = 0;
        for (Iterator it = begin(); it != end(); ++it)
        {
            if (*it == oldChar)
            {
                *it = newChar;
                ++replacedNum;
            }
        }
        return replacedNum;
    }
} // DSA

#endif // DSA_STRING_IMPLEMENTATION_H
