/*
 @Date    : 2018-05-29 14:29:58
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
算术表达式类
可以进行中缀表达式的求值、向前缀表达式（波兰式）和向后缀表达式（逆波兰式）的转换
目前使用了STL中的string，等到我自己的String实现了再替换
还有乘方的计算函数还没有实现
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../Base/AbstractBaseEntity.h"
#include "../CZString/CZString.h"
#include <string>

namespace CZ
{
    static const uint32_t OPERTAOR_NUM = 9;

    class DLL_EXPORT_IMPORT Expression : public AbstractBaseEntity
    {
    public:
        using ValueType = double;

        Expression(const char *exp_ = "", const char delimiter_ = ' ');
        Expression(const std::string &exp_, const char delimiter_ = ' ');
        Expression(const CZString &exp_, const char delimiter_ = ' ');
        ~Expression();

        void print_info(const char *name = "") const;

        ValueType calc_value() const;

        CZString to_PN() const;
        CZString to_RPN() const;

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

    private:
        ValueType read_num(const char *&p) const;
        ValueType reverse_read_num(const char *&p) const;
        char compare_operator(const char nowOp, const char sOp) const;
        char reverse_compare_operator(const char nowOp, const char sOp) const;
        ValueType calc(const ValueType &lhs, const char op, const ValueType &rhs) const;
        ValueType calc(const ValueType &operand, const char op) const;
        bool is_one_element_operator(const char op) const;
        uint32_t get_operator_index(const char op) const;
        char *_exp = nullptr, _delimiter = ' ';

        static const char priTable[OPERTAOR_NUM][OPERTAOR_NUM];        // 运算符优先级表
        static const char priTableReverse[OPERTAOR_NUM][OPERTAOR_NUM]; // 运算符优先级逆表
    };
} // CZ

#endif // EXPRESSION_H
