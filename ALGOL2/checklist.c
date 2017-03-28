#include "checklist.h"

Checklist* init_checklist(){

	Checklist *cl = malloc(sizeof(Checklist));
	cl -> rb = NULL;
	cl -> elem = 0;

}

/* ajoute un bouton et initialise ses champs */

Radiobutton* add_button(Radiobutton *rb, char str[BUFFER_RB]){


	Radiobutton *tmp = malloc(sizeof(Radiobutton));
	tmp -> next = rb;
	tmp -> ENABLE = 0;

	for(int i=0 ; i<BUFFER_RB ; i++){
		tmp -> str[i] = str[i];
	}

	return tmp;
	
}

void enable_button(Radiobutton *rb, int i, int max){

	Radiobutton *tmp = rb;

	for(int j=0 ; j<max ; j++){
		if(j == i) tmp -> ENABLE = 1;
		else tmp -> ENABLE = 0;
		if(tmp -> next == NULL) break; 
		tmp = tmp -> next;
		
	}


}









