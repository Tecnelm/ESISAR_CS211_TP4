#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include "AlgoGenetique.h"
#include "utilityFonction.h"


#define lire(gene, i)    (i%2)?(gene[i/2]&0xF):(gene[i/2]>>4);

void affiche (unsigned char *gene) {

	char code[] = "+-*/";
	int i = 0, res;
	// the last gene is useless 
	while (i < (NBGENE - 1)) {
		res = lire(gene, i);
		if (i % 2) {
			printf("%c ", code[res % 4]);
		}
		else {
			printf("0x%x ", res);
		}
		i = i + 1;
	}
	printf("\n");
}

void calcul (Serpent *g) {

	int *operande, *operator;
	if ((operande = malloc(sizeof(int) * NBGENE)) == NULL) { exit(EXIT_FAILURE); }
	if ((operator = malloc(sizeof(int) * NBGENE - 1)) == NULL) { exit(EXIT_FAILURE); }


	fillOpe(operande, operator, g->gene);


	affiche(g->gene);
	g->score = calculScore(operator, operande);

	free(operande);
	free(operator);
}

void affcalcul(int * operande , int * operator)
{
	char code[] = "+-*/";
	int a;
	for(int i = 0 ; i <NBGENE /2 -1 ; i++)
	{
		a = operande[i] == -1 ? 0 : operande[i];
		printf("%d %c ",a,code[operator[i]]);
	}
	printf("%d \n",operande[NBGENE/2-1]);
}
int calculScore (int *operator, int *operande) {

	int number1;
	int number2;
	int idOperande1, idOperande2;
	int result = 0;

	affcalcul(operande,operator);

	for (int i = 0; i < NBGENE / 2 - 1; i++) {
		if (operator[i] == 2 || operator[i] == 3) {
			idOperande1 = getfirstOperandID(operande,i);
			idOperande2 = getSecondOperandID(operande,i+1);
			number1 = operande[idOperande1];
			number2 = operande[idOperande2];
			switch (operator[i]) {
				case 3:
					if (number2 == 0) {
						return MAX;
					}
					operande[idOperande1] = number1 / number2;
					operande[idOperande2] = -1;
					operator[i] = 0;
					break;
				case 2: operande[idOperande1] = number1 * number2;
					operande[idOperande2] = -1;
					operator[i] = 0;
					break;
			}
			affcalcul(operande,operator);


		}
	}

	result = operande[0] ==-1 ? 0 : operande[0];
	for (int i = 0; i < NBGENE / 2 - 1; i++) {
		idOperande1 = i+1;
		number1 = operande[idOperande1] ==-1 ? 0 : operande[idOperande1];

		switch (operator[i]) {
			case 0:result += (number1);
				break;
			case 1: result -= (number1);
				break;
		}
	}
	return abs(result -666);

}

int getfirstOperandID(int* operande, int theoricalFirst)
{
	int id = theoricalFirst;
	while(operande[id] == -1 && id !=0)
	{
		id--;
	}
	return id;
}
int getSecondOperandID(int *operande, int theoricalSecond)
{
	int id = theoricalSecond;

	while(operande[id] == -1 && id !=NBGENE/2)
	{
		id++;
	}
	return id;
}

void fillOpe (int *operande, int *operator, unsigned char *gene) {

	int i = 0, res;
	int operandeID = 0;
	int operatorID = 0;

	while (i < (NBGENE - 1)) {
		res = lire(gene, i);
		if (i % 2) {
			operator[operatorID++] = res % 4;
		}
		else {
			operande[operandeID++] = res;
		}
		i++;
	}

}


void testCalcul () {

	int i, expect;
	Serpent test[] = {
			{"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a", 660},
			{"\x66\x32\x0d\xb7\x31\x58\xa3\x5a\x25\x5d\x05\x17\x58\xe9\x5e\xd4\xab\xb2\xcd\xc6\x9b\xb4\x54\x11\x0e\x82\x74\x41\x21\x3d\xdc\x87", 735},
			{"\x70\xe9\x3e\xa1\x41\xe1\xfc\x67\x3e\x01\x7e\x97\xea\xdc\x6b\x96\x8f\x38\x5c\x2a\xec\xb0\x3b\xfb\x32\xaf\x3c\x54\xec\x18\xdb\x5c", 694},
			{"\x02\x1a\xfe\x43\xfb\xfa\xaa\x3a\xfb\x29\xd1\xe6\x05\x3c\x7c\x94\x75\xd8\xbe\x61\x89\xf9\x5c\xbb\xa8\x99\x0f\x95\xb1\xeb\xf1\xb3", 646},
			{"\x05\xef\xf7\x00\xe9\xa1\x3a\xe5\xca\x0b\xcb\xd0\x48\x47\x64\xbd\x1f\x23\x1e\xa8\x1c\x7b\x64\xc5\x14\x73\x5a\xc5\x5e\x4b\x79\x63", MAX},
			{"\x3b\x70\x64\x24\x11\x9e\x09\xdc\xaa\xd4\xac\xf2\x1b\x10\xaf\x3b\x33\xcd\xe3\x50\x48\x47\x15\x5c\xbb\x6f\x22\x19\xba\x9b\x7d\xf5", 543},
			{"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05", 1302},
			{"\xac\x86\x21\x2b\xaa\x1a\x55\xa2\xbe\x70\xb5\x73\x3b\x04\x5c\xd3\x36\x94\xb3\xaf\xe2\xf0\xe4\x9e\x4f\x32\x15\x49\xfd\x82\x4e\xa9", MAX},
			{"\x08\x70\xd4\xb2\x8a\x29\x54\x48\x9a\x0a\xbc\xd5\x0e\x18\xa8\x44\xac\x5b\xf3\x8e\x4c\xd7\x2d\x9b\x09\x42\xe5\x06\xc4\x33\xaf\xcd", MAX},
			{"\xa3\x84\x7f\x2d\xad\xd4\x76\x47\xde\x32\x1c\xec\x4a\xc4\x30\xf6\x20\x23\x85\x6c\xfb\xb2\x07\x04\xf4\xec\x0b\xb9\x20\xba\x86\xc3", MAX},
			{"\x3e\x05\xf1\xec\xd9\x67\x33\xb7\x99\x50\xa3\xe3\x14\xd3\xd9\x34\xf7\x5e\xa0\xf2\x10\xa8\xf6\x05\x94\x01\xbe\xb4\xbc\x44\x78\xfa", 727}
	};

	for (i = 0; i < sizeof(test) / sizeof(Serpent); i++) {
		expect = test[i].score;
		calcul(&test[i]);
		if (expect != test[i].score) { printf("error\n"); }
	}
}

void selection (groupe *population, groupe *parents) {
}

int evaluation (groupe *population) {
}

void generationAleatoire (groupe *population) {
}

void reproduction (groupe *population, groupe *parents) {
}

void mutation (groupe *population) {
}



