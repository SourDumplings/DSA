/*
 @Date    : 2018-05-30 08:41:20
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
字符串类，本质为存储了字符型的向量，注意不存储c字符串中的结尾字符'\0'
即向量的大小就是字符串的长度
 */

#ifndef CZSTRING_H
#define CZSTRING_H

#include "../Vector/Vector.h"
#include <string>
#include <iostream>

namespace CZ
{
    class CZString;

    // 操作符函数的声明
    const CZString operator+(const CZString &lhs, const char rhs);
    const CZString operator+(const CZString &lhs, const CZString &rhs);
    std::istream &operator>>(std::istream &is, CZString &rhs);

    class CZString : public Vector<char>
    {
    public:
        using Rank = typename Vector<char>::Rank;

        CZString(const char *str_ = "");
        CZString(const std::string &str_);
        explicit CZString(Rank n, char c); // 初始化一个字符 c 重复 n 次的字符串
        ~CZString() override;

        CZString(const CZString &s);
        CZString(CZString &&s) noexcept;

        void print_info(const char *name = "") const override;

        const char *c_str() const override;
        
        Rank length() const;

        CZString substr(Rank pos = 0) const;
        CZString substr(Rank pos, Rank l) const;
        // 返回长度为 l 的前、后缀
        CZString prefix(Rank l) const;
        CZString suffix(Rank l) const;
        // 若s是当前字符串的一个子串，则返回子串起始位置，否则返回 length()
        Rank index_of(const CZString &s) const;

        operator const char *() const;
        operator const std::string() const;

        CZString &operator=(const CZString &s);
        CZString &operator=(CZString &&s) noexcept;
        CZString &operator+=(const char rhs);
        CZString &operator+=(const CZString &rhs);

        const char *get_entity_name() const override;
    };
} // CZ

#endif // CZSTRING_H
