/**
 * @file BaseDef.h
 * @author chadchang (chadchang@tencent.com)
 * @brief 基本定义
 * @version 1.0.0
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#if !defined(BASE_DEFINE_H)
#define BASE_DEFINE_H

#ifdef _WIN32
    #ifdef DLL_EXPORT
        #define DLL_EXPORT_IMPORT __declspec(dllexport)  
    #else
        #define DLL_EXPORT_IMPORT __declspec(dllimport)
    #endif
#elif __linux__
    #define DLL_EXPORT_IMPORT
#endif

#endif // BASE_DEFINE_H
