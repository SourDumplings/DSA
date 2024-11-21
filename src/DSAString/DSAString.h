/*
 @Date    : 2018-05-30 08:41:20
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
字符串类，本质为存储了字符型的向量，注意不存储c字符串中的结尾字符'\0'
即向量的大小就是字符串的长度
 */

#ifndef DSASTRING_H
#define DSASTRING_H

#include "../Vector/Vector.h"
#include <string>
#include <iostream>

namespace DSA
{
    class DSAString;

    // 操作符函数的声明
    DLL_EXPORT_IMPORT const DSAString operator+(const DSAString &lhs, const char rhs);
    DLL_EXPORT_IMPORT const DSAString operator+(const DSAString &lhs, const DSAString &rhs);
    DLL_EXPORT_IMPORT std::istream &operator>>(std::istream &is, DSAString &rhs);

    class DLL_EXPORT_IMPORT DSAString : public Vector<char>
    {
    public:
        using Rank = typename Vector<char>::Rank;

        DSAString(const char *str_ = "");
        DSAString(const std::string &str_);
        explicit DSAString(Rank n, char c); // 初始化一个字符 c 重复 n 次的字符串
        ~DSAString() override;

        DSAString(const char* begin, const char* end);

        template <typename It>
        DSAString(const It& begin, const It& end);

        DSAString(const DSAString &s);
        DSAString(DSAString &&s) noexcept;

        void print_info(const char *name = "") const override;

        const char *c_str() const override;
        
        Rank length() const;

        DSAString substr(Rank pos = 0) const;
        DSAString substr(Rank pos, Rank l) const;
        // 返回长度为 l 的前、后缀
        DSAString prefix(Rank l) const;
        DSAString suffix(Rank l) const;
        // 若s是当前字符串的一个子串，则返回子串起始位置，否则返回 length()
        Rank index_of(const DSAString &s) const;

        operator const char *() const;
        operator const std::string() const;

        DSAString &operator=(const DSAString &s);
        DSAString &operator=(DSAString &&s) noexcept;
        DSAString &operator+=(const char rhs);
        DSAString &operator+=(const DSAString &rhs);

        const char *get_entity_name() const override;

        /**
         * @brief 替换字符串中单个字符
         * 
         * @param [in] oldChar 
         * @param [in] newChar 
         * @return Rank 被替换的字符个数
         */
        Rank replace_char(char oldChar, char newChar);
    };
} // DSA

#endif // DSASTRING_H
