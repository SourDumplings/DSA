/*
 * @Author: SourDumplings
 * @Date: 2022-08-19 20:05:37
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 哈希算法，将一个对象哈希为一个整数
 */

#ifndef HASH_H
#define HASH_H

#include "../Base/BaseDef.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <cstddef>
#include <type_traits>

namespace CZ
{
    using HashRank = uint64_t;
    constexpr HashRank CZ_MAX_HASH_VALUE = UINT64_MAX;

    /**
     * @brief 判断是否定义了自己的哈希函数，即 hash，可见性必须是 public 才行
     *
     * @tparam T
     */
    class HasDefineOwnHashMethod
    {
    public:
        template <typename C> static std::true_type test(decltype(&C::hash))
        {
            return std::true_type();
        }
        template <typename C> static std::false_type test(...)
        {
            return std::false_type();
        }

    private:
        HasDefineOwnHashMethod();
    };

    // 默认哈希算法
    template <typename T>
    class Hash
    {
    public:
        HashRank operator()(const T &target) const
        {
            return invoke_hash(target, HasDefineOwnHashMethod::test<T>(nullptr));
        }

    private:
        HashRank invoke_hash(const T &target, const std::true_type &) const
        {
            return target.hash();
        }

        HashRank invoke_hash(const T &target, const std::false_type &) const
        {
            return reinterpret_cast<HashRank>(&target);
        }
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const bool>
    {
    public:
        HashRank operator()(const bool &value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const char>
    {
    public:
        HashRank operator()(const char& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const int8_t>
    {
    public:
        HashRank operator()(const int8_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const uint8_t>
    {
    public:
        HashRank operator()(const uint8_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const int16_t>
    {
    public:
        HashRank operator()(const int16_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const uint16_t>
    {
    public:
        HashRank operator()(const uint16_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const int32_t>
    {
    public:
        HashRank operator()(const int32_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const uint32_t>
    {
    public:
        HashRank operator()(const uint32_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const int64_t>
    {
    public:
        HashRank operator()(const int64_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const uint64_t>
    {
    public:
        HashRank operator()(const uint64_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const float>
    {
    public:
        HashRank operator()(const float& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const double>
    {
    public:
        HashRank operator()(const double& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<const std::string>
    {
    public:
        HashRank operator()(const std::string& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<bool>
    {
    public:
        HashRank operator()(const bool& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<std::nullptr_t>
    {
    public:
        HashRank operator()(const std::nullptr_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<char>
    {
    public:
        HashRank operator()(const char& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<int8_t>
    {
    public:
        HashRank operator()(const int8_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<uint8_t>
    {
    public:
        HashRank operator()(const uint8_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<int16_t>
    {
    public:
        HashRank operator()(const int16_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<uint16_t>
    {
    public:
        HashRank operator()(const uint16_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<int32_t>
    {
    public:
        HashRank operator()(const int32_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<uint32_t>
    {
    public:
        HashRank operator()(const uint32_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<int64_t>
    {
    public:
        HashRank operator()(const int64_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<uint64_t>
    {
    public:
        HashRank operator()(const uint64_t& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<float>
    {
    public:
        HashRank operator()(const float& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<double>
    {
    public:
        HashRank operator()(const double& value) const;
    };

    template <>
    class DLL_EXPORT_IMPORT Hash<std::string>
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