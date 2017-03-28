#include "listep.h"
#include "listep_op.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Fichier test des listes.
 * A completer pour autres operations.
 */
   
int testLectureEcriture() {
	PLISTE pl = lire_liste("liste.in");
	ecrire_liste("liste.out", pl);
	ecrire_liste("liste2.out", pl);
	return 0;
}
	

int main() {
	return testLectureEcriture();
}
