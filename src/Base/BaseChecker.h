#pragma once

#include <type_traits>
#include "AbstractBaseEntity.h"

namespace DSA
{

/**
 * @brief 判断某个类型是否是内存拷贝的，即可以直接使用 memcpy 等操作拷贝其内存布局
 *
 * @tparam T
 */
template <typename T>
struct IsMemoryCopyable
{
	static constexpr bool _value =
		std::is_trivially_copyable_v<T> || std::is_base_of_v<AbstractBaseEntity, T>;
};

// 特化类型
// template <>
// struct IsMemoryCopyable<MySpecialType>
// {
// 	static constexpr bool _value = true;
// };
}  // namespace DSA
