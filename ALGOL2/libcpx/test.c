#include "cplx.h"
#include "cplxio.h"
#include "cplxop.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Fichier test.
 * A completer pour autres operations.
 */
   
int testAddition() {
	int nTest=0;
	char encore = 'y';
	do {
		printf("* SOMME ***************\nEntrez deux complexes :\n");
		COMPLEXE * z1 = lire_complexe();
		COMPLEXE * z2 = lire_complexe();
		COMPLEXE * res_z = add_cplx(z1, z2);
		printf("La somme est: ");
		ecrire_complexe(res_z);
		nTest++;
		printf("\n");
		free(z1);
		free(z2);
		free(res_z);
		printf("->> Encore (y/n) ? ");
		clean_stdin();
		scanf("%c", &encore);
	} while (encore=='y');
	return nTest;
}

int testMultiplication() {
	int nTest=0;
	char encore = 'y';
	do {
		printf("* PRODUIT ***************\nEntrez deux complexes :\n");
		COMPLEXE * z1 = lire_complexe();
		COMPLEXE * z2 = lire_complexe();
		COMPLEXE * res_z = mul_cplx(z1, z2);
		printf("Le produit est: ");
		ecrire_complexe(res_z);
		nTest++;
		printf("\n");
		free(z1);
		free(z2);
		free(res_z);
		printf("->> Encore (y/n) ? ");
		clean_stdin();
		scanf("%c", &encore);
	} while (encore=='y');
	printf("encore = %c\n", encore);
	return nTest;	
}
	

int main() {
	return testAddition()+testMultiplication(); 
}
