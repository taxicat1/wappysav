#include "save_proc.h"

// Decomp scratches:
// https://decomp.me/scratch/N4wyL
// https://decomp.me/scratch/byiOC
// https://decomp.me/scratch/TlfBx

#define SAVE_FILE_SIGNATURE  (0x2D472D47)
#define CHECKSUM_KEY         (0x0000)

#define SAVE_ENCODED_SIZE  (0xC0)
#define SAVE_DECODED_SIZE  (SAVE_ENCODED_SIZE - 0x8)
#define SAVE_PADDED_SIZE   (0x100)


// Read/write little-endian data from pointer, don't alter pointer

static inline uint32_t get32(const uint8_t* data) {
	uint32_t ret = *data++;
	ret |= *data++ << 8;
	ret |= *data++ << 16;
	ret |= *data << 24;
	return ret;
}


static inline uint16_t get16(const uint8_t* data) {
	uint16_t ret = *data++;
	ret |= *data << 8;
	return ret;
}


static inline uint8_t get8(const uint8_t* data) {
	return *data;
}


static inline void put32(uint8_t* data, uint32_t value) {
	*data++ = value;
	*data++ = value >> 8;
	*data++ = value >> 16;
	*data = value >> 24;
}


static inline void put16(uint8_t* data, uint16_t value) {
	*data++ = value;
	*data = value >> 8;
}


static inline void put8(uint8_t* data, uint8_t value) {
	*data = value;
}



// Read/write little-endian data from data pointer, increment pointer accordingly

static inline uint32_t read32(const uint8_t** datap) {
	uint32_t ret = *(*datap)++;
	ret |= *(*datap)++ << 8;
	ret |= *(*datap)++ << 16;
	ret |= *(*datap)++ << 24;
	return ret;
}


static inline uint16_t read16(const uint8_t** datap) {
	uint16_t ret = *(*datap)++;
	ret |= *(*datap)++ << 8;
	return ret;
}


static inline uint8_t read8(const uint8_t** datap) {
	return *(*datap)++;
}


static inline void write32(uint8_t** datap, uint32_t value) {
	*(*datap)++ = value;
	*(*datap)++ = value >> 8;
	*(*datap)++ = value >> 16;
	*(*datap)++ = value >> 24;
}


static inline void write16(uint8_t** datap, uint16_t value) {
	*(*datap)++ = value;
	*(*datap)++ = value >> 8;
}


static inline void write8(uint8_t** datap, uint8_t value) {
	*(*datap)++ = value;
}



// Functions for save file encoding and decoding

static void encodeXor(uint8_t* encoded_dst, const uint8_t* decoded_src, int length, uint16_t key) {
	key ^= 0x4741;
	for (int i = 0; i < length / 2; i++) {
		uint16_t hword = read16(&decoded_src);
		hword ^= key;
		write16(&encoded_dst, hword);
		key = hword;
	}
}


static void decodeXor(uint8_t* decoded_dst, const uint8_t* encoded_src, int length, uint16_t key) {
	key ^= 0x4741;
	for (int i = 0; i < length / 2; i++) {
		uint16_t hword = read16(&encoded_src);
		write16(&decoded_dst, hword ^ key);
		key = hword;
	}
}


static uint32_t generateChecksum(const uint8_t* save_data, int length) {
	uint32_t checksum = 0;
	while (length > 0) {
		int shift = (length * 8) & 31;
		checksum += read8(&save_data) << shift;
		length--;
	}
	return checksum;
}


static void encodeSaveData(uint8_t* encoded_dst, const uint8_t* decoded_src) {
	// Write signature
	put32(&encoded_dst[0], SAVE_FILE_SIGNATURE);
	
	// Generate checksum of unencoded data and derive key
	uint32_t checksum = generateChecksum(&decoded_src[0], SAVE_DECODED_SIZE);
	uint16_t checksum_key = checksum ^ (checksum >> 8) ^ (checksum >> 16);
	
	// Encode and write data
	encodeXor(&encoded_dst[8], &decoded_src[0], SAVE_DECODED_SIZE, checksum_key);
	
	// Write and encode checksum
	uint8_t checksum_bytes[4];
	put32(&checksum_bytes[0], checksum);
	encodeXor(&encoded_dst[4], &checksum_bytes[0], 4, CHECKSUM_KEY);
}


static WDSaveStatus decodeSaveData(uint8_t* decoded_dst, uint8_t* encoded_src) {
	// Check save file signature
	if (get32(&encoded_src[0]) != SAVE_FILE_SIGNATURE) {
		return SAVE_STATUS_SIGNATURE_MISMATCH;
	}
	
	// Decode save file checksum and derive key
	uint8_t checksum_bytes[4];
	decodeXor(&checksum_bytes[0], &encoded_src[4], 4, CHECKSUM_KEY);
	uint32_t stored_checksum = get32(&checksum_bytes[0]);
	uint16_t checksum_key = stored_checksum ^ (stored_checksum >> 8) ^ (stored_checksum >> 16);
	
	// Decode rest of the save data
	decodeXor(&decoded_dst[0], &encoded_src[8], SAVE_DECODED_SIZE, checksum_key);
	
	// Validate checksum
	uint32_t calculated_checksum = generateChecksum(&decoded_dst[0], SAVE_DECODED_SIZE);
	if (calculated_checksum == stored_checksum) {
		return SAVE_STATUS_OK;
	} else {
		return SAVE_STATUS_CHECKSUM_MISMATCH;
	}
}



