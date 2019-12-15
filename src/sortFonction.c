//
// Created by clement on 12/15/19.
//
#include "sortFonction.h"

void sort(Groupe* population )
{
	int cnt =0;
	Serpent* temps;
	if ((temps=malloc(sizeof(Serpent)*population->nombre)) == NULL ) exit(EXIT_FAILURE);
	mergeSort(population->membres, temps, 0, population->nombre-1,&cnt);
	free(population->membres);
	population->membres = temps;
}

void mergeSort(Serpent *tab, Serpent *tmp, int left, int right, int *cnt) {
	int mid;
	if (abs(left - right) > 0) { // do the condition if the table isn't a single tab
		mid = (left + right) / 2;
		mergeSort(tab, tmp, left, mid, cnt);
		mergeSort(tab, tmp, mid + 1, right, cnt);

		merge(tab, tmp, left, mid + 1, right, cnt);
	}
}

void merge(Serpent *tab, Serpent *tmp, int left, int mid, int right, int *cnt) {
	int indexTab1 = left, indexTab2 = mid;
	int indextmp = left;
	int nbModify = 0;
	/*
	 * decompose a main table with index right mid and left mid  is the 1st element of right table
	 * compare each element in a logic order, between the two tab , when one is higher it's placed in the temp table and is counter of the
	 * of this table is incremented
	 */
	if (tab[mid - 1].score < tab[mid].score) { // compare the last element of the first table and the first of the second table , as they are already sort we can abort the merge turn
		(*cnt)++;
		return;
	}
	while (indexTab1 < mid && indexTab2 <= right) {
		if (tab[indexTab1].score < tab[indexTab2].score) {
			tmp[indextmp] = tab[indexTab1];
			indexTab1++;
		} else {
			tmp[indextmp] = tab[indexTab2];
			indexTab2++;
		}
		(*cnt)++;
		nbModify++;
		indextmp++;
	}
	while (indexTab1 < mid)//  if it have element in the right table  copy them at the end of the tmp table
	{
		tmp[indextmp++] = tab[indexTab1++];
		(*cnt)++;
		nbModify++;
	}

	//copy the tmp table into the main table
	for (indextmp = left; indextmp < nbModify + left; indextmp++) {
		tab[indextmp] = tmp[indextmp];

	}
}