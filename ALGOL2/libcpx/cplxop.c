#include "cplx.h"
#include "cplxio.h"
#include <stdio.h>
#include <stdlib.h>

/* Calcule la somme de deux complexes 
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeurs vers des complexes (operandes)
 * OUTPUT: pointeur sur resultat, un complexe.
 */
COMPLEXE * add_cplx (COMPLEXE* z1, COMPLEXE* z2) {

	double re = z1 -> re + z2 -> re;
	double im = z1 -> im + z2 -> im;
	COMPLEXE* z = create_complexe(re,im);
	return z;

}



/* Calcule la soustraction entre deux complexes z1-z2 
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeurs vers des complexes (operandes)
 *        entier, si 1 = moins unaire (oppose) (on récupèrera l'opposé du premier agurment), si 2 = moins binaire 

 * OUTPUT: pointeur sur resultat, un complexe.
 */
COMPLEXE * moins_cplx (COMPLEXE* z1, COMPLEXE* z2,int code)  {
	
	if(code == 2) {
		double re = z1 -> re - z2 -> re;
		double im = z1 -> im - z2 -> im;
		COMPLEXE* z = create_complexe(re,im);
		return z;
	}
	else if(code == 1) {
		double re = - z1 -> re;
		double im = - z1 -> im;
		COMPLEXE* z = create_complexe(re,im);
		return z;
	}
	else {
		printf("Choisir entre la soustraction unaire, avec 1, et binaire, avec 2");
		return 0;
	}


}
/* Calcule la multiplication entre deux complexes 
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeurs vers des complexes (operandes)
 * OUTPUT: pointeur sur resultat, un complexe.
 */

COMPLEXE * mul_cplx (COMPLEXE* z1, COMPLEXE* z2) {

	double re = (z1 -> re)*(z2 -> re) - (z1 -> im)*(z2 -> im);
	double im = (z1 -> re)*(z2 -> im) + (z1 -> im)*(z2 -> re);
	COMPLEXE* z = create_complexe(re,im);
	return z;

}

/* Calcule le produit d'un complexe et d'un reel
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeur sur un complexe et un reel (operandes)
 * OUTPUT: pointeur sur resultat, un complexe.
 */
COMPLEXE * mul_cplx_reel (COMPLEXE* z1, double a)  {

	double re = a * (z1 -> re);
	double im = a * (z1 -> im);
	COMPLEXE* z = create_complexe(re,im);
	return z;

}

