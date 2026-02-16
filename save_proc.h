#ifndef SAVE_PROC_H
#define SAVE_PROC_H

#include "nitro_types.h"

#define SAVE_FILE_INPUT_SIZE  (0xC0)
#define SAVE_FILE_OUTPUT_SIZE  (SAVE_FILE_INPUT_SIZE - 8)

typedef struct {
    u32   decoded_save_data_len;
    u16*  decoded_save_data;
    u16*  raw_save_data;
    u32   status;
    u32   lock_id;
} SaveCtx;

enum {
    SAVE_STATUS_OK = 1,
    SAVE_STATUS_READ_FAIL = -1,
    SAVE_STATUS_SIGNATURE_MISMATCH = -2,
    SAVE_STATUS_CHECKSUM_MISMATCH = -3
};

extern SaveCtx gSaveCtx;

void InitSaveData(void);

#endif
