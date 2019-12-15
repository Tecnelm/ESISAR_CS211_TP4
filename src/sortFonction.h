//
// Created by clement on 12/15/19.
//

#ifndef ESISAR_CS211_TP4_SORTFONCTION_H
#define ESISAR_CS211_TP4_SORTFONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include "AlgoGenetique.h"

void sort(Groupe* population);
void merge (Serpent* tab, Serpent* tmp, int left, int mid, int right, int* cnt);
void mergeSort (Serpent* tab,Serpent* tmp, int left, int right, int* cnt);
#endif //ESISAR_CS211_TP4_SORTFONCTION_H
