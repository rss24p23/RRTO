#ifndef _RRTO_DEVICE_H_
#define _RRTO_DEVICE_H_

#include "RRTO-types.h"
#include <stddef.h>
#include "cudadebugger.h"

bool RRTO_device_get_prop(CUDBGAPI cudbgAPI, uint32_t device_index,
                             RRTODeviceProp *prop);
bool RRTO_device_get_num(CUDBGAPI cudbgAPI, uint32_t *dev_num);
void RRTO_device_free_prop(RRTODeviceProp *prop);
void RRTO_device_print_prop(RRTODeviceProp *prop);

#endif //_RRTO_DEVICE_H_
