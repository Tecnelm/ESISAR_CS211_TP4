#include "utilityFonction.h"


FILE *openFile (char *name, char *mode) {

	FILE *fd;
	fd = fopen(name, mode);

	if (fd == NULL) {
		fprintf(stderr, "ERROR OPENING FOLDER : %s\n", name);
		perror("");
		exit(EXIT_FAILURE);
	}

	return fd;
}

void closeFile (FILE *file) {

	if (fclose(file) == EOF) {
		fprintf(stderr, "\"ERROR CLOSE FOLDER \n");
		perror("");
		exit(EXIT_FAILURE);
	}
}

int isInsideTable (char c, const char *table, int table_size) {///compare each element of a table and return if the parmeter is present

	int result = 0;
	int index = 0;
	do {
		if (c == table[index]) {
			result = 1;
		}
	}
	while ((c != table[index]) && ++index < table_size);
	return result;
}


void print_binary_char (char c, char lastchar) {

	int i;
	for (i = 7; i >= 0; i--) {
		printf("%d", c >> i & 1); /// get the bit and print it
	}
	printf("%c", lastchar);
}

int convert_String_hexa (const char *string) { /// convert a char*, format in HEXA to an integer "FF" -> 255

	unsigned int stringlen = strlen(string);
	int result = 0;
	int value;
	unsigned int index;

	for (index = 2; index < stringlen; index++) {
		result *= 16;
		switch (string[index]) {
			case '0':value = 0;
				break;
			case '1':value = 1;
				break;
			case '2':value = 2;
				break;
			case '3':value = 3;
				break;
			case '4':value = 4;
				break;
			case '5':value = 5;
				break;
			case '6':value = 6;
				break;
			case '7':value = 7;
				break;
			case '8':value = 8;
				break;
			case '9':value = 9;
				break;
			case 'A':value = 10;
				break;
			case 'B':value = 11;
				break;
			case 'C':value = 12;
				break;
			case 'D':value = 13;
				break;
			case 'E':value = 14;
				break;
			case 'F':value = 15;
				break;
			default:return -1;
		}
		result += value;
	}
	return result;
}

void resetBuffer () {

	int c;
	while ((c = getchar()) != EOF && c != '\n');
}

