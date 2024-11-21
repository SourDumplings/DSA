/*
 * @Author: SourDumplings
 * @Date: 2022-10-24 18:16:08
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 基础实体类型
 */

#ifndef ABSTRACT_BASE_ENTITY_H
#define ABSTRACT_BASE_ENTITY_H

#include "BaseDef.h"
#include "../Algorithms/Hash.h"

#include <iostream>
#include <sstream>

namespace DSA
{
    class DLL_EXPORT_IMPORT AbstractBaseEntity
    {
    public:
        AbstractBaseEntity();
        AbstractBaseEntity(const AbstractBaseEntity &entity);
        AbstractBaseEntity(AbstractBaseEntity &&entity) noexcept;
        virtual ~AbstractBaseEntity();

        virtual const char *c_str() const = 0;
        virtual HashRank hash() const = 0;
        virtual const char *get_entity_name() const = 0;

        AbstractBaseEntity &operator=(const AbstractBaseEntity &rhs);
        AbstractBaseEntity &operator=(AbstractBaseEntity &&rhs) noexcept;

    protected:
        const char *get_c_str_from_stream(const std::ostringstream &oss) const;

    private:
        mutable char *_pStr; // 存储字符串信息的指针
    };

    DLL_EXPORT_IMPORT std::ostream &operator<<(std::ostream &os, const AbstractBaseEntity &rhs);
    DLL_EXPORT_IMPORT bool operator==(const AbstractBaseEntity &lhs, const AbstractBaseEntity &rhs);
    DLL_EXPORT_IMPORT bool operator!=(const AbstractBaseEntity &lhs, const AbstractBaseEntity &rhs);
}

#endif