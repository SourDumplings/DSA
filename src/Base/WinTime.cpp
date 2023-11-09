#include "WinTime.h"

void gettimeofday(struct timeval *tv, void *p)
{
    auto time_now = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    auto duration_in_s = std::chrono::duration_cast<std::chrono::seconds>(time_now.time_since_epoch()).count();
    auto duration_in_us = std::chrono::duration_cast<std::chrono::microseconds>(time_now.time_since_epoch()).count();

    tv->tv_sec = duration_in_s;
    tv->tv_usec = duration_in_us;
}