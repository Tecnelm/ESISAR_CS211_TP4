#ifndef NBPOPULATION
#define NBPOPULATION 1000
#endif

#ifndef NBPARENTS
#define NBPARENTS 10
#endif

#define MAX 2000000
#define SEEK 666

#ifndef NBGENE
#define NBGENE 64
#endif

#ifndef MUTATEGEN
#define MUTATEGEN 10
#endif

#include "sortFonction.h"

#ifndef SERPENT
#define SERPENT
typedef struct {
	unsigned char gene[NBGENE / 2];
	int score;
} Serpent;

typedef struct {
	Serpent *membres;
	int nombre;
} Groupe;
#endif

void affiche (unsigned char *gene);

void calcul (Serpent *g);

void selection (Groupe *population, Groupe *parents);

int evaluation (Groupe *population);

void generationAleatoire (Groupe *population);

void reproduction (Groupe *population, Groupe *parents);

void mutation (Groupe *population);

void testCalcul ();


void fillOpe (int *operande, int *operator, unsigned char *gene);

int calculScore (int *operator, int *operande);


int getfirstOperandID (int *operande, int theoricalFirst);

int getSecondOperandID (int *operande, int theoricalSecond);

void affcalcul (int *operande, int *operator);
