/*
 @Date    : 2018-05-29 14:36:23
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
算术表达式模板类的实现
 */

#include <cctype>
#include <stdexcept>
#include <cmath>
#include <cstring>
#include <iostream>

#include "Expression.h"
#include "../Stack/Stack.h"
#include "../Algorithms/Factorial.h"

namespace CZ
{
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

    const char Expression::priTableReverse[OPERTAOR_NUM][OPERTAOR_NUM] =
    {
        /* ------------------当前运算符---------------------*/
        /*             +    -    *    /    ^    !    (    )    \0  */
        /* |                                                       */
        /* 栈  +  */  '<', '<', '>', '>', '>', '>', '<', '>', '<',
        /* |   -  */  '<', '<', '>', '>', '>', '>', '<', '>', '<',
        /* 顶  *  */  '<', '<', '<', '<', '>', '>', '<', '>', '<',
        /* |   /  */  '<', '<', '<', '<', '>', '>', '<', '>', '<',
        /* 运  ^  */  '<', '<', '<', '<', '<', '>', '<', '>', '<',
        /* |   !  */  '<', '<', '<', '<', '<', '<', '<', '>', '<',
        /* 算  (  */  'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
        /* |   )  */  '>', '>', '>', '>', '>', '>', '=', '>', 'e',
        /* 符  \0 */  '>', '>', '>', '>', '>', '>', '<', 'e', '=',
        /* |                                                       */
    };

    Expression::Expression(const char *exp_, const char delimiter_) : _delimiter(delimiter_)
    {
        _exp = new char[strlen(exp_) + 2];
        *_exp = '\0'; // 头部哨兵
        strcpy(_exp + 1, exp_);
    }

    Expression::Expression(const std::string &exp_, const char delimiter_) : Expression(exp_.c_str(), delimiter_) {}

    Expression::Expression(const CZString &exp_, const char delimiter_) : Expression(exp_.c_str(), delimiter_) {}

    Expression::~Expression()
    {
        if (_exp)
            delete[] _exp;
    }

    void Expression::print_info(const char *name) const
    {
        printf("expression %s is: %s\n\n", name, _exp + 1);
        return;
    }

    bool inline Expression::is_one_element_operator(const char op) const
    {
        return op == '!';
    }

