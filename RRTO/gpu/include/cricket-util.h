#ifndef _RRTO_UTIL_H_
#define _RRTO_UTIL_H_

#include <stdio.h>

void RRTO_error_unreachable(void);
double time_diff_sec(const struct timeval *tv1, const struct timeval *tv2);
uint time_diff_usec(const struct timeval *tv1, const struct timeval *tv2);
void print_binary32(uint32_t num);
void print_binary64(uint64_t num);

#endif //_RRTO_UTIL_H_
