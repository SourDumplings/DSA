/*
 * @Author: SourDumplings
 * @Date: 2022-12-13 19:21:53
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#ifndef ASSERT_H
#define ASSERT_H

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace CZ
{

#ifdef DEBUG
#define ASSERT_DEBUG(assertion, failMsgFmt, args...) Assert(assertion, __FILE__, __LINE__, failMsgFmt, ##args)
#else
#define ASSERT_DEBUG(assertion, failMsgFmt, ...)
#endif

#define ASSERT_RELEASE(assertion, failMsgFmt, args...) Assert(assertion, __FILE__, __LINE__, failMsgFmt, ##args)

#define MAX_ERROR_MSG_LEN 100

void Assert(bool assertion, const char *fileName, int lineNo, const char *failMsgFmt, ...) noexcept;
}

#endif