#include "save_proc.h"
#include "nitro_compat.h"

#define SAVE_FILE_SIGNATURE  (0x2D472D47)

SaveCtx gSaveCtx;


// https://decomp.me/scratch/N4wyL
static void DecodeSaveData(void* output_save_data, const void* input_save_data, u32 length, u32 key) {
	const u16* src = (const u16*)input_save_data;
	u16* dst = (u16*)output_save_data;
	
	key ^= 0x4741;
	for (int i = 0; i < length / 2; i++) {
		u16 hword = *src++;
		*dst++ = hword ^ key;
		key = hword;
	}
}


// https://decomp.me/scratch/byiOC
static u32 GenerateSaveChecksum(void* save_data, int length) {
	u8* datap = (u8*)save_data;
	
	u32 checksum = 0;
	while (length > 0) {
		u32 shift = ((u32)length << 30) >> 27;
		checksum += *datap++ << shift;
		length--;
	}
	return checksum;
}


static void FUN_02028658(void* data) {
	// ?
}


// https://decomp.me/scratch/TlfBx
#define FIX_FOR_MODERN_COMPILER
void InitSaveData(void) {
	u32 card_result = CARD_GetResultCode();
	CARD_UnlockBackup(gSaveCtx.lock_id);
	
	if (card_result != CARD_RESULT_SUCCESS) {
		gSaveCtx.status = SAVE_STATUS_READ_FAIL;
	} else {
		// Check save file signature
		u32 check = (gSaveCtx.raw_save_data[1] << 16) | gSaveCtx.raw_save_data[0];
		if (check == SAVE_FILE_SIGNATURE) {
			// Decode save file checksum and derive key
#ifdef FIX_FOR_MODERN_COMPILER
			u16 decoded[2];
			DecodeSaveData(&decoded[0], &gSaveCtx.raw_save_data[2], 4, 0);
			check = decoded[0] | (decoded[1] << 16);
#else
			DecodeSaveData((u16*)&check, &gSaveCtx.raw_save_data[2], 4, 0);
#endif
			u16 checksum_key = check ^ (check >> 8) ^ (check >> 16);
			
			// Decode rest of the save data
			DecodeSaveData(&gSaveCtx.decoded_save_data[0],
			               &gSaveCtx.raw_save_data[4],
			               gSaveCtx.decoded_save_data_len,
			               checksum_key);
			
			// Validate checksum
			u32 decoded_save_checksum = GenerateSaveChecksum(&gSaveCtx.decoded_save_data[0], gSaveCtx.decoded_save_data_len);
			gSaveCtx.status = (check == decoded_save_checksum) ? SAVE_STATUS_OK : SAVE_STATUS_CHECKSUM_MISMATCH;
		} else {
			gSaveCtx.status = SAVE_STATUS_SIGNATURE_MISMATCH;
		}
	}
	
	// Not sure?
	FUN_02028658(gSaveCtx.raw_save_data);
}
