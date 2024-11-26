/*
 @Date    : 2018-04-10 21:31:27
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
当小于装填因子时
Vector类模板的缩容操作
 */

#ifndef VECTOR_SHRINK_H
#define VECTOR_SHRINK_H

#include "Vector.h"

namespace DSA
{
template <typename T>
bool Vector<T>::_shrink()
{
	// 以12.5%为界
	if (_need_shrink())
	{
		T *oldElem = _elem;
		while (_need_shrink())
		{
			_capacity >>= 1;
		}

		if constexpr (IsMemoryCopyable<T>::_value)
		{
			_elem = reinterpret_cast<T *>(malloc(_capacity * sizeof(T)));
			memcpy(
				reinterpret_cast<void *>(_elem),
				reinterpret_cast<void *>(oldElem),
				_capacity * sizeof(T)
			);
			free(oldElem);
		}
		else
		{
			_elem = new T[_capacity];
			for (uint32_t i = 0; i < _size; ++i)
			{
				_elem[i] = oldElem[i];
			}
			delete[] oldElem;
		}

		return true;
	}
	return false;
}

template <typename T>
inline bool Vector<T>::_need_shrink() const
{
	return (_size << 2) < _capacity;
}
}  // namespace DSA

#endif	// VECTOR_SHRINK_H
