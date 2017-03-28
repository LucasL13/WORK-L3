#include "ez-draw.h"
#include "ez-image.h"
#include "menu.h"
#include "Fractale.h"


Menu* create_menu(){

	Menu *men = malloc(sizeof(Menu));
	men -> x = 0;
	men -> y = 0;
	men -> hauteur = 100;
	men -> largeur = 100;
	men -> cl = init_checklist();
	
	return men; 
	
}

void destroy_menu(Menu *men){
	free(men);
}

/* setters */

void set_pos_x(Menu *men, int x){ 

	men -> x = x;

}

void set_pos_y(Menu *men, int y){

	men -> y = y;


}

/* affichage et animations */

void print_menu(Ez_window win, Menu *men){

	ez_set_color(ez_grey);
	ez_fill_rectangle(win,men->x,men->y,men->x+men->largeur,men->y+men->hauteur);
	ez_set_color(ez_black);
	ez_draw_rectangle(win,men->x,men->y,men->x+men->largeur,men->y+men->hauteur);	

}

void draw_menu(Ez_window win, Menu *men,int step){

	int largeur,hauteur;
	Menu *men2 = malloc(sizeof(Menu)); 	
	
	
	men2 -> y = HAUTEUR/2;

	if(step > 20){
		largeur = men -> largeur;
		hauteur = men -> hauteur;
	}
	else {
		largeur = men -> largeur;
		hauteur = men -> hauteur/20*step;
	}
	
	men2 -> x = men -> x;
	men2 -> y = men2 -> y - hauteur/2;
	men2 -> largeur = largeur;
	men2 -> hauteur = hauteur;

	print_menu(win, men2);	

}


void draw_checklist(Ez_window win, Checklist *cl, int x, int y){

	Data *d = ez_get_data(win);
	ez_set_nfont (2);
	
	Radiobutton *rb = cl -> rb;
	int decalage_x = 20, decalage_y = 20;
	
	while(rb != NULL){
		
		if(rb -> ENABLE) ez_image_paint(win,d -> checkboxenable,x+decalage_x,y+decalage_y);
		else ez_image_paint(win,d -> checkboxdisable,x+decalage_x,y+decalage_y);
		ez_set_color(ez_black);
		ez_draw_text(win,EZ_TC, x+2*decalage_x+2*TAILLEBOX+25, y+decalage_y+2,rb -> str);
		decalage_y = decalage_y + TAILLEBOX + 15;
		rb = rb->next;

	}

}

void valider_choix(Ez_window win, int max){

		Data *d = ez_get_data(win);
		Radiobutton *tmp = d -> men -> cl -> rb;				
				
		for(int i=0 ; i<(d->men->cl->elem) ; i++){
		
			if(tmp -> ENABLE){ d-> button_checked = i;break;}
			tmp = tmp -> next;
	
		}
		
		
}





