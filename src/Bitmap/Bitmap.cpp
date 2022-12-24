/*
 @Date    : 2018-05-15 14:34:53
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Bitmap类的实现
使用连续申请的空间 _m[]，并依次将其中的各比特位与位图集合中的各个整数
一一对应。实现了向量一般的循秩访问的高效性，同时极大地节约了空间
如果集合中包含整数k，那么该段空间中的第k个比特位为 1，否则为 0;
使用如下方法实现了上述的对应关系：
1.通常而言，每个字节包含 8 个位，故通过移位运算 k >> 3（即 k / 8）
即可确定对应的比特位所属字节的秩；
2.通过逻辑位与运算：k & 0x07，(即 k % 8)
即可确定该比特位在此字节中的位置
3.最后通过移位操作：0x80 >> (k & 0x07)
即可得到该比特位在此字节中对应的数值掩码。
比如说第 14 位（00001110），其所在的字节的秩为 1，在字节中对应为第 6 位
则其对应的掩码为 00000010
在局部将此字节与该掩码做按位或，即可将整数 k 所对应的比特位设置为 1；即 _m[1] 的第 2 位设置为 1
在局部将此字节与该掩码做按位与，即可测试该比特位的状态；即查看 _m[1] 的第 2 位是否为 1
在局部将此字节与该掩码按位取反后做按位与，即可将整数 k 所对应的比特位设置为 0；即将 _m[1] 的第 2 位设置为 0
 */

#include "Bitmap.h"

// #include <bitset>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

namespace CZ
{
    // 初始化函数
    void Bitmap::init(Bitmap::Rank n_)
    {
        _m = new char[_charNum = (n_ + 7) >> 3];
        memset(_m, 0, _charNum);
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
        FILE *fp = fopen(file, "r");
        ASSERT_DEBUG(fp, "can't open this file");
        fread(_m, sizeof(char), _charNum, fp);
        fclose(fp);
    }

    // 析构函数
    Bitmap::~Bitmap()
    {
        delete[] _m;
        return;
    }

    // 扩容函数
    void Bitmap::expand(Bitmap::Rank k)
    {
        if (k < 8 * sizeof(char) * _charNum)
        {
            // 无需扩容
            return;
        }
        // printf("$$k = %d, _charNum = %d, need expand!$$\n", k, _charNum);
        Bitmap::Rank oldN = _charNum;
        char *oldM = _m;
        init(2 * k);
        memcpy(_m, oldM, oldN);
        delete[] oldM;
    }

    // 访问接口函数
    void Bitmap::dump(const char *file) const
    {
        FILE *fp = fopen(file, "w");
        ASSERT_DEBUG(fp, "can't open this file");
        fwrite(_m, sizeof(char), _charNum, fp);
        fclose(fp);
    }

    CZString Bitmap::bits2czstring(typename Bitmap::Rank n_) const
    {
        CZString res;
        Rank maxNum = n_;
        if (sizeof(char) * _charNum * 8 < n_)
        {
            maxNum = sizeof(char) * _charNum * 8;
        }

        res.resize(maxNum);
        for (Rank i = 0; i < maxNum; i++)
        {
            res[i] = test(i) ? '1' : '0';
        }
        res.reverse();
        return res;
    }

    bool Bitmap::test(Bitmap::Rank k) const
    {
        if (8 * sizeof(char) * _charNum <= k)
        {
            return false;
        }

        return _m[k >> 3] & (0x80 >> (k & 0x07));
    }

    // 动态接口
    void Bitmap::set(Bitmap::Rank k)
    {
        // printf("before set %u\n", k);
        // std::cout << "_m[k >> 3]: " << std::bitset<8>(_m[k >> 3]) << std::endl;
        expand(k);
        _m[k >> 3] |= (0x80 >> (k & 0x07));
        // std::cout << "_m[k >> 3]: " << std::bitset<8>(_m[k >> 3]) << std::endl;
        // printf("after set %u\n", k);
    }

    void Bitmap::clear(Bitmap::Rank k)
    {
        if (8 * sizeof(char) <= k)
        {
            return;
        }

        _m[k >> 3] &= ~(0x80 >> (k & 0x07));
    }

    // 打印位域的信息
    void Bitmap::print_info(const char *name)
    {
        printf("Bitmap %s: \n", name);
        printf("contains: ");
        for (Rank i = 0; i < _charNum * sizeof(char) * 8; ++i)
        {
            if (test(i))
            {
                printf("%d ", i);
            }
        }
        printf("\n\n");

        // for (Rank i = 0; i < _charNum; ++i)
        // {
        //     std::cout << "_m[" << i << "] = " << std::bitset<8>(_m[i]) << std::endl;
        // }
        return;
    }

    const char *Bitmap::c_str() const
    {
        std::ostringstream oss;
        oss << this->get_entity_name() << "(" << bits2czstring(_charNum * sizeof(char) * 8) << ")";
        return this->get_c_str_from_stream(oss);
    }

    HashRank Bitmap::hash() const
    {
        HashRank res = Hash<CZString>()(get_entity_name());
        for (Bitmap::Rank i = 0; i < _charNum * 8 * sizeof(char); ++i)
        {
            if (test(i))
            {
                res = (res + Hash<Rank>()(i)) % CZ_MAX_HASH_VALUE;
            }
        }
        return res;
    }

    const char *Bitmap::get_entity_name() const
    {
        return "Bitmap";
    }

} // CZ
