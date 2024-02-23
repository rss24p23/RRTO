#ifndef _RRTO_REGISTER_H_
#define _RRTO_REGISTER_H_

#include <stddef.h>
#include "cudadebugger.h"
#include "RRTO-device.h"

size_t RRTO_register_size(RRTODeviceProp *prop);
bool RRTO_register_ckp(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                          uint32_t warp, uint32_t lane, void *register_data,
                          RRTODeviceProp *prop);
bool RRTO_register_rst(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                          uint32_t warp, uint32_t lane, void *register_data,
                          RRTODeviceProp *prop);

#endif //_RRTO_REGISTER_H_
