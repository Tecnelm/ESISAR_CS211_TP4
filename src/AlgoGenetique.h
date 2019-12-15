#ifndef NBPOPULATION
#define NBPOPULATION 1000 
#endif 

#ifndef NBPARENTS
#define NBPARENTS 50 
#endif

#define MAX 2000000
#define SEEK 666

#ifndef NBGENE
#define NBGENE 64
#endif 

typedef struct {
	unsigned char gene[NBGENE/2];  
	int score; 
} Serpent; 

typedef struct { 
	Serpent *membres; 
	int nombre; 
} groupe; 



void affiche(unsigned char *gene); 
void calcul(Serpent *g); 
void selection(groupe *population,groupe *parents); 
int evaluation(groupe *population); 
void generationAleatoire(groupe *population); 
void reproduction(groupe *population,groupe *parents); 
void mutation (groupe *population);

void testCalcul();


void fillOpe(int* operande,int *operator,unsigned char* gene);
int calculScore (int *operator, int *operande);


int getfirstOperandID(int* operande, int theoricalFirst);
int getSecondOperandID(int* operande, int theoricalSecond);

void affcalcul(int * operande , int * operator);
