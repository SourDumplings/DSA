/*
 * @Author: SourDumplings
 * @Date: 2022-10-24 18:16:08
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 基础实体类型
 */

#ifndef ABSTRACT_BASE_ENTITY_H
#define ABSTRACT_BASE_ENTITY_H

#include "../Algorithms/Hash.h"

#include <iostream>
#include <sstream>

namespace CZ
{
    class AbstractBaseEntity
    {
    public:
        AbstractBaseEntity();
        AbstractBaseEntity(const AbstractBaseEntity &entity);
        AbstractBaseEntity(AbstractBaseEntity &&entity);
        virtual ~AbstractBaseEntity();

        virtual const char *c_str() const = 0;

        virtual HashRank hash() const = 0;

        AbstractBaseEntity &operator=(const AbstractBaseEntity &rhs);
        AbstractBaseEntity &operator=(AbstractBaseEntity &&rhs);

        virtual const char *get_entity_name() const = 0;

    protected:
        const char *get_c_str_from_stream(const std::ostringstream &oss) const;

    private:
        mutable char *_pStr; // 存储字符串信息的指针
    };

    std::ostream &operator<<(std::ostream &os, const AbstractBaseEntity &rhs);
    bool operator==(const AbstractBaseEntity &lhs, const AbstractBaseEntity &rhs);
    bool operator!=(const AbstractBaseEntity &lhs, const AbstractBaseEntity &rhs);
}

#endif