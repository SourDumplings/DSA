/*
 @Date    : 2018-05-15 14:34:53
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Bitmap类的实现
使用连续申请的空间_m[]，并依次将其中的各比特位与位图集合中的各个整数
一一对应。实现了向量一般的循秩访问的高效性，同时极大地节约了空间
如果集合中包含整数k，那么该段空间中的第k个比特位为1，否则为0;
使用如下方法实现了上述的对应关系：
1.通常而言，每个字节包含8个位，故通过移位运算k >> 3（即k / 8）
即可确定对应的比特位所属字节的秩；
2.通过逻辑位与运算：k & 0x07，(即k % 8)
即可确定该比特位在此字节中的位置
3.最后通过移位操作：0x80 >> (k & 0x07)
即可得到该比特位在此字节中对应的数值掩码。
比如说第14位（00001110），其所在的字节的秩为1，在字节中对应为第6位
则其对应的掩码为00000010
在局部将此字节与该掩码做按位或，即可将整数k所对应的比特位设置为1；即_m[1]的第2位设置为1
在局部将此字节与该掩码做按位与，即可测试该比特位的状态；即查看_m[1]的第2为是否为1
在局部将此字节与该掩码按位取反后做按位与，即可将整数k所对应的比特位设置为0；即将_m[1]的第2位设置为0
 */

#include "Bitmap.h"
#include <cstring>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <iostream>

namespace CZ
{
    // 初始化函数
    void Bitmap::init(Bitmap::Rank n_)
    {
        _m = new char[_n = (n_ + 7) >> 3];
        memset(_m, 0, _n);
        return;
    }

    // 构造函数
    Bitmap::Bitmap(Bitmap::Rank n_)
    {
        init(n_);
        return;
    }

    Bitmap::Bitmap(const char *file, Bitmap::Rank n_)
    {
        init(n_);
        try
        {
            FILE *fp = fopen(file, "r");
            if (fp)
            {
                fread(_m, sizeof(char), _n, fp);
                fclose(fp);
            }
            else
                throw "can't open this file";
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }

        return;
    }

    // 析构函数
    Bitmap::~Bitmap()
    {
        delete [] _m;
        return;
    }

    // 扩容函数
    void Bitmap::expand(Bitmap::Rank k)
    {
        if (k < 8 * _n)
        {
            // 无需扩容
            return;
        }
        // printf("$$k = %d, _n = %d, need expand!$$\n", k, _n);
        Bitmap::Rank oldN = _n;
        char *oldM = _m;
        init(2 * k);
        memcpy(_m, oldM, oldN);
        delete oldM;
        return;
    }

    // 访问接口函数
    void Bitmap::dump(const char *file)
    {
        try
        {
            FILE *fp = fopen(file, "w");
            if (fp)
            {
                fwrite(_m, sizeof(char), _n, fp);
                fclose(fp);
            }
            else
                throw "can't open this file";
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    std::string Bitmap::bits2string(Bitmap::Rank n_)
    {
        expand(n_ - 1); // 此时可能被访问的最高位为Bitmap[n_-1]
        std::string res;
        res.resize(n_);
        for (Bitmap::Rank i = 0; i < n_; ++i)
        {
            res[i] = test(i) ? '1' : '0';
        }
        return res;
    }

    bool Bitmap::test(Bitmap::Rank k)
    {
        expand(k);
        return _m[k >> 3] & (0x80 >> (k & 0x07));
    }

    // 动态接口
    void Bitmap::set(Bitmap::Rank k)
    {
        expand(k);
        _m[k >> 3] |= (0x80 >> (k & 0x07));
        return;
    }

    void Bitmap::clear(Bitmap::Rank k)
    {
        expand(k);
        _m[k >> 3] &= ~(0x80 >> (k & 0x07));
        return;
    }

    // 打印位域的信息
    void Bitmap::print_info(const char *name)
    {
        printf("Bitmap %s: \n", name);
        printf("contains: ");
        for (Bitmap::Rank i = 0; i < _n * 8; ++i)
        {
            if (test(i))
            {
                printf("%d ", i);
            }
        }
        printf("\n\n");
        return;
    }

    inline std::ostream& operator<<(std::ostream &os, const Bitmap &b) { return os; }
} // CZ

