#include <stdio.h>
#include <stdlib.h>

#include "save_proc.h"


int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Wappy Dog save file decoder\n");
		printf("Usage: %s input.sav output.bin\n", argv[0]);
		return 1;
	}
	
	char* input_fname = argv[1];
	char* output_fname = argv[2];
	
	char* input_buf = calloc(SAVE_FILE_INPUT_SIZE, 1);
	char* output_buf = calloc(SAVE_FILE_OUTPUT_SIZE, 1);
	
	FILE* input_file = fopen(input_fname, "rb");
	if (input_file == NULL) {
		printf("Could not read %s\n", input_fname);
		return 1;
	}
	
	fread(&input_buf[0], 1, SAVE_FILE_INPUT_SIZE, input_file);
	fclose(input_file);
	
	gSaveCtx.raw_save_data = (u16*)input_buf;
	gSaveCtx.decoded_save_data = (u16*)output_buf;
	gSaveCtx.decoded_save_data_len = SAVE_FILE_OUTPUT_SIZE;
	
	InitSaveData();
	
	switch (gSaveCtx.status) {
		case SAVE_STATUS_OK: {
			FILE* output_file = fopen(output_fname, "wb");
			fwrite(output_buf, 1, SAVE_FILE_OUTPUT_SIZE, output_file);
			fclose(output_file);
			printf("OK\n");
			break;
		}
		
		case SAVE_STATUS_READ_FAIL: {
			// Impossible
			break;
		}
		
		case SAVE_STATUS_SIGNATURE_MISMATCH: {
			printf("Signature mismatch (file must begin 47 2D 47 2D)\n");
			break;
		}
		
		case SAVE_STATUS_CHECKSUM_MISMATCH: {
			printf("Checksum mismatch (file is considered corrupt)\n");
			break;
		}
	}
	
	free(input_buf);
	free(output_buf);
	
	return (gSaveCtx.status == SAVE_STATUS_OK) ? 0 : 1;
}
