#ifndef _RRTO_FILE_H_
#define _RRTO_FILE_H_

#include <stddef.h>
#include <stdbool.h>

typedef enum _RRTODataType {
    RRTO_DT_REGISTERS = 1,
    RRTO_DT_PC = 2,
    RRTO_DT_GLOBALS = 3,
    RRTO_DT_STACK = 4,
    RRTO_DT_PARAM = 5,
    RRTO_DT_HEAP = 6,
    RRTO_DT_SHARED = 7,
    RRTO_DT_CALLSTACK = 8,
    RRTO_DT_LAST
} RRTODataType;

const char *RRTO_file_dt2str(RRTODataType data_type);
bool RRTO_file_store_mem(const char *path, RRTODataType data_type,
                            const char *suffix, void *data, size_t size);
bool RRTO_file_read_mem(const char *path, RRTODataType data_type,
                           const char *suffix, void *data, size_t size);
bool RRTO_file_read_mem_size(const char *path, RRTODataType data_type,
                                const char *suffix, void **data,
                                size_t alloc_size, size_t *size);
bool RRTO_file_exists(const char *path, RRTODataType data_type,
                         const char *suffix);

#endif //_RRTO_FILE_H_
