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
#include <string>
#include <cstddef>

namespace CZ
{
    using HashRank = uint64_t;
    constexpr HashRank CZ_MAX_HASH_VALUE = UINT64_MAX;

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
    template <>
    class Hash<const bool>
    {
    public:
        HashRank operator()(const bool &value) const;
    };

    template <>
    class Hash<const char>
    {
    public:
        HashRank operator()(const char &value) const;
    };

    template <>
    class Hash<const int8_t>
    {
    public:
        HashRank operator()(const int8_t &value) const;
    };

    template <>
    class Hash<const uint8_t>
    {
    public:
        HashRank operator()(const uint8_t &value) const;
    };

    template <>
    class Hash<const int16_t>
    {
    public:
        HashRank operator()(const int16_t &value) const;
    };

    template <>
    class Hash<const uint16_t>
    {
    public:
        HashRank operator()(const uint16_t &value) const;
    };

    template <>
    class Hash<const int32_t>
    {
    public:
        HashRank operator()(const int32_t &value) const;
    };

    template <>
    class Hash<const uint32_t>
    {
    public:
        HashRank operator()(const uint32_t &value) const;
    };

    template <>
    class Hash<const int64_t>
    {
    public:
        HashRank operator()(const int64_t &value) const;
    };

    template <>
    class Hash<const uint64_t>
    {
    public:
        HashRank operator()(const uint64_t &value) const;
    };

    template <>
    class Hash<const float>
    {
    public:
        HashRank operator()(const float &value) const;
    };

    template <>
    class Hash<const double>
    {
    public:
        HashRank operator()(const double &value) const;
    };

    template <>
    class Hash<const std::string>
    {
    public:
        HashRank operator()(const std::string &value) const;
    };

    template <>
    class Hash<bool>
    {
    public:
        HashRank operator()(const bool &value) const;
    };

    template <>
    class Hash<std::nullptr_t>
    {
    public:
        HashRank operator()(const std::nullptr_t &value) const;
    };

    template <>
    class Hash<char>
    {
    public:
        HashRank operator()(const char &value) const;
    };

    template <>
    class Hash<int8_t>
    {
    public:
        HashRank operator()(const int8_t &value) const;
    };

    template <>
    class Hash<uint8_t>
    {
    public:
        HashRank operator()(const uint8_t &value) const;
    };

    template <>
    class Hash<int16_t>
    {
    public:
        HashRank operator()(const int16_t &value) const;
    };

    template <>
    class Hash<uint16_t>
    {
    public:
        HashRank operator()(const uint16_t &value) const;
    };

    template <>
    class Hash<int32_t>
    {
    public:
        HashRank operator()(const int32_t &value) const;
    };

    template <>
    class Hash<uint32_t>
    {
    public:
        HashRank operator()(const uint32_t &value) const;
    };

    template <>
    class Hash<int64_t>
    {
    public:
        HashRank operator()(const int64_t &value) const;
    };

    template <>
    class Hash<uint64_t>
    {
    public:
        HashRank operator()(const uint64_t &value) const;
    };

    template <>
    class Hash<float>
    {
    public:
        HashRank operator()(const float &value) const;
    };

    template <>
    class Hash<double>
    {
    public:
        HashRank operator()(const double &value) const;
    };

    template <>
    class Hash<std::string>
    {
    public:
        HashRank operator()(const std::string &value) const;
    };

    // 对于指针，直接将其底层位模式按照 HashRank 解释即可
    template <typename T>
    class Hash<T *>
    {
    public:
        HashRank operator()(T *const &value) const
        {
            return Hash<HashRank>()(reinterpret_cast<HashRank>(value));
        }
    };

    template <typename T>
    class Hash<const T *>
    {
    public:
        HashRank operator()(const T *const &value) const
        {
            return Hash<HashRank>()(reinterpret_cast<const HashRank>(value));
        }
    };

    template <typename T>
    class Hash<T *const>
    {
    public:
        HashRank operator()(const T *const &value) const
        {
            return Hash<HashRank>()(reinterpret_cast<const HashRank>(value));
        }
    };

    template <typename T>
    class Hash<const T *const>
    {
    public:
        HashRank operator()(const T *const &value) const
        {
            return Hash<HashRank>()(reinterpret_cast<const HashRank>(value));
        }
    };
}

#endif