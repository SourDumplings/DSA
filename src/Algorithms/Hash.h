/*
 * @Author: SourDumplings
 * @Date: 2022-08-19 20:05:37
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 哈希算法，将一个对象哈希为一个整数
 */

#ifndef HASH_H
#define HASH_H

#include <cstddef>
#include <cstdint>

namespace CZ
{
    using HashRank = uint64_t;

    // 默认哈希算法
    template <typename T>
    HashRank Hash(const T &value)
    {
        return value.hash();
    }

    // 针对一些特定类型的哈希算法
    template <>
    HashRank Hash<bool>(const bool &value);

    template <>
    HashRank Hash<nullptr_t>(const nullptr_t &value);

    template <>
    HashRank Hash<char>(const char &value);

    template <>
    HashRank Hash<int8_t>(const int8_t &value);

    template <>
    HashRank Hash<uint8_t>(const uint8_t &value);

    template <>
    HashRank Hash<int16_t>(const int16_t &value);

    template <>
    HashRank Hash<uint16_t>(const uint16_t &value);

    template <>
    HashRank Hash<int32_t>(const int32_t &value);

    template <>
    HashRank Hash<uint32_t>(const uint32_t &value);

    template <>
    HashRank Hash<int64_t>(const int64_t &value);

    template <>
    HashRank Hash<uint64_t>(const uint64_t &value);

    template <>
    HashRank Hash<float>(const float &value);

    template <>
    HashRank Hash<double>(const double &value);
}

#endif