#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "save_proc.h"

enum {
	OP_ENCODE,
	OP_DECODE
};


int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Wappy Dog save file decoder\n");
		printf("Usage: %s decode savefile.sav data.bin\n", argv[0]);
		printf("       %s encode data.bin savefile.sav\n", argv[0]);
		return 1;
	}
	
	int operation;
	if (strcmp(argv[1], "encode") == 0) {
		operation = OP_ENCODE;
	} else if (strcmp(argv[1], "decode") == 0) {
		operation = OP_DECODE;
	} else {
		printf("Invalid operation: %s\n", argv[1]);
		printf("Expected 'encode' or 'decode'\n");
		return 1;
	}
	
	char* input_fname = argv[2];
	char* output_fname = argv[3];
	int ret_code = EXIT_SUCCESS;
	
	void* encoded_data_buf = malloc(SAVE_ENCODED_SIZE);
	void* decoded_data_buf = malloc(SAVE_DECODED_SIZE);
	
	FILE* input_file = fopen(input_fname, "rb");
	if (input_file == NULL) {
		printf("Could not read %s\n", input_fname);
		ret_code = EXIT_FAILURE;
		goto EXIT;
	}
	
	if (operation == OP_DECODE) {
		WD_ImportSaveFile(encoded_data_buf, input_file);
		fclose(input_file);
		
		int decode_result = WD_DecodeSaveData(decoded_data_buf, encoded_data_buf);
		switch (decode_result) {
			case SAVE_STATUS_OK: {
				FILE* output_file = fopen(output_fname, "wb");
				if (output_file == NULL) {
					printf("Could not write %s\n", output_fname);
					ret_code = EXIT_FAILURE;
					goto EXIT;
				}
				
				WD_ExportDataFile(output_file, decoded_data_buf);
				fclose(output_file);
				printf("OK\n");
				break;
			}
			
			case SAVE_STATUS_SIGNATURE_MISMATCH: {
				printf("Signature mismatch (file must begin 47 2D 47 2D)\n");
				ret_code = EXIT_FAILURE;
				goto EXIT;
			}
			
			case SAVE_STATUS_CHECKSUM_MISMATCH: {
				printf("Checksum mismatch (file is considered corrupt)\n");
				ret_code = EXIT_FAILURE;
				goto EXIT;
			}
		}
	} else {
		WD_ImportDataFile(decoded_data_buf, input_file);
		fclose(input_file);
		
		WD_EncodeSaveData(encoded_data_buf, decoded_data_buf);
		
		FILE* output_file = fopen(output_fname, "wb");
		if (output_file == NULL) {
			printf("Could not write %s\n", output_fname);
			ret_code = EXIT_FAILURE;
			goto EXIT;
		}
		
		WD_ExportSaveFile(output_file, encoded_data_buf);
		printf("OK\n");
	}
	
EXIT:
	free(encoded_data_buf);
	free(decoded_data_buf);
	return ret_code;
}
