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

#include <string>

namespace CZ
{
    using std::string;

    static const unsigned OPERTAOR_NUM = 9;

    class Expression
    {
    public:
        using ValueType = double;

        Expression(const char *exp_ = "", const char delimiter_ = ' ');
        Expression(const string &exp_, const char delimiter_ = ' ');

        void print_info(const string &name = "") const;

        ValueType calc_value() const;

        string to_PN() const;
        string to_RPN() const;
    private:
        ValueType read_num(const char *&p) const;
        char compare_operator(const char nowOp, const char sOp) const;
        ValueType calc(const ValueType &lhs, const char op, const ValueType &rhs) const;
        ValueType calc(const ValueType &operand, const char op) const;
        bool is_one_element_operator(const char op) const;
        unsigned get_operator_index(const char op) const;


        const char *_exp, _delimiter = ' ';
        static const char priTable[OPERTAOR_NUM][OPERTAOR_NUM]; // 运算符优先级表
    };

    // 初始化算数符号优先级顺序表
    // '<'代表栈顶元素的优先级高，'>'代表当前元素优先级高
    // '='代表优先级相等，需要单纯弹栈不计算
    // 'e'代表表达式错误
    const char Expression::priTable[OPERTAOR_NUM][OPERTAOR_NUM] =
    {
        /* ------------------当前运算符---------------------*/
        /*             +    -    *    /    ^    !    (    )    \0  */
        /* |                                                       */
        /* 栈  +  */  '<', '<', '>', '>', '>', '>', '>', '<', '<',
        /* |   -  */  '<', '<', '>', '>', '>', '>', '>', '<', '<',
        /* 顶  *  */  '<', '<', '<', '<', '>', '>', '>', '<', '<',
        /* |   /  */  '<', '<', '<', '<', '>', '>', '>', '<', '<',
        /* 运  ^  */  '<', '<', '<', '<', '<', '>', '>', '<', '<',
        /* |   !  */  '<', '<', '<', '<', '<', '<', '>', '<', '<',
        /* 算  (  */  '>', '>', '>', '>', '>', '>', '>', '=', 'e',
        /* |   )  */  'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
        /* 符  \0 */  '>', '>', '>', '>', '>', '>', '>', 'e', '=',
        /* |                                                       */
    };
} // CZ

#endif // EXPRESSION_H


