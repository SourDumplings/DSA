/*
 @Date    : 2018-08-12 21:24:23
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
集合类模板，由红黑树实现
 */

#ifndef SET_H
#define SET_H

#include "../Tree/BinTree/RedBlackTree.h"
#include "SetIterator.h"

namespace CZ
{
    template <typename T> class Set;

    template <typename T> bool operator==(const Set<T> &lhs, const Set<T> &rhs);
    template <typename T> bool operator!=(const Set<T> &lhs, const Set<T> &rhs);
    template <typename T> Set<T> operator+(const Set<T> &lhs, const Set<T> &rhs);
    template <typename T> Set<T> operator-(const Set<T> &lhs, const Set<T> &rhs);

    template <typename T>
    class Set
    {
        friend bool operator==<T>(const Set<T> &lhs, const Set<T> &rhs);
        friend bool operator!=<T>(const Set<T> &lhs, const Set<T> &rhs);
        friend Set<T> operator+<T>(const Set<T> &lhs, const Set<T> &rhs);
        friend Set<T> operator-<T>(const Set<T> &lhs, const Set<T> &rhs);
        friend class SetIterator<T>;
    public:
        using Rank = uint32_t;
        using Iterator = SetIterator<T>;

        Set();
        Set(const std::initializer_list<T> &l);
        Set(const T *begin, const T *end);
        template <typename It>
        Set(const It &begin, const It &end);
        Set(const Set<T> &s);
        Set(Set<T> &&s);

        // 数据访问接口
        Rank size() const;
        bool empty() const;
        bool contains(const T &value) const;
        Iterator begin();
        Iterator begin() const;
        Iterator end();
        Iterator end() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        // 插入，如果该值已经存在则插入失败，即什么都不做，返回 false
        bool insert(const T &value);
        // 删除，成功返回true，失败返回false或者抛出异常
        bool remove(const T &value, bool nonexcept = true);
        void clear();

        Set<T>& operator=(const Set<T>& s);
        Set<T>& operator=(Set<T>&& s);

        void print_info(const char *name = "") const;

        static Set<T> intersection(const Set<T> &s1, const Set<T> &s2);
    private:
        RedBlackTree<T> _T;

        template <typename It>
        void _construct_from(const It &begin, const It &end);
    };
} // CZ

#include "Set_implementation.h"
#include "Set_operations.h"

#endif // SET_H

