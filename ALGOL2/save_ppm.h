#ifndef __save_ppm__
#define __save_ppm__

#include "listep.h"
#include "Fractale.h"
#include "listep.h"
#include "listep_op.h"
#include "koch.h"

void save_koch(int n, double c, int choix);
void save_ppm_koch(char* name, int pixmap[][LARGEUR], int largeur, int hauteur);
void draw_and_save(PLISTE list, int pixmap[][LARGEUR]);
void init_pixmap(int pixmap[][LARGEUR]);
void save_ppm_from_pixmap(Ez_image *img, char* name);

#endif
