#ifndef SAVE_PROC_H
#define SAVE_PROC_H

#include <stdio.h>


#define SAVE_FILE_SIZE  (0x200)
#define SAVE_ENCODED_SIZE  (0xC0)
#define SAVE_DECODED_SIZE  (SAVE_ENCODED_SIZE - 0x8)

enum {
	SAVE_STATUS_OK,
	SAVE_STATUS_SIGNATURE_MISMATCH,
	SAVE_STATUS_CHECKSUM_MISMATCH
};

int WD_EncodeSaveData(void* encoded_dst, void* decoded_src);
int WD_DecodeSaveData(void* decoded_dst, void* encoded_src);

int WD_ImportSaveFile(void* encoded_dst, FILE* sav_src);
int WD_ExportSaveFile(FILE* sav_dst, void* encoded_src);

int WD_ImportDataFile(void* decoded_dst, FILE* bin_src);
int WD_ExportDataFile(FILE* bin_dst, void* decoded_src);

#endif
