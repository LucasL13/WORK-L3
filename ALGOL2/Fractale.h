#ifndef __FRACTALE__
#define __FRACTALE__

#include "ez-draw.h"
#include "ez-image.h"

#include "Fractale.h"
#include <stdio.h>
#include "listep.h"
#include "listep_op.h"
#include "draw.h"
#include "menu.h"
#include "pthread.h"
#define LARGEUR 1000
#define HAUTEUR 700
#define HMENU 200
#define MENU LARGEUR*12/100
#define OFF 0
#define ON 1



typedef struct {

	PLISTE liste, listecourante;
	Ez_image *buttoncenter, *buttonrun, *selection, *reset, *save, *saveactive, *resetactive, *fondmenu, *checkboxdisable, *checkboxenable;
	int count, delay, select, tailleKoch, nivKoch, menux, menuy, start_anim, incrementniv, incrementangle, couleur, anim, rempli,zoom, focus, show_menu,
	step_menu, button_checked, enable_draw_mendel, enable_draw_julia, iter_max, type_julia, indice_buffer;
	Ez_pixmap *pixmap;
	Ez_image *image;
	Menu *men;
	
	int mx,my,calcul, anim_calcul;
	
	pthread_t thread_zoom;
	pthread_mutex_t *mutex;	

	double  cplx_x1, cplx_x2, cplx_y1, cplx_y2;
	Ez_window win;
	char buffer[3];

}Data;

void remplir_buffer(Ez_window win, int val);
void vider_buffer(Ez_window win);
void init(Data *d);
void win1_event (Ez_event *ev);
void win1_on_Expose(Ez_event *ev);
void win1_on_KeyPress(Ez_event *ev);
void reset(Ez_window win);
void win1_on_button_release(Ez_event *ev);
void win1_on_button_press(Ez_event *ev);

#endif 
