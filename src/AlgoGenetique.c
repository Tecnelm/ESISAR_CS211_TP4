#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include "time.h"
#include <arpa/nameser.h>
#include "AlgoGenetique.h"


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

void calcul (serpent *g) {
	//--------------- traduction des operandes
	int i = 0;
	char geneTraduit[NBGENE - 1];
	char code[] = "+-*/";

	for (i; i < (NBGENE - 1); i++) {
		if (i % 2) {
			geneTraduit[i] = code[(g->gene[i]) & 0b0011];
		}
		else {
			geneTraduit[i] = g->gene[i];
		}
	}

	//-------------- determination des delimitations de priorité
	int j = 0;
	int k = 0;
	int tilt = 1;
	int delimitation_parenthese[NBGENE];

	for (j; j < (NBGENE - 1); j++) {
		if (j % 2) {
			if (geneTraduit[j] == '*' || geneTraduit[j] == '/') {
				if (tilt) {
					delimitation_parenthese[k] = j - 1;
					tilt = 0;
					k++;
				}
			}
			else {
				if (!tilt) {
					delimitation_parenthese[k] = j - 1;
					tilt = 1;
					k++;
				}
			}
		}
	}
	delimitation_parenthese[k] = END;

	//------------- somme des termes
	int parenthese = 0;
	int l = 0;
	int indexParenthese;
	int nbTermeParenthese;
	int buffer = 0;
	g->score = 0;
	k = 0;


	for (l; l < (NBGENE - 1); l++) {
		if (l == delimitation_parenthese[k] && !parenthese && delimitation_parenthese[k + 1] != END) {
			parenthese = 1;
			k++;
		}
		if (parenthese) {
			nbTermeParenthese = delimitation_parenthese[k] - delimitation_parenthese[k - 1];
			buffer = geneTraduit[delimitation_parenthese[k - 1]];

			for (indexParenthese = delimitation_parenthese[k - 1]; indexParenthese < delimitation_parenthese[k]; indexParenthese++) {
				if (indexParenthese % 2 == 1) {
					if (geneTraduit[indexParenthese] == '*') {
						buffer = buffer * geneTraduit[indexParenthese + 1];
					}
					else if (geneTraduit[indexParenthese] == '/' && geneTraduit[indexParenthese + 1] != 0) {
						buffer = buffer / geneTraduit[indexParenthese + 1];
					}
					else {
						g->score = MAX;
						exit(EXIT_SUCCESS);
					}
				}
			}
			if (geneTraduit[delimitation_parenthese[k - 1] - 1] == '-') {
				g->score = g->score - buffer;
			}
			else {
				g->score = g->score + buffer;
			}
			buffer = 0;
			l = l + (nbTermeParenthese - 1);
			parenthese = 0;
			k++;
		}
		else if (l % 2 == 0 && geneTraduit[l - 1] != '/' && geneTraduit[l - 1] != '*') {
			if (geneTraduit[l - 1] == '-') {
				g->score = g->score - geneTraduit[l];
			}
			else {
				g->score = g->score + geneTraduit[l];
			}
		}
	}
	//g->score = abs(g->score - 666);
}


void testCalcul () {

	int i, expect;
	serpent test[] = {
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

	for (i = 0; i < sizeof(test) / sizeof(serpent); i++) {
		expect = test[i].score;
		calcul(&test[i]);
		if (expect != test[i].score) { printf("error\n"); }
	}
}

void insertionSort (int *table, int size) {

	int index;
	int index2;
	int varToSort;
	int nbaction = 0;

	for (index = 1; index < size; index++) {
		varToSort = *(table + index);
		index2 = index;
		nbaction++;
		while (index2 > 0 && varToSort < table[index2 - 1]) {// programme stable grâce à l'inégalité stricte.
			table[index2] = table[index2 - 1];
			index2--;
			nbaction++;
		}
		table[index2] = varToSort;
	}
}

void selection (groupe *population, groupe *parents) {
	int i;
	char tab[NBPOPULATION][2];

	for (i = 0; i < population->nombre; ++i) {
		calcul(&(population->membres[i]));
		tab[i][0] = (population->membres[i]).score;
		tab[1][i] = i;
	}



}

int evaluation (groupe *population) {

	int i;
	for (i = 0; i < population->nombre; ++i) {
		if (((population->membres)->score) == 0) {
			return 0;
		}
	}
	return 1;
}

void generationAleatoire (groupe *population) {

	int i = 0, j = 0;
	srand(time(NULL));

	for (i; i < population->nombre; i++) {
		for (j; j < (NBGENE - 1); j++) {
			(population->membres[i]).gene[j] = rand() % 16;
		}
	}
}

void reproduction (groupe *population, groupe *parents) {
}

void mutation (groupe *population) {
}



