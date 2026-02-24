#include "save_proc.h"
#include "nitro_types.h"

// Decomp scratches:
// https://decomp.me/scratch/N4wyL
// https://decomp.me/scratch/byiOC
// https://decomp.me/scratch/TlfBx

#define SAVE_FILE_SIGNATURE  (0x2D472D47)
#define CHECKSUM_KEY  (0x0000)

#define SAVE_FILE_SIZE  (0x200)
#define SAVE_ENCODED_SIZE  (0xC0)
#define SAVE_DECODED_SIZE  (SAVE_ENCODED_SIZE - 0x8)


static void decodeHwords(u16* dst, u16* src, u32 length, u16 key) {
	key ^= 0x4741;
	for (int i = 0; i < length / 2; i++) {
		u16 hword = *src++;
		*dst++ = hword ^ key;
		key = hword;
	}
}


static void encodeHwords(u16* dst, u16* src, u32 length, u16 key) {
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



static u32 read32(const u8** datap) {
	u32 ret = *(*datap)++;
	ret |= *(*datap)++ << 8;
	ret |= *(*datap)++ << 16;
	ret |= *(*datap)++ << 24;
	return ret;
}


static u16 read16(const u8** datap) {
	u16 ret = *(*datap)++;
	ret |= *(*datap)++ << 8;
	return ret;
}


static u8 read8(const u8** datap) {
	return *(*datap)++;
}


static void write32(u8** datap, u32 data) {
	*(*datap)++ = data & 0xFF;
	*(*datap)++ = (data >> 8) & 0xFF;
	*(*datap)++ = (data >> 16) & 0xFF;
	*(*datap)++ = (data >> 24) & 0xFF;
}


static void write16(u8** datap, u16 data) {
	*(*datap)++ = data & 0xFF;
	*(*datap)++ = (data >> 8) & 0xFF;
}


static void write8(u8** datap, u8 data) {
	*(*datap)++ = data;
}


static void deserialize(WDSave* dst, const void* decoded_src) {
	const u8* src_bytes = (const u8*)decoded_src;
	
	for (int i = 0; i < 10; i++) {
		dst->unlockFlags[i] = read32(&src_bytes);
	}
	
	for (int i = 0; i < 11; i++) {
		dst->nickname[i] = read16(&src_bytes);
	}
	
	dst->musicVolume = read8(&src_bytes);
	dst->soundVolume = read8(&src_bytes);
	
	dst->travelModeColor = read8(&src_bytes);
	dst->travelModeAccessory = read8(&src_bytes);
	dst->travelModeRoom = read8(&src_bytes);
	
	dst->dogAge = read8(&src_bytes);
	dst->dogMood = (s16)read16(&src_bytes);
	
	for (int i = 0; i < 4; i++) {
		dst->dogPersonality[i] = read8(&src_bytes);
	}
	
	dst->dogFriendship = read16(&src_bytes);
	
	dst->unk4C = read8(&src_bytes);
	
	dst->_unk4D = read8(&src_bytes); // Unknown byte
	
	dst->dogHunger = read16(&src_bytes);
	dst->dogCleanliness = read16(&src_bytes);
	
	for (int i = 0; i < 2; i++) {
		dst->_unk52[i] = read8(&src_bytes); // Unknown 2 bytes
	}
	
	dst->playTime = read32(&src_bytes);
	
	for (int i = 0; i < 30; i++) {
		dst->minigameScores[i] = read16(&src_bytes);
	}
	
	dst->unk94 = read8(&src_bytes);
	dst->unk95 = read8(&src_bytes);
	dst->unk96 = read8(&src_bytes);
	dst->unk97 = read8(&src_bytes);
	dst->unk98 = read8(&src_bytes);
	dst->unk99 = read8(&src_bytes);
	dst->unk9A = read8(&src_bytes);
	dst->unk9B = read8(&src_bytes);
	
	for (int i = 0; i < 2; i++) {
		dst->_unk9C[i] = read8(&src_bytes); // Unknown 2 bytes
	}
	
	for (int i = 0; i < 21; i++) {
		dst->unk9E[i] = read8(&src_bytes);
	}
	
	for (int i = 0; i < 6; i++) {
		dst->_unkB2[i] = read8(&src_bytes); // Unknown 6 bytes
	}
}


static void serialize(void* decoded_dst, const WDSave* src) {
	u8* dst_bytes = (u8*)decoded_dst;
	
	for (int i = 0; i < 10; i++) {
		write32(&dst_bytes, src->unlockFlags[i]);
	}
	
	for (int i = 0; i < 11; i++) {
		write16(&dst_bytes, src->nickname[i]);
	}
	
	write8(&dst_bytes, src->musicVolume);
	write8(&dst_bytes, src->soundVolume);
	
	write8(&dst_bytes, src->travelModeColor);
	write8(&dst_bytes, src->travelModeAccessory);
	write8(&dst_bytes, src->travelModeRoom);
	
	write8(&dst_bytes, src->dogAge);
	write16(&dst_bytes, (u16)src->dogMood);
	
	for (int i = 0; i < 4; i++) {
		write8(&dst_bytes, src->dogPersonality[i]);
	}
	
	write16(&dst_bytes, src->dogFriendship);
	
	write8(&dst_bytes, src->unk4C);
	
	write8(&dst_bytes, src->_unk4D); // Unknown byte
	
	write16(&dst_bytes, src->dogHunger);
	write16(&dst_bytes, src->dogCleanliness);
	
	for (int i = 0; i < 2; i++) {
		write8(&dst_bytes, src->_unk52[i]); // Unknown 2 bytes
	}
	
	write32(&dst_bytes, src->playTime);
	
	for (int i = 0; i < 30; i++) {
		write16(&dst_bytes, src->minigameScores[i]);
	}
	
	write8(&dst_bytes, src->unk94);
	write8(&dst_bytes, src->unk95);
	write8(&dst_bytes, src->unk96);
	write8(&dst_bytes, src->unk97);
	write8(&dst_bytes, src->unk98);
	write8(&dst_bytes, src->unk99);
	write8(&dst_bytes, src->unk9A);
	write8(&dst_bytes, src->unk9B);
	
	for (int i = 0; i < 2; i++) {
		write8(&dst_bytes, src->_unk9C[i]); // Unknown 2 bytes
	}
	
	for (int i = 0; i < 21; i++) {
		write8(&dst_bytes, src->unk9E[i]);
	}
	
	for (int i = 0; i < 6; i++) {
		write8(&dst_bytes, src->_unkB2[i]); // Unknown 6 bytes
	}
}



static void encodeSaveData(void* encoded_dst, void* decoded_src) {
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
}


static WDSaveStatus decodeSaveData(void* decoded_dst, void* encoded_src) {
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



WDSaveStatus WD_ImportSaveFile(WDSave* dst, const char* savfile_src) {
	FILE* sav_src = fopen(savfile_src, "rb");
	if (sav_src == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	// Ignore padding and backup copy
	u8 encoded_data_buf[SAVE_ENCODED_SIZE];
	if (fread(&encoded_data_buf[0], 1, SAVE_ENCODED_SIZE, sav_src) != SAVE_ENCODED_SIZE) {
		fclose(sav_src);
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	fclose(sav_src);
	
	u8 decoded_data_buf[SAVE_DECODED_SIZE];
	WDSaveStatus status = decodeSaveData(&decoded_data_buf[0], &encoded_data_buf[0]);
	if (status == SAVE_STATUS_OK) {
		deserialize(dst, &decoded_data_buf[0]);
	}
	
	return status;
}


WDSaveStatus WD_ExportSaveFile(const char* savfile_dst, const WDSave* src) {
	FILE* sav_dst = fopen(savfile_dst, "wb");
	if (sav_dst == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	u8 decoded_data_buf[SAVE_DECODED_SIZE];
	serialize(&decoded_data_buf[0], src);
	
	u8 encoded_data_buf[SAVE_ENCODED_SIZE];
	encodeSaveData(&encoded_data_buf[0], &decoded_data_buf[0]);
	
	// Write data, padding, backup data, padding
	for (int i = 0; i < 2; i++) {
		if (fwrite(encoded_data_buf, 1, SAVE_ENCODED_SIZE, sav_dst) != SAVE_ENCODED_SIZE) {
			fclose(sav_dst);
			return SAVE_STATUS_FILE_FAILURE;
		}
		
		u8 fill_byte = 0xFF;
		for (int offset = SAVE_ENCODED_SIZE; offset != 0x100; offset++) {
			if (fwrite(&fill_byte, 1, 1, sav_dst) != 1) {
				fclose(sav_dst);
				return SAVE_STATUS_FILE_FAILURE;
			}
		}
	}
	
	fclose(sav_dst);
	
	return SAVE_STATUS_OK;
}



WDSaveStatus WD_ImportDataFile(WDSave* dst, const char* binfile_src) {
	FILE* bin_src = fopen(binfile_src, "rb");
	if (bin_src == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	u8 decoded_data_buf[SAVE_DECODED_SIZE];
	if (fread(&decoded_data_buf[0], 1, SAVE_DECODED_SIZE, bin_src) != SAVE_DECODED_SIZE) {
		fclose(bin_src);
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	fclose(bin_src);
	
	deserialize(dst, &decoded_data_buf[0]);
	
	return SAVE_STATUS_OK;
}


WDSaveStatus WD_ExportDataFile(const char* binfile_dst, const WDSave* src) {
	FILE* bin_dst = fopen(binfile_dst, "wb");
	if (bin_dst == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	u8 decoded_data_buf[SAVE_DECODED_SIZE];
	serialize(&decoded_data_buf[0], src);
	
	if (fwrite(&decoded_data_buf[0], 1, SAVE_DECODED_SIZE, bin_dst) != SAVE_DECODED_SIZE) {
		fclose(bin_dst);
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	fclose(bin_dst);
	
	return SAVE_STATUS_OK;
}
