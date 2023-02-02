/*
 * @Author: SourDumplings
 * @Date: 2022-12-14 19:46:08
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */


#include "Assert.h"

namespace CZ
{
    void Assert(bool assertion, const char *fileName, int lineNo, const char *failMsgFmt, ...)
    {
        if (!assertion)
        {
            va_list ap;
            va_start(ap, failMsgFmt);
            fflush(stdout);
            char failMsg[MAX_ERROR_MSG_LEN];
            vsnprintf(failMsg, MAX_ERROR_MSG_LEN, failMsgFmt, ap);
            fprintf(stderr, "Assertion failed at %s::%d %s\n", fileName, lineNo, failMsg);
            fflush(stderr);
            va_end(ap);
            abort();
        }
    }
}