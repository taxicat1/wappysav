#ifndef NITRO_COMPAT_H
#define NITRO_COMPAT_H

#include "nitro_types.h"

typedef enum {
    CARD_RESULT_SUCCESS,
    CARD_RESULT_FAILURE,
    CARD_RESULT_INVALID_PARAM,
    CARD_RESULT_UNSUPPORTED,
    CARD_RESULT_TIMEOUT,
    CARD_RESULT_ERROR,
    CARD_RESULT_NO_RESPONSE,
    CARD_RESULT_CANCELED
} CARDResult;

static inline CARDResult CARD_GetResultCode(void) {
	return CARD_RESULT_SUCCESS;
}

static inline void CARD_UnlockBackup(u16 lock_id) {
}

#endif
