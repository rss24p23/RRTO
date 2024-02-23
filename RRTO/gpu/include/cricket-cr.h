#ifndef _RRTO_CR_H_
#define _RRTO_CR_H_

#include "RRTO-types.h"
#include <stddef.h>
#include <stdbool.h>
#include "cudadebugger.h"

#define RRTO_CR_NOLANE (0xFFFFFFFF)
#define RRTO_JMX_ADDR_REG 0

bool RRTO_cr_read_pc(RRTOWarpInfo *wi, uint32_t lane, const char *ckp_dir,
                        RRTO_callstack *callstack);
bool RRTO_cr_rst_pc(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi,
                       uint32_t lane_num, RRTO_callstack *callstack);
bool RRTO_cr_ckp_pc(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi,
                       uint32_t lane_param, const char *ckp_dir,
                       RRTO_callstack *callstack);
bool RRTO_cr_callstack(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi,
                          uint32_t lane_param, RRTO_callstack *callstack);

bool RRTO_cr_make_checkpointable(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi,
                                    RRTO_function_info *fi, size_t fi_num,
                                    RRTO_callstack *callstack);

bool RRTO_cr_ckp_lane(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi, uint32_t lane,
                         const char *ckp_dir);
bool RRTO_cr_rst_lane(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi, uint32_t lane,
                         const char *ckp_dir);
bool RRTO_cr_function_name(uint64_t pc, const char **name);
bool RRTO_cr_kernel_name(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                            uint32_t wp, const char **name);
bool RRTO_cr_ckp_params(CUDBGAPI cudbgAPI, const char *ckp_dir,
                           RRTO_elf_info *elf_info, uint32_t dev,
                           uint32_t sm, uint32_t warp);
bool RRTO_cr_rst_params(CUDBGAPI cudbgAPI, const char *ckp_dir,
                           RRTO_elf_info *elf_info, uint32_t dev,
                           uint32_t sm, uint32_t warp);
bool RRTO_cr_ckp_shared(CUDBGAPI cudbgAPI, const char *ckp_dir,
                           RRTO_elf_info *elf_info, uint32_t dev,
                           uint32_t sm, uint32_t warp);
bool RRTO_cr_rst_shared(CUDBGAPI cudbgAPI, const char *ckp_dir,
                           RRTO_elf_info *elf_info, uint32_t dev,
                           uint32_t sm, uint32_t warp);
bool RRTO_cr_ckp_ssy(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi, uint32_t lane,
                        const char *ckp_dir);
bool RRTO_cr_join_threads(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm,
                             uint32_t wp);

bool RRTO_cr_rst_globals(CUDBGAPI cudbgAPI, const char *ckp_dir);
bool RRTO_cr_ckp_globals(CUDBGAPI cudbgAPI, const char *ckp_dir);

bool RRTO_cr_rst_ssy(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi,
                        RRTO_callstack *callstack, int c_level,
                        RRTO_jmptable_entry *ssy, size_t ssy_num,
                        uint64_t *cur_address);
bool RRTO_cr_rst_subcall(CUDBGAPI cudbgAPI, RRTOWarpInfo *wi,
                            RRTO_callstack *callstack, int c_level,
                            RRTO_jmptable_entry *cal, size_t cal_num,
                            uint64_t *cur_address);
bool RRTO_cr_sm_broken(CUDBGAPI cudbgAPI, uint32_t dev, uint32_t sm);

void RRTO_cr_free_callstack(RRTO_callstack *callstack);

#endif //_RRTO_CR_H_