// Functions for serializing or deserializing struct and bytes

static void deserializeSaveData(WDSave* dst, const uint8_t* src_bytes) {
	for (int i = 0; i < FLAG_NUM_U32S; i++) {
		dst->gameFlags[i] = read32(&src_bytes);
	}
	
	for (int i = 0; i < NICKNAME_BUF_LEN; i++) {
		dst->nickname[i] = read16(&src_bytes);
	}
	
	dst->musicVolume = read8(&src_bytes);
	dst->soundVolume = read8(&src_bytes);
	
	dst->travelModeColor     = read8(&src_bytes);
	dst->travelModeAccessory = read8(&src_bytes);
	dst->travelModeRoom      = read8(&src_bytes);
	
	dst->age = read8(&src_bytes);
	dst->mood = (int16_t)read16(&src_bytes);
	
	for (int i = PERSONALITY_START; i < PERSONALITY_MAX; i++) {
		dst->personality[i] = read8(&src_bytes);
	}
	
	dst->friendship     = read16(&src_bytes);
	dst->fieldshipLevel = read8(&src_bytes);
	
	dst->pad4D = read8(&src_bytes); // Padding byte
	
	dst->fullness    = read16(&src_bytes);
	dst->cleanliness = read16(&src_bytes);
	
	for (int i = 0; i < 2; i++) {
		dst->pad52[i] = read8(&src_bytes); // Padding 2 bytes
	}
	
	dst->playTime = read32(&src_bytes);
	
	for (int g = MINIGAME_START; g < MINIGAME_MAX; g++) {
		for (int d = DIFFICULTY_START; d < DIFFICULTY_MAX; d++) {
			dst->minigameScores[g][d] = read16(&src_bytes);
		}
	}
	
	dst->messageReceivedCount = read8(&src_bytes);
	dst->minigameWinCount     = read8(&src_bytes);
	dst->fullyCleanedCount    = read8(&src_bytes);
	dst->fedCount             = read8(&src_bytes);
	dst->minigamePlayCount    = read8(&src_bytes);
	dst->petCount             = read8(&src_bytes);
	dst->messageSentCount     = read8(&src_bytes);
	dst->toyPlayCount         = read8(&src_bytes);
	
	for (int i = 0; i < TRICK_MAX; i++) {
		dst->trickCount[i] = read8(&src_bytes);
	}
	
	for (int i = 0; i < 6; i++) {
		dst->padB2[i] = read8(&src_bytes); // Padding 6 bytes
	}
}


static void serializeSaveData(uint8_t* dst_bytes, const WDSave* src) {
	for (int i = 0; i < FLAG_NUM_U32S; i++) {
		write32(&dst_bytes, src->gameFlags[i]);
	}
	
	for (int i = 0; i < NICKNAME_BUF_LEN; i++) {
		write16(&dst_bytes, src->nickname[i]);
	}
	
	write8(&dst_bytes, src->musicVolume);
	write8(&dst_bytes, src->soundVolume);
	
	write8(&dst_bytes, src->travelModeColor);
	write8(&dst_bytes, src->travelModeAccessory);
	write8(&dst_bytes, src->travelModeRoom);
	
	write8(&dst_bytes, src->age);
	write16(&dst_bytes, (uint16_t)src->mood);
	
	for (int p = PERSONALITY_START; p < PERSONALITY_MAX; p++) {
		write8(&dst_bytes, src->personality[p]);
	}
	
	write16(&dst_bytes, src->friendship);
	write8(&dst_bytes, src->fieldshipLevel);
	
	write8(&dst_bytes, src->pad4D); // Padding byte
	
	write16(&dst_bytes, src->fullness);
	write16(&dst_bytes, src->cleanliness);
	
	for (int i = 0; i < 2; i++) {
		write8(&dst_bytes, src->pad52[i]); // Padding 2 bytes
	}
	
	write32(&dst_bytes, src->playTime);
	
	for (int g = MINIGAME_START; g < MINIGAME_MAX; g++) {
		for (int d = DIFFICULTY_START; d < DIFFICULTY_MAX; d++) {
			write16(&dst_bytes, src->minigameScores[g][d]);
		}
	}
	
	write8(&dst_bytes, src->messageReceivedCount);
	write8(&dst_bytes, src->minigameWinCount);
	write8(&dst_bytes, src->fullyCleanedCount);
	write8(&dst_bytes, src->fedCount);
	write8(&dst_bytes, src->minigamePlayCount);
	write8(&dst_bytes, src->petCount);
	write8(&dst_bytes, src->messageSentCount);
	write8(&dst_bytes, src->toyPlayCount);
	
	for (int i = 0; i < TRICK_MAX; i++) {
		write8(&dst_bytes, src->trickCount[i]);
	}
	
	for (int i = 0; i < 6; i++) {
		write8(&dst_bytes, src->padB2[i]); // Padding 6 bytes
	}
}



