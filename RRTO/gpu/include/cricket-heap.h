#ifndef _RRTO_HEAP_H_
#define _RRTO_HEAP_H_

#include "cudadebugger.h"
#include <stddef.h>

bool RRTO_focus_host(bool batch_flag);
bool RRTO_focus_kernel(bool batch_flag);
bool RRTO_heap_memreg_size(void *addr, size_t *size);

#endif //_RRTO_HEAP_H_
