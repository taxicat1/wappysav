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
		return EXIT_FAILURE;
	}
	
	int operation;
	if (strcmp(argv[1], "encode") == 0) {
		operation = OP_ENCODE;
	} else if (strcmp(argv[1], "decode") == 0) {
		operation = OP_DECODE;
	} else {
		printf("Invalid operation: %s\n", argv[1]);
		printf("Expected 'encode' or 'decode'\n");
		return EXIT_FAILURE;
	}
	
	char* input_fname = argv[2];
	char* output_fname = argv[3];
	
	if (operation == OP_DECODE) {
		WDSave save_data;
		switch (WD_ImportSaveFile(&save_data, input_fname)) {
			case SAVE_STATUS_OK:
				if (WD_ExportDataFile(output_fname, &save_data) != SAVE_STATUS_OK) {
					printf("Could not write %s\n", output_fname);
					return EXIT_FAILURE;
				}
				
				printf("OK\n");
				return EXIT_SUCCESS;
			
			case SAVE_STATUS_FILE_FAILURE:
				printf("Could not read %s\n", input_fname);
				return EXIT_FAILURE;
			
			case SAVE_STATUS_SIGNATURE_MISMATCH:
				printf("Signature mismatch (file must begin 47 2D 47 2D)\n");
				return EXIT_FAILURE;
			
			case SAVE_STATUS_CHECKSUM_MISMATCH:
				printf("Checksum mismatch (file is considered corrupt)\n");
				return EXIT_FAILURE;
		}
	} else {
		WDSave save_data;
		if (WD_ImportDataFile(&save_data, input_fname) != SAVE_STATUS_OK) {
			printf("Could not read %s\n", input_fname);
			return EXIT_FAILURE;
		}
		
		if (WD_ExportSaveFile(output_fname, &save_data) != SAVE_STATUS_OK) {
			printf("Could not write %s\n", output_fname);
			return EXIT_FAILURE;
		}
		
		printf("OK\n");
		return EXIT_SUCCESS;
	}
}
