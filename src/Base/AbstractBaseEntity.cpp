/*
 * @Author: SourDumplings
 * @Date: 2022-10-27 19:56:11
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#include "AbstractBaseEntity.h"

#include <cstdlib>
#include <cstring>

namespace CZ
{
    AbstractBaseEntity::AbstractBaseEntity() : _pStr(nullptr) {}

    AbstractBaseEntity::AbstractBaseEntity(const AbstractBaseEntity &entity)
        : _pStr(nullptr)
    {
        if (entity._pStr)
        {
            _pStr = static_cast<char *>(malloc(sizeof(char) * (strlen(entity._pStr) + 1)));
            strcpy(_pStr, entity._pStr);
        }
    }

    AbstractBaseEntity::AbstractBaseEntity(AbstractBaseEntity &&entity)
        : _pStr(entity._pStr)
    {
        entity._pStr = nullptr;
    }

    AbstractBaseEntity::~AbstractBaseEntity()
    {
        if (_pStr)
        {
            free(_pStr);
        }
    }

    std::ostream &operator<<(std::ostream &os, const AbstractBaseEntity &rhs)
    {
        return os << rhs.c_str();
    }

    AbstractBaseEntity &AbstractBaseEntity::operator=(const AbstractBaseEntity &rhs)
    {
        if (&(rhs) != this)
        {
            if (_pStr)
            {
                free(_pStr);
            }
            if (rhs._pStr)
            {
                _pStr = static_cast<char *>(malloc(sizeof(char) * (strlen(rhs._pStr) + 1)));
                strcpy(_pStr, rhs._pStr);
            }
            else
            {
                _pStr = nullptr;
            }
        }
        return *this;
    }

    AbstractBaseEntity &AbstractBaseEntity::operator=(AbstractBaseEntity &&rhs)
    {
        if (&(rhs) != this)
        {
            if (_pStr)
            {
                free(_pStr);
            }
            _pStr = rhs._pStr;
            rhs._pStr = nullptr;
        }
        return *this;
    }

    bool operator==(const AbstractBaseEntity &lhs, const AbstractBaseEntity &rhs)
    {
        return lhs.hash() == rhs.hash();
    }

    bool operator!=(const AbstractBaseEntity &lhs, const AbstractBaseEntity &rhs)
    {
        return !(lhs == rhs);
    }

    const char *AbstractBaseEntity::get_c_str_from_stream(const std::ostringstream &oss) const
    {
        if (_pStr)
        {
            free(_pStr);
        }
        this->_pStr = static_cast<char *>(malloc(sizeof(char) * (oss.str().length() + 1)));
        strcpy(this->_pStr, oss.str().c_str());
        return _pStr;
    }
}