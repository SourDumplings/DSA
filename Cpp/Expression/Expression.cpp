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

#include "Expression.h"
#include "../Stack/Stack.h"
#include "../Algorithms/Factorial.h"

namespace CZ
{
    Expression::Expression(const char *exp_, const char delimiter_):
    _exp(exp_), _delimiter(delimiter_) {}

    Expression::Expression(const string &exp_, const char delimiter_):
    Expression(exp_.c_str(), delimiter_) {}

    void Expression::print_info(const char *name) const
    {
        printf("expression %s is: %s\n\n", name, _exp);
        return;
    }

    bool inline Expression::is_one_element_operator(const char op) const
    { return op == '!'; }

    unsigned Expression::get_operator_index(const char op) const
    {
        unsigned ret;
        try
        {
            switch (op)
            {
                case '+': ret = 0; break;
                case '-': ret = 1; break;
                case '*': ret = 2; break;
                case '/': ret = 3; break;
                case '^': ret = 4; break;
                case '!': ret = 5; break;
                case '(': ret = 6; break;
                case ')': ret = 7; break;
                case '\0': ret = 8; break;
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
        unsigned nowI = get_operator_index(nowOp), sI = get_operator_index(sOp);
        return priTable[sI][nowI];
    }

    Expression::ValueType Expression::read_num(const char *&p) const
    {
        string num;
        for (; isdigit(*p) || *p == '.'; ++p) num += *p;
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
                case '+': ret = lhs + rhs; break;
                case '-': ret = lhs - rhs; break;
                case '*': ret = lhs * rhs; break;
                case '/': ret = lhs / rhs; break;
                case '^': ret = pow(lhs, rhs); break;
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
                case '!': ret = Factorial(operand); break;
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
        Stack<char> operatorS; // 运算符栈
        operatorS.push('\0'); // 哨兵运算符入栈

        const char *p = _exp;
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
                                ValueType operand = operandS.top(); operandS.pop();
                                operandS.push(calc(operand, sOp));
                            }
                            else
                            {
                                ValueType rhs = operandS.top(); operandS.pop();
                                ValueType lhs = operandS.top(); operandS.pop();
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

} // CZ

