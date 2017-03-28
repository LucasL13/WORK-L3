#include <stdio.h>
#include <stdlib.h>
#include "listep.h"
#define BUFFER 1000

PLISTE init_liste(double xx, double yy){

	PLISTE list = malloc(sizeof(EPOINT));
	list -> x = xx;
	list -> y = yy;
	list -> next = NULL;
	return list;

}

EPOINT * insert_after(EPOINT * elt, double xx, double yy){

	PLISTE point = malloc(sizeof(EPOINT));
	point -> x = xx;
	point -> y = yy;
	point -> next = elt -> next; 
	elt -> next = point;
	
	return point;
}

EPOINT * remove_after(EPOINT * elt){

	PLISTE tmp = elt -> next -> next;
	free(elt -> next);
	elt -> next = tmp;
	return elt;

}

PLISTE lire_liste(char * nf){
	PLISTE list, tmp;
	FILE* f = fopen(nf, "r");
	char ch[BUFFER];
	double xx, yy;

	fgets(ch,BUFFER,f);
	sscanf(ch,"%lf %lf",&xx,&yy);
	list = init_liste(xx,yy);
	tmp = list;

	while (fgets(ch,BUFFER,f))
	{
		if (sscanf(ch,"%lf %lf",&xx,&yy)==2){
			list = insert_after(list, xx, yy);
			
		}
	}
	fclose(f);
	return tmp;
}

void ecrire_liste(char * nf, PLISTE pl){

	FILE* f = fopen(nf,"w");

	if(f == NULL){
		
	}
	else{
		while(pl != NULL){
			fprintf(f,"%.2lf %.2lf\n",pl -> x,pl -> y);
			pl = pl -> next;
		}
	
	fclose(f);
	}
}