    int32_t Expression::get_operator_index(const char op) const
    {
        int32_t ret;
        try
        {
            switch (op)
            {
            case '+':
                ret = 0;
                break;
            case '-':
                ret = 1;
                break;
            case '*':
                ret = 2;
                break;
            case '/':
                ret = 3;
                break;
            case '^':
                ret = 4;
                break;
            case '!':
                ret = 5;
                break;
            case '(':
                ret = 6;
                break;
            case ')':
                ret = 7;
                break;
            case '\0':
                ret = 8;
                break;
            default:
            {
                throw "in function get_operator_index, unknown operator";
                break;
            }
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s: %c\n", errMsg, op);
            throw std::exception();
        }
        return ret;
    }

    inline char Expression::compare_operator(const char nowOp, const char sOp) const
    {
        uint32_t nowI = get_operator_index(nowOp), sI = get_operator_index(sOp);
        return priTable[sI][nowI];
    }

    inline char Expression::reverse_compare_operator(const char nowOp, const char sOp) const
    {
        uint32_t nowI = get_operator_index(nowOp), sI = get_operator_index(sOp);
        return priTableReverse[sI][nowI];
    }

    Expression::ValueType Expression::read_num(const char *&p) const
    {
        std::string num;
        for (; isdigit(*p) || *p == '.'; ++p)
            num += *p;
        // printf("num = %s\n", num.c_str());
        return stod(num);
    }

    Expression::ValueType Expression::reverse_read_num(const char *&p) const
    {
        std::string num;
        for (; isdigit(*p) || *p == '.'; --p)
            num = *p + num;
        // printf("num = %s\n", num.c_str());
        return stod(num);
    }

    Expression::ValueType Expression::calc(const ValueType &lhs, const char op, const ValueType &rhs)
        const
    {
        ValueType ret;
        try
        {
            switch (op)
            {
            case '+':
                ret = lhs + rhs;
                break;
            case '-':
                ret = lhs - rhs;
                break;
            case '*':
                ret = lhs * rhs;
                break;
            case '/':
                ret = lhs / rhs;
                break;
            case '^':
                ret = pow(lhs, rhs);
                break;
            default:
            {
                throw "in function calc, unknown operator";
                break;
            }
            }
        }
        catch (const char *errMsg)
        {
            printf("Error %s: %c\n", errMsg, op);
            throw std::exception();
        }
        return ret;
    }

    Expression::ValueType Expression::calc(const ValueType &operand, const char op) const
    {
        ValueType ret;
        try
        {
            switch (op)
            {
            case '!':
                ret = Factorial(operand);
                break;
            default:
            {
                throw "in function calc, unknown operator";
                break;
            }
            }
        }
        catch (const char *errMsg)
        {
            printf("Error %s: %c\n", errMsg, op);
            throw std::exception();
        }
        return ret;
    }

    Expression::ValueType Expression::calc_value() const
    {
        Stack<ValueType> operandS; // 运算数栈
        Stack<char> operatorS;     // 运算符栈
        operatorS.push('\0');      // 哨兵运算符入栈

        const char *p = _exp + 1;
        while (!operatorS.empty())
        {
            try
            {
                char c = *p;
                if (c == _delimiter)
                {
                    ++p;
                    continue;
                }
                else if (isdigit(c))
                {
                    // 数的话读入数并进入运算数栈
                    operandS.push(read_num(p));
                }
                else
                {
                    char sOp = operatorS.top(), nowOp = c;

                    switch (compare_operator(nowOp, sOp))
                    {
                    case 'e':
                    {
                        throw "is not correct!";
                        break;
                    }
                    case '=': // 栈顶元素与当前运算符优先级相等，需要单纯弹出栈顶符号不计算
                    {
                        operatorS.pop();
                        ++p;
                        break;
                    }
                    case '<': // 栈顶元素的优先级更高，弹栈计算，并将新的运算结果入运算数栈
                    {
                        if (is_one_element_operator(sOp))
                        {
                            ValueType operand = operandS.top();
                            operandS.pop();
                            operandS.push(calc(operand, sOp));
                        }
                        else
                        {
                            ValueType rhs = operandS.top();
                            operandS.pop();
                            ValueType lhs = operandS.top();
                            operandS.pop();
                            operandS.push(calc(lhs, sOp, rhs));
                        }
                        operatorS.pop();
                        break;
                    }
                    case '>': // 当前元素的优先级更高，将当前运算符入栈
                    {
                        operatorS.push(nowOp);
                        ++p;
                        break;
                    }
                    }
                }
            }
            catch (const char *errMsg)
            {
                printf("Error: the expression %s %s\n", _exp, errMsg);
                throw std::exception();
            }
        }
        return operandS.top(); // 返回最终的运算结果
    }

    CZString Expression::to_RPN() const
    {
        Stack<char> operatorS; // 运算符栈
        operatorS.push('\0');  // 哨兵运算符入栈

        CZString RPN;

        const char *p = _exp + 1;
        while (!operatorS.empty())
        {
            try
            {
                char c = *p;
                if (c == _delimiter)
                {
                    ++p;
                    continue;
                }
                else if (isdigit(c))
                {
                    // 数的话读入数并进入运算数栈，并加到逆波兰表达式的后面
                    ValueType number = read_num(p);
                    // 默认保留两位小数
                    char temp[100];
                    sprintf(temp, "%.2f%c", number, _delimiter);

                    RPN += temp;
                }
                else
                {
                    char sOp = operatorS.top(), nowOp = c;

                    switch (compare_operator(nowOp, sOp))
                    {
                    case 'e':
                    {
                        throw "is not correct!";
                        break;
                    }
                    case '=': // 栈顶元素与当前运算符优先级相等，需要单纯弹出栈顶符号不计算
                    {
                        operatorS.pop();
                        ++p;
                        break;
                    }
                    case '<': // 栈顶元素的优先级更高，弹栈计算，并将新的运算结果入运算数栈
                    {
                        RPN += operatorS.top(); // 将运算符加到逆波兰表达式的末尾
                        RPN += _delimiter;
                        operatorS.pop();
                        break;
                    }
                    case '>': // 当前元素的优先级更高，将当前运算符入栈
                    {
                        operatorS.push(nowOp);
                        ++p;
                        break;
                    }
                    }
                }
            }
            catch (const char *errMsg)
            {
                printf("Error: the expression %s %s\n", _exp, errMsg);
                throw std::exception();
            }
        }
        return RPN;
    }

    CZString Expression::to_PN() const
    {
        Stack<char> operatorS; // 运算符栈
        operatorS.push('\0');  // 哨兵运算符入栈

        CZString PN;

        CZString::Rank l = strlen(_exp + 1);
        const char *p = _exp + l;
        while (!operatorS.empty())
        {
            try
            {
                char c = *p;
                if (c == _delimiter)
                {
                    --p;
                    continue;
                }
                else if (isdigit(c))
                {
                    // 数的话读入数并进入运算数栈，并加到逆波兰表达式的后面
                    ValueType number = reverse_read_num(p);
                    // 默认保留两位小数
                    char temp[100];
                    sprintf(temp, "%.2f%c", number, _delimiter);

                    PN = temp + PN;
                }
                else
                {
                    char sOp = operatorS.top(), nowOp = c;

                    switch (reverse_compare_operator(nowOp, sOp))
                    {
                    case 'e':
                    {
                        throw "is not correct!";
                        break;
                    }
                    case '=': // 栈顶元素与当前运算符优先级相等，需要单纯弹出栈顶符号不计算
                    {
                        operatorS.pop();
                        --p;
                        break;
                    }
                    case '<': // 栈顶元素的优先级更高，弹栈计算，并将新的运算结果入运算数栈
                    {
                        char temp[100];
                        sprintf(temp, "%c%c", sOp, _delimiter);
                        PN = temp + PN; // 将运算符加到波兰表达式的前端
                        operatorS.pop();
                        break;
                    }
                    case '>': // 当前元素的优先级更高，将当前运算符入栈
                    {
                        operatorS.push(nowOp);
                        --p;
                        break;
                    }
                    }
                }
            }
            catch (const char *errMsg)
            {
                printf("Error: the expression %s %s\n", _exp, errMsg);
                throw std::exception();
            }
        }
        return PN;
    }

    inline std::ostream &operator<<(std::ostream &os, const Expression &e) { return os; }
} // CZ
