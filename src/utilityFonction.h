
#ifndef ESISAR_CS211_TP4_UTILITYFONCTION_H
#define ESISAR_CS211_TP4_UTILITYFONCTION_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void closeFile (FILE *file);

FILE *openFile (char *name, char *mode);

int isInsideTable (char c, const char *table, int table_size);

void print_binary_char (char character, char lastchar);

int convert_String_hexa (const char *string);//

void resetBuffer ();

#endif //ESISAR_CS211_TP4_UTILITYFONCTION_H
