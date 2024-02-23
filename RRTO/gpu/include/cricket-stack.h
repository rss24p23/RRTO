#ifndef _RRTO_STACK_H_
#define _RRTO_STACK_H_

#include "cudadebugger.h"
#include <stddef.h>

uint32_t RRTO_stack_get_sp_regnum(void);

bool RRTO_stack_get_sp(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                          uint32_t warp, uint32_t lane, uint32_t *sp);

bool RRTO_stack_set_mem(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                           uint32_t warp, uint32_t lane, void *stack_mem,
                           uint32_t stack_loc, uint32_t stack_size);

bool RRTO_stack_get_mem(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                           uint32_t warp, uint32_t lane, void *stack_mem,
                           uint32_t stack_size);

bool RRTO_param_get_mem(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                           uint32_t warp, uint16_t param_addr, void *param_mem,
                           uint16_t param_size);
#endif //_RRTO_STACK_H_
