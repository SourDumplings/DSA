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
    class Hash
    {
    public:
        HashRank operator()(const T &value) const
        {
            return value.hash();
        }
    };

    // 针对一些特定类型的哈希算法
    template<>
    class Hash<bool>
    {
    public:
        HashRank operator()(const bool &value) const;
    };

    template<>
    class Hash<nullptr_t>
    {
    public:
        HashRank operator()(const nullptr_t &value) const;
    };

    template<>
    class Hash<char>
    {
    public:
        HashRank operator()(const char &value) const;
    };

    template<>
    class Hash<int8_t>
    {
    public:
        HashRank operator()(const int8_t &value) const;
    };

    template<>
    class Hash<uint8_t>
    {
    public:
        HashRank operator()(const uint8_t &value) const;
    };

    template<>
    class Hash<int16_t>
    {
    public:
        HashRank operator()(const int16_t &value) const;
    };

    template<>
    class Hash<uint16_t>
    {
    public:
        HashRank operator()(const uint16_t &value) const;
    };

    template<>
    class Hash<int32_t>
    {
    public:
        HashRank operator()(const int32_t &value) const;
    };

    template<>
    class Hash<uint32_t>
    {
    public:
        HashRank operator()(const uint32_t &value) const;
    };

    template<>
    class Hash<int64_t>
    {
    public:
        HashRank operator()(const int64_t &value) const;
    };

    template<>
    class Hash<uint64_t>
    {
    public:
        HashRank operator()(const uint64_t &value) const;
    };

    template<>
    class Hash<float>
    {
    public:
        HashRank operator()(const float &value) const;
    };

    template<>
    class Hash<double>
    {
    public:
        HashRank operator()(const double &value) const;
    };
}

#endif