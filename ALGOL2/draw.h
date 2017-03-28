#ifndef __DRAWOP__
#define __DRAWOP__

#include "ez-draw.h"
#include <stdio.h>
#include "listep.h"
#include "listep_op.h"
#include "Fractale.h"


void draw_polygon(Ez_window win, PLISTE list);
void draw_frac_carre(Ez_window win, PLISTE list, int taille, int posx, int poxy);
void genere_carre(double taille, double posx, double posy);
void anim_koch(Ez_window win, int i);
void draw_buttons(Ez_window win, int x, int y); 	
int get_centery(int x, int y, int c);
void remplir_flocon(Ez_window win);
void tracer_seg_bresenham(int x0, int y0, int x1, int y1, int pixmap[][1000]);
void draw_buttons_julia(Ez_window win, int x, int y);
void draw_anim_calcul(Ez_window win);

#endif 
