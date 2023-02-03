/*
 * @Author: SourDumplings
 * @Date: 2021-11-17 10:54:43
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: Hash 算法模板的特化实现
 */

#include "Hash.h"

namespace CZ
{
    HashRank Hash<const bool>::operator()(const bool &value) const
    {
        return value ? 1 : 0;
    }

    HashRank Hash<const nullptr_t>::operator()(const nullptr_t &value) const
    {
        return 0;
    }

    HashRank Hash<const char>::operator()(const char &value) const
    {
        return Hash<int32_t>()(value - '\0');
    }

    HashRank Hash<const int8_t>::operator()(const int8_t &value) const
    {
        return value < 0 ? value - INT8_MIN : value;
    }

    HashRank Hash<const uint8_t>::operator()(const uint8_t &value) const
    {
        return value;
    }

    HashRank Hash<const int16_t>::operator()(const int16_t &value) const
    {
        return value < 0 ? value - INT16_MIN : value;
    }

    HashRank Hash<const uint16_t>::operator()(const uint16_t &value) const
    {
        return value;
    }

    HashRank Hash<const int32_t>::operator()(const int32_t &value) const
    {
        return value < 0 ? value - INT32_MIN : value;
    }

    HashRank Hash<const uint32_t>::operator()(const uint32_t &value) const
    {
        return value;
    }

    HashRank Hash<const int64_t>::operator()(const int64_t &value) const
    {
        return value < 0 ? value - INT64_MIN : value;
    }

    HashRank Hash<const uint64_t>::operator()(const uint64_t &value) const
    {
        return value;
    }

    HashRank Hash<const float>::operator()(const float &value) const
    {
        return Hash<uint64_t>()(reinterpret_cast<uint64_t>(&value));
    }

    HashRank Hash<const double>::operator()(const double &value) const
    {
        return Hash<uint64_t>()(reinterpret_cast<uint64_t>(&value));
    }

    HashRank Hash<const std::string>::operator()(const std::string &value) const
    {
        HashRank hashValue = 0;
        const char *containerName = "string";
        for (const char *p = containerName; p && *p != '\0'; ++p)
        {
            hashValue = ((hashValue ^ Hash<const char>()(*p)) << 8) | ((hashValue >> 56) & 0xF);
        }

        for (const char c : value)
        {
            hashValue = ((hashValue ^ Hash<const char>()(c)) << 8) | ((hashValue >> 56) & 0xF);
        }
        return hashValue;
    }

    HashRank Hash<bool>::operator()(const bool &value) const
    {
        return value ? 1 : 0;
    }

    HashRank Hash<nullptr_t>::operator()(const nullptr_t &value) const
    {
        return 0;
    }

    HashRank Hash<char>::operator()(const char &value) const
    {
        return Hash<int32_t>()(value - '\0');
    }

    HashRank Hash<int8_t>::operator()(const int8_t &value) const
    {
        return value < 0 ? value - INT8_MIN : value;
    }

    HashRank Hash<uint8_t>::operator()(const uint8_t &value) const
    {
        return value;
    }

    HashRank Hash<int16_t>::operator()(const int16_t &value) const
    {
        return value < 0 ? value - INT16_MIN : value;
    }

    HashRank Hash<uint16_t>::operator()(const uint16_t &value) const
    {
        return value;
    }

    HashRank Hash<int32_t>::operator()(const int32_t &value) const
    {
        return value < 0 ? value - INT32_MIN : value;
    }

    HashRank Hash<uint32_t>::operator()(const uint32_t &value) const
    {
        return value;
    }

    HashRank Hash<int64_t>::operator()(const int64_t &value) const
    {
        return value < 0 ? value - INT64_MIN : value;
    }

    HashRank Hash<uint64_t>::operator()(const uint64_t &value) const
    {
        return value;
    }

    HashRank Hash<float>::operator()(const float &value) const
    {
        return Hash<uint64_t>()(reinterpret_cast<uint64_t>(&value));
    }

    HashRank Hash<double>::operator()(const double &value) const
    {
        return Hash<uint64_t>()(reinterpret_cast<uint64_t>(&value));
    }

    HashRank Hash<std::string>::operator()(const std::string &value) const
    {
        return Hash<const std::string>()(value);
    }
}
