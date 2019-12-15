#ifndef NBPOPULATION
#define NBPOPULATION 500
#endif

#ifndef NBPARENTS
#define NBPARENTS 100
#endif

#define MAX 2000000
#define SEEK 666

#ifndef NBGENE
#define NBGENE 64
#endif

#ifndef MUTATEGEN
#define MUTATEGEN 20
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

#ifndef ESISAR_CS211_TP4_ALGOGENETIQUE_H
#define ESISAR_CS211_TP4_ALGOGENETIQUE_H
#include <math.h>
void affiche (unsigned const char *gene);

void calcul (Serpent *g);

void selection (Groupe *population, Groupe *parents);

int evaluation (Groupe *population);

void generationAleatoire (Groupe *population);

void reproduction (Groupe *population, Groupe *parents);

void mutation (Groupe *population);

void testCalcul ();


void fillOpe (int *operande, int *operator, unsigned const char *gene);

int calculScore (int *operator, int *operande);


int getfirstOperandID (int const *operande, int const theoricalFirst);

int getSecondOperandID (int const *operande, int const theoricalSecond);

void affcalcul (int const *operande, int const *operator);
#endif