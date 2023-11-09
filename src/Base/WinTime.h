/**
 * @file WinTime.h
 * @author chadchang (chadchang@tencent.com)
 * @brief 实现一些 Windows 平台下一些时间相关定义，参考：https://blog.csdn.net/CUSTESC/article/details/104968050
 * @version 1.0.0
 * @date 2023-11-09
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#ifndef WINTIME_H
#define WINTIME_H

#include "BaseDef.h"
#include<chrono>

#ifdef _WIN32
struct DLL_EXPORT_IMPORT timeval
{
    __int64 tv_sec;
    __int64 tv_usec;
};

DLL_EXPORT_IMPORT void gettimeofday(struct timeval *tv, void *);
#endif

#endif // WINTIME_H