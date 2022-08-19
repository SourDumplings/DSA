/*
 * @Author: SourDumplings
 * @Date: 2021-11-17 10:54:43
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 算法模板的特化实现
 */

#include "Hash.h"
#include "Swap.h"


namespace CZ
{
    template <>
    void Swap<int>(int &a, int &b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }

    template <>
    HashRank Hash<bool>(const bool &value)
    {
        return value ? 1 : 0;
    }

    template <>
    HashRank Hash<nullptr_t>(const nullptr_t &value)
    {
        return 0;
    }

    template <>
    HashRank Hash<char>(const char &value)
    {
        return Hash(value - '\0');
    }

    template <>
    HashRank Hash<int8_t>(const int8_t &value)
    {
        return value - INT8_MIN;
    }

    template <>
    HashRank Hash<uint8_t>(const uint8_t &value)
    {
        return value; 
    }

    template <>
    HashRank Hash<int16_t>(const int16_t &value)
    {
        return value - INT16_MIN;
    }

    template <>
    HashRank Hash<uint16_t>(const uint16_t &value)
    {
        return value;
    }

    template <>
    HashRank Hash<int32_t>(const int32_t &value)
    {
        return value - INT32_MIN;
    }

    template <>
    HashRank Hash<uint32_t>(const uint32_t &value)
    {
        return value;
    }

    template <>
    HashRank Hash<int64_t>(const int64_t &value)
    {
        return value - INT64_MIN;
    }

    template <>
    HashRank Hash<uint64_t>(const uint64_t &value)
    {
        return value;
    }

    template <>
    HashRank Hash<float>(const float &value)
    {
        return Hash(*reinterpret_cast<const uint64_t *>(&value));
    }

    template <>
    HashRank Hash<double>(const double &value)
    {
        return Hash(*reinterpret_cast<const uint64_t *>(&value));
    }
}
