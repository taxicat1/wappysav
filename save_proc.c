#include "save_proc.h"
#include "nitro_types.h"

// Decomp scratches:
// https://decomp.me/scratch/N4wyL
// https://decomp.me/scratch/byiOC
// https://decomp.me/scratch/TlfBx

#define SAVE_FILE_SIGNATURE  (0x2D472D47)
#define CHECKSUM_KEY  (0x0000)


static void decodeHwords(u16* dst, u16* src, u32 length, u32 key) {
	key ^= 0x4741;
	for (int i = 0; i < length / 2; i++) {
		u16 hword = *src++;
		*dst++ = hword ^ key;
		key = hword;
	}
}


static void encodeHwords(u16* dst, u16* src, u32 length, u32 key) {
	key ^= 0x4741;
	for (int i = 0; i < length / 2; i++) {
		u16 hword = *src++;
		key ^= hword;
		*dst++ = key;
	}
}


static u32 generateChecksum(void* save_data, int length) {
	u8* datap = (u8*)save_data;
	
	u32 checksum = 0;
	while (length > 0) {
		u32 shift = ((u32)length << 30) >> 27;
		checksum += *datap++ << shift;
		length--;
	}
	return checksum;
}



int WD_EncodeSaveData(void* encoded_dst, void* decoded_src) {
	u16* dst_hwords = (u16*)encoded_dst;
	u16* src_hwords = (u16*)decoded_src;
	
	// Write signature
	dst_hwords[0] = SAVE_FILE_SIGNATURE & 0xFFFF;
	dst_hwords[1] = SAVE_FILE_SIGNATURE >> 16;
	
	// Generate checksum of unencoded data and derive key
	u32 checksum = generateChecksum(&src_hwords[0], SAVE_DECODED_SIZE);
	u16 checksum_key = checksum ^ (checksum >> 8) ^ (checksum >> 16);
	
	// Encode and write data
	encodeHwords(&dst_hwords[4], &src_hwords[0], SAVE_DECODED_SIZE, checksum_key);
	
	// Write and encode checksum
	u16 checksum_hwords[2];
	checksum_hwords[0] = checksum & 0xFFFF;
	checksum_hwords[1] = checksum >> 16;
	encodeHwords(&dst_hwords[2], &checksum_hwords[0], 4, CHECKSUM_KEY);
	
	return SAVE_STATUS_OK;
}


int WD_DecodeSaveData(void* decoded_dst, void* encoded_src) {
	u16* dst_hwords = (u16*)decoded_dst;
	u16* src_hwords = (u16*)encoded_src;
	
	// Check save file signature
	u32 signature = (src_hwords[1] << 16) | src_hwords[0];
	if (signature != SAVE_FILE_SIGNATURE) {
		return SAVE_STATUS_SIGNATURE_MISMATCH;
	}
	
	// Decode save file checksum and derive key
	u16 checksum_hwords[2];
	decodeHwords(&checksum_hwords[0], &src_hwords[2], 4, CHECKSUM_KEY);
	u32 checksum = (checksum_hwords[1] << 16) | checksum_hwords[0];
	u16 checksum_key = checksum ^ (checksum >> 8) ^ (checksum >> 16);
	
	// Decode rest of the save data
	decodeHwords(&dst_hwords[0], &src_hwords[4], SAVE_DECODED_SIZE, checksum_key);
	
	// Validate checksum
	u32 decoded_save_checksum = generateChecksum(&dst_hwords[0], SAVE_DECODED_SIZE);
	if (checksum == decoded_save_checksum) {
		return SAVE_STATUS_OK;
	} else {
		return SAVE_STATUS_CHECKSUM_MISMATCH;
	}
}


int WD_ImportSaveFile(void* encoded_dst, FILE* sav_src) {
	// Ignore padding and backup copy
	return fread(encoded_dst, 1, SAVE_ENCODED_SIZE, sav_src);
}


int WD_ExportSaveFile(FILE* sav_dst, void* encoded_src) {
	for (int i = 0; i < 2; i++) {
		fwrite(encoded_src, 1, SAVE_ENCODED_SIZE, sav_dst);
		int offset = SAVE_ENCODED_SIZE;
		
		u8 fill_byte = 0xFF;
		while (offset != 0x100) {
			fwrite(&fill_byte, 1, 1, sav_dst);
			offset++;
		}
	}
	
	return 0;
}


int WD_ImportDataFile(void* decoded_dst, FILE* bin_src) {
	return fread(decoded_dst, 1, SAVE_DECODED_SIZE, bin_src);
}


int WD_ExportDataFile(FILE* bin_dst, void* decoded_src) {
	return fwrite(decoded_src, 1, SAVE_DECODED_SIZE, bin_dst);
}
