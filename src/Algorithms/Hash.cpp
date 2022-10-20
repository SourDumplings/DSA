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
        return value - INT8_MIN;
    }

    HashRank Hash<uint8_t>::operator()(const uint8_t &value) const
    {
        return value;
    }

    HashRank Hash<int16_t>::operator()(const int16_t &value) const
    {
        return value - INT16_MIN;
    }

    HashRank Hash<uint16_t>::operator()(const uint16_t &value) const
    {
        return value;
    }

    HashRank Hash<int32_t>::operator()(const int32_t &value) const
    {
        return value - INT32_MIN;
    }

    HashRank Hash<uint32_t>::operator()(const uint32_t &value) const
    {
        return value;
    }

    HashRank Hash<int64_t>::operator()(const int64_t &value) const
    {
        return value - INT64_MIN;
    }

    HashRank Hash<uint64_t>::operator()(const uint64_t &value) const
    {
        return value;
    }

    HashRank Hash<float>::operator()(const float &value) const
    {
        return Hash<uint64_t>()(*reinterpret_cast<const uint64_t *>(&value));
    }

    HashRank Hash<double>::operator()(const double &value) const
    {
        return Hash<uint64_t>()(*reinterpret_cast<const uint64_t *>(&value));
    }
}