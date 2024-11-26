/*
 @Date    : 2018-04-06 19:46:48
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector的构造函数
 */

#ifndef VECTOR_CONSTRUCTORS_H
#define VECTOR_CONSTRUCTORS_H

#include "Vector.h"

namespace DSA
{
template <typename T>
Vector<T>::Vector(Vector<T>::Rank s)
	: _elem(nullptr)
	, _size(s)
	, _capacity(s * 2)
{
	if constexpr (IsMemoryCopyable<T>::_value)
	{
		_elem = reinterpret_cast<T *>(malloc(_capacity * sizeof(T)));
		for (Rank i = 0; i != s; ++i)
		{
			new (_elem + i) T();
		}
	}
    else
    {
        _elem = new T[_capacity];
    }
}

template <typename T>
template <typename It>
Vector<T>::Vector(const It &begin, const It &end)
	: _elem(nullptr)
	, _size(0)
	, _capacity(0)
{
	_init_from(begin, end);
}

template <typename T>
Vector<T>::Vector(const T *begin, const T *end)
	: _elem(nullptr)
	, _size(0)
	, _capacity(0)
{
	_init_from(begin, end);
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> &initL)
	: _elem(nullptr)
	, _size(0)
	, _capacity(0)
{
	// printf("initL construct\n");
	_init_from(initL.begin(), initL.end());
}
}  // namespace DSA

#endif	// VECTOR_CONSTRUCTORS_H
