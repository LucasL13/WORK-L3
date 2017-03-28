#include "draw.h"
#include <stdio.h>
#include "koch.h"



void draw_polygon(Ez_window win, PLISTE list){

	EPOINT point1, point2, premierpoint;
	int i=0;

	if(list != NULL && list -> next != NULL){
		premierpoint.x = list -> x;
		premierpoint.y = list -> y;
		
		point1.x = list -> x;
		point1.y = list -> y;

	
		list = list -> next;
	
		while(list != NULL){ 
	
			
		
			point2.x = list -> x;
			point2.y = list -> y;
		
			ez_draw_line(win, point1.x, point1.y, point2.x, point2.y);
			
			point1.x = point2.x;
			point1.y = point2.y;
			
			
			list = list -> next;
		}
	
		ez_draw_line(win, point2.x, point2.y, premierpoint.x, premierpoint.y);
	
	}

}

void anim_koch(Ez_window win, int i){

	
	
	PLISTE list = NULL;
	
	
	
	switch (i){
		case 0:
			list = lire_liste("koch/k0.in");			
			break;
		case 1:
			list = lire_liste("koch/k1.in");
			break;
		case 2:
			list = lire_liste("koch/k2.in");
			break;
		case 3:
			list = lire_liste("koch/k3.in");
			break;
		case 4:
			list = lire_liste("koch/k4.in");
			break;
		case 5:
			list = lire_liste("koch/k5.in");
			break;
		case 6:
			list = lire_liste("koch/k6.in");
			break;

		case 7:
			list = lire_liste("koch/k7.in");
			break;
		case 8:
			list = lire_liste("koch/k8.in");
			break;
		case 9:
			list = lire_liste("koch/k9.in");
			break;
		
	}
	draw_polygon(win,list);

	
	
	
}

int get_centery(int x, int y, int c){

	double x2 = x+c, y2 = y, tmpx = c/2.0, tmpy = y2 - y, nouvy;
	double alpha = PI * 30 / 180;
	nouvy = tmpx*sin(alpha) + tmpy*cos(alpha);
	return y-nouvy;
	
	
}

void draw_frac_carre(Ez_window win, PLISTE list, int taille, int posx, int poxy){

	



}

void draw_buttons(Ez_window win, int x, int y){

	Data *d = ez_get_data(win);
	d -> menux = x;
	d -> menuy = y;
	ez_set_color (ez_black);
	ez_set_nfont (2);
	
	
            
	//int focus_on_buttonup = 0, focus_on_buttondown = 0, focus_on_buttonup10 = 0, focus_on_buttondown10 = 0;
	
	switch(d -> select){
		case 1:
			ez_image_paint(win,d->selection,x+315,y-20);
			break;
		case 2:
			ez_image_paint(win,d->selection,x+315,y+40);
			break;
		case 3: 
			ez_image_paint(win,d->selection,x+175,y-20);
			break;
			
		default: break;
	
	}
	
	
	ez_image_paint(win,d->buttoncenter,x+320,y-15); // taille
	ez_image_paint(win,d->buttoncenter,x+320,y+45); // niveau
								
	ez_image_paint(win,d->buttoncenter,x+180,y-15); // reglage animation

	if(d->focus == 1) ez_image_paint(win,d->resetactive,x+380 ,y - 15); // reset
	else ez_image_paint(win,d->reset,x+380 ,y - 15); // reset
	if(d->focus == 2) ez_image_paint(win,d->saveactive,x+380 ,y +45); // save
	else ez_image_paint(win,d->save,x+380 ,y +45); // save
	ez_image_paint(win,d->buttonrun,x+180 ,y+45); // play
	
	ez_draw_text (win, EZ_TC, x+345, y, "%d", d->tailleKoch);
	ez_draw_text (win, EZ_TC, x+345, y+60, "%d", d->nivKoch);
	ez_draw_text (win, EZ_TC, x+205, y, "%d", d->anim);
	
	ez_draw_text (win, EZ_TC, x+270, y, "Taille");
	ez_draw_text (win, EZ_TC, x+270, y+60, "niveau");
	ez_draw_text (win, EZ_TC, x+120, y, "type anim"); // type d'animation
	
	ez_draw_text (win, EZ_TC, x+90, y+60, "Remplir : r"); 

	
	
}


