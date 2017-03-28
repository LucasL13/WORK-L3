#ifndef __MENU__
#define __MENU__
#define TAILLEBOX 25
#include "checklist.h"

/* ce fichier contient le necessaire a l'animation et la création du widget "menu" */

typedef struct {

	int x,y,hauteur,largeur;
	Checklist *cl;
	
	

}Menu;

Menu* create_menu();
void set_pos_x(Menu *men, int x);
void set_pos_y(Menu *men, int y);
void print_menu(Ez_window win, Menu *men);
void destroy_menu(Menu *men);
void draw_menu(Ez_window win, Menu *men,int step);
void draw_checklist(Ez_window win, Checklist *cl, int x, int y);
void valider_choix(Ez_window win, int max);

#endif