// New save file creation

void WD_CreateNewSave(WDSave* dst) {
	static const uint8_t new_save_file_data[] = {
		0x84, 0x10, 0x06, 0x80, 0x24, 0x49, 0xFE, 0xEF, 0xF8, 0x07, 0x00, 0x00,
		0x0C, 0x00, 0x00, 0x21, 0x84, 0x01, 0x20, 0x49, 0x92, 0xFF, 0x3B, 0xFE,
		0x01, 0x00, 0x00, 0x03, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0xF0, 0x3F, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x61, 0x00, 0x70, 0x00, 0x70, 0x00,
		0x79, 0x00, 0x00, 0x00, 0x20, 0x00, 0x70, 0x00, 0x72, 0x00, 0x65, 0x00,
		0x76, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x01, 0xC0, 0xFF, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x02,
		0x57, 0x02, 0x57, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};
	
	deserializeSaveData(dst, &new_save_file_data[0]);
}



// Save file importing or exporting to struct

WDSaveStatus WD_ImportSaveFile(WDSave* dst, const char* savfile_src) {
	FILE* sav_src = fopen(savfile_src, "rb");
	if (sav_src == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	uint8_t encoded_data_buf[SAVE_ENCODED_SIZE];
	if (fread(&encoded_data_buf[0], 1, SAVE_ENCODED_SIZE, sav_src) != SAVE_ENCODED_SIZE) {
		fclose(sav_src);
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	uint8_t decoded_data_buf[SAVE_DECODED_SIZE];
	WDSaveStatus status = decodeSaveData(&decoded_data_buf[0], &encoded_data_buf[0]);
	if (status != SAVE_STATUS_OK) {
		// Try backup data instead
		if (fseek(sav_src, SAVE_PADDED_SIZE, SEEK_SET) != 0) {
			fclose(sav_src);
			return SAVE_STATUS_FILE_FAILURE;
		}
		
		if (fread(&encoded_data_buf[0], 1, SAVE_ENCODED_SIZE, sav_src) != SAVE_ENCODED_SIZE) {
			fclose(sav_src);
			return SAVE_STATUS_FILE_FAILURE;
		}
		
		status = decodeSaveData(&decoded_data_buf[0], &encoded_data_buf[0]);
	}
	
	fclose(sav_src);
	
	if (status == SAVE_STATUS_OK) {
		deserializeSaveData(dst, &decoded_data_buf[0]);
	}
	
	return status;
}


WDSaveStatus WD_ExportSaveFile(const char* savfile_dst, const WDSave* src) {
	FILE* sav_dst = fopen(savfile_dst, "wb");
	if (sav_dst == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	uint8_t decoded_data_buf[SAVE_DECODED_SIZE];
	serializeSaveData(&decoded_data_buf[0], src);
	
	uint8_t encoded_data_buf[SAVE_ENCODED_SIZE];
	encodeSaveData(&encoded_data_buf[0], &decoded_data_buf[0]);
	
	// Write data, padding, backup data, padding
	for (int i = 0; i < 2; i++) {
		if (fwrite(encoded_data_buf, 1, SAVE_ENCODED_SIZE, sav_dst) != SAVE_ENCODED_SIZE) {
			fclose(sav_dst);
			return SAVE_STATUS_FILE_FAILURE;
		}
		
		uint8_t fill_byte = 0xFF;
		for (int offset = SAVE_ENCODED_SIZE; offset != SAVE_PADDED_SIZE; offset++) {
			if (fwrite(&fill_byte, 1, 1, sav_dst) != 1) {
				fclose(sav_dst);
				return SAVE_STATUS_FILE_FAILURE;
			}
		}
	}
	
	fclose(sav_dst);
	
	return SAVE_STATUS_OK;
}



// Data file importing or exporting to struct

WDSaveStatus WD_ImportDataFile(WDSave* dst, const char* binfile_src) {
	FILE* bin_src = fopen(binfile_src, "rb");
	if (bin_src == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	uint8_t decoded_data_buf[SAVE_DECODED_SIZE];
	if (fread(&decoded_data_buf[0], 1, SAVE_DECODED_SIZE, bin_src) != SAVE_DECODED_SIZE) {
		fclose(bin_src);
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	fclose(bin_src);
	
	deserializeSaveData(dst, &decoded_data_buf[0]);
	
	return SAVE_STATUS_OK;
}


WDSaveStatus WD_ExportDataFile(const char* binfile_dst, const WDSave* src) {
	FILE* bin_dst = fopen(binfile_dst, "wb");
	if (bin_dst == NULL) {
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	uint8_t decoded_data_buf[SAVE_DECODED_SIZE];
	serializeSaveData(&decoded_data_buf[0], src);
	
	if (fwrite(&decoded_data_buf[0], 1, SAVE_DECODED_SIZE, bin_dst) != SAVE_DECODED_SIZE) {
		fclose(bin_dst);
		return SAVE_STATUS_FILE_FAILURE;
	}
	
	fclose(bin_dst);
	
	return SAVE_STATUS_OK;
}
