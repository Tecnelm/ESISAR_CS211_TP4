#ifndef NBPOPULATION
#define NBPOPULATION 10
#endif 

#ifndef NBPARENTS
#define NBPARENTS 2
#endif 

#define MAX 2000000
#define SEEK 666

#ifndef NBGENE
#define NBGENE 10
#endif

#define END 666

typedef struct {
	unsigned char gene[NBGENE];
	int score; 
} serpent; 

typedef struct { 
	serpent *membres; 
	int nombre; 
} groupe; 



void affiche(unsigned char *gene); 
void calcul(serpent *g); 
void selection(groupe *population,groupe *parents); 
int evaluation(groupe *population); 
void generationAleatoire(groupe *population); 
void reproduction(groupe *population,groupe *parents); 
void mutation (groupe *population);
void insertionSort (int *tabPop, int *tabInd, int size);