void draw_buttons_julia(Ez_window win, int x, int y){

	Data *d = ez_get_data(win);
	d -> menux = x;
	d -> menuy = y;
	ez_set_color (ez_black);
	ez_set_nfont (2);
	
	
            
	//int focus_on_buttonup = 0, focus_on_buttondown = 0, focus_on_buttonup10 = 0, focus_on_buttondown10 = 0;
	
	switch(d -> select){
		case 1:
			ez_image_paint(win,d->selection,x+115,y-20);
			break;
		case 2:
			ez_image_paint(win,d->selection,x+115,y+40);
			break;
		
			
		default: break;
	
	}
	
	
	ez_image_paint(win,d->buttoncenter,x+120,y-15); // iteration_Max
	ez_image_paint(win,d->buttoncenter,x+120,y+45); // niveau
								
	

	if(d->focus == 1) ez_image_paint(win,d->resetactive,x+180 ,y - 15); // reset
	else ez_image_paint(win,d->reset,x+180 ,y - 15); // reset
	if(d->focus == 2) ez_image_paint(win,d->saveactive,x+180 ,y +45); // save
	else ez_image_paint(win,d->save,x+180 ,y +45); // save
	
	ez_set_color(ez_red);
	ez_draw_text (win, EZ_TC, x+145, y, "%d", d->iter_max);
	ez_draw_text (win, EZ_TC, x+145, y+60, "%d", d->type_julia);
	
	
	ez_draw_text (win, EZ_TC, x+60, y, "iterations");
	ez_draw_text (win, EZ_TC, x+70, y+60, "type");
	
	ez_set_color(ez_black);
	 

	
	
}

void remplir_flocon(Ez_window win) {
	Data *d = ez_get_data(win);
	int x = LARGEUR/2 - (d->tailleKoch*50)/2 ,y = (HAUTEUR-HMENU)/2 + (sqrt(3.0)/2.0*((d->tailleKoch*50)/2.0))/1.4;
	PLISTE act, prec, suiv, fin;
	PLISTE list = NULL;
	double j = 0.0;
	int niv = d -> nivKoch;
	ez_set_thick(2);
	
	for(int i = 0; i <= niv; i++) {
		j = 0.;
		if(i == 0) {
			list = triangle(x,y,d->tailleKoch*50);
			act = list -> next;
			suiv = act -> next;
			ez_fill_triangle(win, list ->x, list -> y, act -> x, act -> y, suiv -> x, suiv -> y);
			ez_draw_triangle(win, list ->x, list -> y, act -> x, act -> y, suiv -> x, suiv -> y);
		}
		else if(i > 0) {
			list = koch(i,x,y,d->tailleKoch*50);
			prec = list -> next; 	
			act = prec -> next;
			suiv = act -> next;
			ez_fill_triangle(win, prec ->x, prec -> y, act -> x, act -> y, suiv -> x, suiv -> y);
			while(j < 3.0*(pow(4.,(double)(i-1)))-1.0){
				prec = suiv -> next -> next;
				act = prec -> next;
				suiv = act -> next;
				ez_fill_triangle(win, prec -> x, prec -> y, act -> x, act -> y, suiv -> x, suiv -> y);
				ez_draw_triangle(win, prec -> x, prec -> y, act -> x, act -> y, suiv -> x, suiv -> y);
				j++;
						
			}
		}
	}
	ez_set_thick(1);
	
}


void genere_carre(double taille, double posx, double posy){

	FILE* f1 = fopen("carre.out","w");	
	fprintf(f1,"%.2lf %.2lf\n",posx,posy);
	fprintf(f1,"%.2lf %.2lf\n",posx+taille,posy);
	fprintf(f1,"%.2lf %.2lf\n",posx+taille,posy+taille);
	fprintf(f1,"%.2lf %.2lf\n",posx,posy+taille);
	fclose(f1);
	
}


void draw_anim_calcul(Ez_window win){

	Data *d = ez_get_data(win);
	int x = LARGEUR/2 - 102;
	int y = HAUTEUR/2 - 25;

	for(int i=0;i<4;i++){
				
		ez_draw_circle(win,x+i*55,y,(x+50)+i*55,y+50);
	}

	switch(d -> anim_calcul){

		case 0:		
			ez_fill_circle(win,x,y,x+50,y+50);
			break;
		case 1:		
			ez_fill_circle(win,x+55,y,x+105,y+50);
			break;
		case 2:		
			ez_fill_circle(win,x+110,y,x+160,y+50);
			break;
		case 3:		
			ez_fill_circle(win,x+165,y,x+215,y+50);
			break;

	}

}








