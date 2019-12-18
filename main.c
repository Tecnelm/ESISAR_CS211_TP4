#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include "src/AlgoGenetique.h"


#define TES


#ifndef TEST

int main (int argc, char *argv[]) {

	int moyenne;

	int opt, nbgeneration = 0;
	Groupe population, parents;

	// les valeurs par defaut.
	population.nombre = NBPOPULATION;
	parents.nombre = NBPARENTS;

	while ((opt = getopt(argc, argv, "p:P:")) != -1) {
		switch (opt) {
			case 'p': population.nombre = atoi(optarg);
				break;
			case 'P': parents.nombre = atoi(optarg);
				break;
			default: /* '?' */
				fprintf(stderr, "Usage: %s [-p nbpopulation] [-P nbparents] \n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	// test et allocation mémoire. 
	if (parents.nombre > population.nombre) { exit(EXIT_FAILURE); }

	if ((population.membres = malloc(sizeof(Serpent) * population.nombre)) == NULL) { exit(EXIT_FAILURE); }
	if ((parents.membres = malloc(sizeof(Serpent) * parents.nombre)) == NULL) { exit(EXIT_FAILURE); }

	// creation de la premiere génération 
	generationAleatoire(&population);

	while (evaluation(&population, &moyenne)) {
		selection(&population, &parents);
		printf("Generation %d \nle meilleur score est : %d \nla moyenne est : %d \n", nbgeneration, population.membres[0].score, moyenne);
		reproduction(&population, &parents);
		mutation(&population);
		nbgeneration++;
	}

	printf("\nGeneration %d\n", nbgeneration);
	printf("Serpent malefique !! voici son ADN : \n");
	affiche(population.membres[0].gene);
	free(population.membres);
	free(parents.membres);

}

#else

int main (int argc, char *argv[]) {

	testCalcul();
}

#endif

