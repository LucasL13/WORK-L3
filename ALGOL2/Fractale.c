#include "Fractale.h"
#include "koch.h"  
#include "math.h"    
#include "save_ppm.h"
#include "menu.h"
#include "mandelbrot.h"
    
int pixmap[LARGEUR][LARGEUR];    
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main ()    
{    
    if (ez_init() < 0) exit(1); 
    
    Data *data = malloc(sizeof(Data)); 
    data -> mutex = &mutex;
       
    
    Ez_window win = ez_window_create (LARGEUR, HAUTEUR, "Fractale", win1_event); 
    data -> win = win;
    init(data);    
    ez_set_data(win,data);
    
    ez_window_dbuf(win, 1); // double buff pour les images
    
    ez_start_timer (win, data -> delay); // début du timer (pour rentre au moins une fois dans TimerNotify)
      
    ez_main_loop();  
    exit(0);  
} 
 
void init(Data *d){

	
	d -> liste = NULL; 
	d -> zoom = 0;
	d -> rempli = 0;   
	d -> delay = 100;    
	d -> tailleKoch = 9;
	d -> nivKoch = 2; 
	d -> select = 0;
	ecrire_liste("test.out",d->liste);  
	d -> count = 0;	 
	d -> start_anim = 1; 
	d -> incrementniv = 0;
	d -> incrementangle = 10;
	d -> button_checked = 4;
	d -> liste = koch_center(d->nivKoch,d->tailleKoch*50,d->button_checked);
	
	d -> couleur = 255; 
	d -> anim = 1;
	
	/* les images */
	
	
	d -> buttoncenter = ez_image_load("images/buttoncenter.png");
	d -> buttonrun = ez_image_load("images/buttonrun.png");
	
	d -> selection = ez_image_load("images/selection.png");

	d -> reset = ez_image_load("images/buttonreset.png");
	d -> save = ez_image_load("images/buttonsave.png");

	d -> saveactive = ez_image_load("images/buttonsaveactive.png");
	d -> resetactive = ez_image_load("images/buttonresetactive.png");
	d -> fondmenu = ez_image_load("images/fondmenu.png");
	d -> checkboxenable = ez_image_load("images/checkboxenable.png");
	d -> checkboxdisable = ez_image_load("images/checkbox.png");
	d -> focus = 0;
	d -> show_menu = 0;
	d -> step_menu = 0;
	d -> start_anim = 0;
	d -> men = create_menu();
	
	d -> men -> largeur = 200;
	d -> men -> hauteur = 220;
	d -> men -> x = LARGEUR/2 - (d -> men -> largeur) /2;
	d -> men -> y = HAUTEUR/2 - (d -> men -> hauteur) /2;

	d -> image = NULL;
	
	d -> men -> cl -> rb = add_button(d -> men -> cl -> rb, "Koch");
	d -> men -> cl -> rb = add_button(d -> men -> cl -> rb, "Koch inverse");
	d -> men -> cl -> rb = add_button(d -> men -> cl -> rb, "Cesaro");
	d -> men -> cl -> rb = add_button(d -> men -> cl -> rb, "Mandelbrot");
	d -> men -> cl -> rb = add_button(d -> men -> cl -> rb, "Julia");
	d -> pixmap = NULL; 
	
	d -> men -> cl -> elem = 5; /* a modifier pour que ce soit plus simple peut être. */

	enable_button(d -> men -> cl -> rb,4,d -> men -> cl -> elem); /* par défaut on active koch */
	
	d -> enable_draw_mendel = 0;
	d -> enable_draw_julia = 0;
	d -> type_julia = 1;
	d -> iter_max = MAX_ITER;
	
	/* definition des bornes de mandelbrot de base */

	d -> cplx_x1 = -2.4;
	d -> cplx_x2 = 2.4;
	d -> cplx_y1 = -1.5;
	d -> cplx_y2 = 1.5;
	d -> anim_calcul = 0;
	for(int i=0 ; i<3 ; i++)
		d -> buffer[i] = 0;
	init_pixmap(pixmap);
	
	 
}


void win1_on_timer_notify (Ez_event *ev)                 /* The timer has expired */
{
	Data *d = ez_get_data(ev -> win);
    
	ez_send_expose (ev->win);     
      
    	if(d->start_anim){
		ez_start_timer (ev->win, d->delay); // on execute ce qu'il y a dans case Expose tout les delay ms 
	}
    
	else if(d->show_menu && d->step_menu < 20){
		ez_start_timer(ev->win, 25);	
	}
	else if(d -> calcul == ON){
		d -> anim_calcul = (d->anim_calcul+1)%4;
		ez_start_timer(ev->win,150);
	}
    
	d -> focus = 0;	 
     
}
  
 

void win1_on_Expose(Ez_event *ev){         
	   
	Data *d = ez_get_data(ev->win); 
	int x = LARGEUR/2 - (d->tailleKoch*50)/2 ,y = (HAUTEUR-HMENU)/2 + (sqrt(3.0)/2.0*((d->tailleKoch*50)/2.0))/1.4;
	
        ez_set_thick(1); 
        
	if(d->button_checked == 4 || d->button_checked == 3){ 	/* on est sur koch ou son inverse */
		
		

     	   if(!d->start_anim){  
		
		
			ez_set_color(ez_black);
			draw_polygon(ev->win,d -> liste);
			if(d->rempli) remplir_flocon(ev->win);
			if(d->show_menu){
				draw_menu(ev->win,d->men,d->step_menu); 
			
				if(d->step_menu != 20) d -> step_menu++;
				if(d->step_menu == 20){
					draw_checklist(ev->win,d->men->cl,d->men->x,d->men->y);
				}
			}
		
			
		
		 
		}
	 
        	else if (d->anim == 1) {
			d->delay = 50; 
        		d->incrementniv = (d->incrementniv + 1) % (d->nivKoch+1); 
        		d->incrementangle = (d->incrementangle + 2);
        	
        		if(d->incrementangle == 60) {
				d->start_anim = 0;
			}
		
        	
        		if(d->button_checked == 4) d -> liste = koch_a(d->nivKoch,x,y,d->tailleKoch*50,d->incrementangle);
			else if(d->button_checked == 3) d -> liste = koch_a(d->nivKoch,x,y,d->tailleKoch*50,-1*(d->incrementangle));
        		d -> couleur -= 8;   
        		ez_set_color(ez_get_RGB(d->couleur,0,0)); 
        		
			draw_polygon(ev->win,d -> liste);  
			ez_start_timer (ev->win, d->delay);
        	} 
		else if (d->anim == 2) {
			d->delay = 250;	
			anim_koch(ev->win,(d -> count)++);
			if(d->count == d->nivKoch+1) d-> count = 0;
			ez_start_timer (ev->win, d->delay);	
		}
		else if (d->anim == 3) {
			d->delay = 250;	
			anim_koch(ev->win,(d -> count)++);
			if(d->count == d->nivKoch+1){ d-> count = 0;d->start_anim=0;}
			ez_start_timer (ev->win, d->delay);	
		}
		else if (d->anim == 4) {	
			d->delay = 250;
	
			for(int i=0 ; i<d->count ; i++){	
				anim_koch(ev->win,i);
			}
			
			if(!(d->count == d->nivKoch)){(d->count)++;}
			ez_start_timer (ev->win, d->delay);
		}

		else if (d->anim == 5) {
			d->delay = 250;
			for(int i=0 ; i<d->count ; i++){	
				anim_koch(ev->win,i);
			}
			
			if(d->count == d->nivKoch){d -> count = 0;}
			else {(d->count)++;}
			ez_start_timer (ev->win, d->delay);
		} 
	
	
		
        	draw_buttons(ev -> win, 0,HAUTEUR - MENU); 
	
		}
	 
        else if(d->button_checked == 2){ /* on est sur cesaro */
		if(d->show_menu){
			draw_menu(ev->win,d->men,d->step_menu);
			
			if(d->step_menu != 20) d -> step_menu++;
			if(d->step_menu == 20){
				draw_checklist(ev->win,d->men->cl,d->men->x,d->men->y);
			}
			
		}
		draw_buttons(ev -> win, 0,HAUTEUR - MENU);
	}
 	
	else if(d->button_checked == 1){ /* on est sur mendelbroot */
	
		if(d -> enable_draw_mendel){
			d -> image = draw_img_mandelbrot(ev->win);
			d -> pixmap = ez_pixmap_create_from_image(d -> image);
			
			
			d -> enable_draw_mendel = 0;
		}
		ez_pixmap_paint(ev->win,d->pixmap,0,0);
		if(d->show_menu){
			draw_menu(ev->win,d->men,d->step_menu);
			
			if(d->step_menu != 20) d -> step_menu++;
			if(d->step_menu == 20){
				draw_checklist(ev->win,d->men->cl,d->men->x,d->men->y);
			}
		}

		
	}

	else if(d->button_checked == 0){ /* on est sur julia */

	
		if(d -> enable_draw_julia) { /* théoriquement on dessine une et une seule fois la fractale ici */

			ez_image_destroy(d -> image);
			ez_pixmap_destroy(d -> pixmap);
			d -> image = draw_img_julia(ev->win,d->iter_max,d->type_julia);
			d -> pixmap = ez_pixmap_create_from_image(d -> image);
			
			
			d -> enable_draw_julia = 0;
		}
		
		
		
		ez_pixmap_paint(ev->win,d->pixmap,0,0);

		pthread_mutex_lock(d -> mutex);
		if(d -> calcul == ON){
			ez_set_color(ez_get_RGB(255,102,0));
			draw_anim_calcul(ev -> win);
		}
		pthread_mutex_unlock(d -> mutex);		

		if(d->show_menu){
			draw_menu(ev->win,d->men,d->step_menu); 
			
			if(d->step_menu != 20) d -> step_menu++;
			if(d->step_menu == 20){
				draw_checklist(ev->win,d->men->cl,d->men->x,d->men->y);
			}
		}
		draw_buttons_julia(ev->win,0,HAUTEUR-MENU);

	}		
}
 
void win1_on_KeyPress(Ez_event *ev){    
	Data *d = ez_get_data(ev->win);
	d -> start_anim = 0;  
	d -> count = 0;  
	switch(ev->key_sym){
	 	
		case XK_q : ez_quit(); break;
		case XK_1 : 
				if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 1; 
					if(d->select == 2) d->nivKoch = 1;
					if(d->select == 3) d->anim = 1;
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,1); vider_buffer(ev->win);}
					if(d -> select == 2) d -> type_julia = 1;
				}
				break;

	 	case XK_2 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 2; 
					if(d->select == 2) d->nivKoch = 2;
					if(d->select == 3) d->anim = 2;
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,2); vider_buffer(ev->win);}
					if(d -> select == 2) d -> type_julia = 2;
				}
				break;

	 	case XK_3 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 3; 
					if(d->select == 2) d->nivKoch = 3;
					if(d->select == 3) d->anim = 3;
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,3); vider_buffer(ev->win);}
					if(d -> select == 2) d -> type_julia = 3;
				}
				break;

	 	case XK_4 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 4; 
					if(d->select == 2) d->nivKoch = 4;
					if(d->select == 3) d->anim = 4;
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,4); vider_buffer(ev->win);}
					if(d -> select == 2) d -> type_julia = 4;
				}
				break;

	 	case XK_5 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 5; 
					if(d->select == 2) d->nivKoch = 5;
					if(d->select == 3) d->anim = 5;
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,5); vider_buffer(ev->win);}
					if(d -> select == 2) d -> type_julia = 5;
				}
				break;

	 	case XK_6 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 6; 
					if(d->select == 2) d->nivKoch = 6;
					
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,6); vider_buffer(ev->win);}
					if(d -> select == 2) d -> type_julia = 6;
				}
				break;

	 	case XK_7 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 7; 
					if(d->select == 2) d->nivKoch = 7;
					
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,7); vider_buffer(ev->win);}
					
				}
				break;

	 	case XK_8 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 8; 
					if(d->select == 2) d->nivKoch = 8;
					
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,8); vider_buffer(ev->win);}
					
				}
				break;

	 	case XK_9 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					if(d->select == 1) d->tailleKoch = 9; 
					if(d->select == 2) d->nivKoch = 9;
					
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,9); vider_buffer(ev->win);}
					
				}
				break;

	 	case XK_0 : if(!d->show_menu && (d -> button_checked == 5 || d -> button_checked == 4)){
					 
					if(d->select == 2) d->nivKoch = 0;
					
				}

				if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
					if(d->select == 1) {remplir_buffer(ev->win,0); vider_buffer(ev->win);}
					
				}
				break;

		case XK_r : if(!d->show_menu){if(!(d->zoom)) d->rempli = !(d->rempli);ez_send_expose(ev->win);}break;
		case XK_Return : if(d->show_menu){ d->show_menu = 0;valider_choix(ev->win,d->men->cl->elem);d -> liste = koch_center(d->nivKoch,d->tailleKoch*50,d->button_checked);}break;
		case XK_m : d->show_menu = !(d->show_menu); if(d->step_menu > 0) d->step_menu = 0;ez_start_timer (ev->win, d->delay); break;
		case XK_BackSpace :
			if(!d->show_menu && (d -> button_checked == 0 || d -> button_checked == 1 )){
				for(int i=0 ; i<3 ; i++){
					d->buffer[i] = 0;
				}
				d -> indice_buffer = 0;
				vider_buffer(ev->win);
			}
			break;
	 	
	 	
	 	  
	
	}   
}  	 

void remplir_buffer(Ez_window win,int val){
	
	Data *d = ez_get_data(win);
	
	if(d->indice_buffer == 0) d -> buffer[d -> indice_buffer] = val;
	else if(d -> indice_buffer == 1) {
		d->buffer[1] = d->buffer[0];
		d->buffer[0] = val;
		d->buffer[2] = 0;
	}
	else if(d -> indice_buffer == 2) {
		d->buffer[2] = d->buffer[1];
		d->buffer[1] = d->buffer[0];
		d->buffer[0] = val;
	}

	d -> indice_buffer = (d -> indice_buffer + 1) % 3;

}

void vider_buffer(Ez_window win){
	Data *d = ez_get_data(win);
	d -> iter_max = d -> buffer[0] + d->buffer[1]*10 + d->buffer[2]*100;
}

void win1_on_button_press(Ez_event *ev){  
	Data *d = ez_get_data(ev->win);  
    
	if(ev->mb == 1 && !d->show_menu && (d->button_checked == 3 || d->button_checked == 4)){
		 
		if(ev->mx >= (320) && ev->mx <= (370) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){
			d -> select = 1; // focus on "taille"
			ez_send_expose(ev->win);
		}
		else if(ev->mx >= (320) && ev->mx <= (370) && ev->my >= (HAUTEUR-MENU+45) && ev->my <= (HAUTEUR-MENU+95)){
		 	d -> select = 2; // focus on "niveau"
			ez_send_expose(ev->win);
		}
		else if(ev->mx >= (180) && ev->mx <= (230) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){
			d -> select = 3; // focus on "type anim"
			ez_send_expose(ev->win);
		}
		else if(ev->mx >= (180) && ev->mx <= (230) && ev->my >= (HAUTEUR-MENU+45) && ev->my <= (HAUTEUR-MENU+95)){
			d -> start_anim = 1;
			d-> incrementangle = 0;
			d->couleur = 255; 
			d -> liste = koch_center(d->nivKoch,d->tailleKoch*50,d->button_checked);
			save_koch(d->nivKoch,d->tailleKoch*50,d->button_checked);
			d -> count = 0; 
			d -> zoom = 0;     
			ez_send_expose(ev->win);
				
		}
		else if(ev->mx >= (380) && ev->mx <= (480) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){ // reset button
			reset(ev->win);
			d -> focus = 1;	
			ez_start_timer (ev->win, 150);
			ez_send_expose(ev->win);
		}
		
		else if(ev->mx >= (380) && ev->mx <= (480) && ev->my >= (HAUTEUR-MENU+45) && ev->my <= (HAUTEUR-MENU+95)){ // save button
			d -> focus = 2;
			init_pixmap(pixmap);			
			draw_and_save(d->liste,pixmap);
			ez_start_timer (ev->win, 150);
			ez_send_expose(ev->win);
		}
		
		else if(ev->mx >= 0 && ev->mx <= LARGEUR && ev->my >= 0 && ev->my <= HAUTEUR){
			d -> liste = zoom_koch(d->liste,1.25,ev -> mx,ev -> my);
			d -> zoom = 1;
			d -> rempli = 0;
			ez_send_expose(ev->win);
		}
		else {d->select = 0;ez_send_expose(ev->win);} 
	}

	if(ev->mb == 1 && d->show_menu){ /* choix sur le menu */
		for(int i=0 ; i<(d -> men -> cl -> elem) ; i++){

			if(ev->mx >= d->men->x+20 && ev ->mx <= d->men->x+20+TAILLEBOX 
			&& ev->my >= d->men->y+20 + i*(TAILLEBOX+15) 
			&& ev->my <= d->men->y+20+TAILLEBOX+i*(TAILLEBOX+15))
			{
 
				
				enable_button(d -> men -> cl -> rb,i,d -> men -> cl -> elem);
				if(i == 0) d->enable_draw_julia = 1;
				if(i == 1) d->enable_draw_mendel = 1;
				break;

			}
		}
		ez_send_expose(ev->win);
		
	}

	if(ev->mb == 4 && !d->show_menu && (d->button_checked == 3 || d->button_checked == 4)){
		if(ev->mx >= 0 && ev->mx <= LARGEUR && ev->my >= 0 && ev->my <= HAUTEUR){
			d -> liste = zoom_koch(d->liste,1.25,ev -> mx,ev -> my);
			d -> zoom = 1;
			d -> rempli = 0;
		}
		ez_send_expose(ev->win);
	}
	/*   dézoom impossible avec la méthode optimisé */
	
	
	if(ev->mb == 1 && !d->show_menu && d->button_checked == 0){ /* dans la fenetre de julia */
		 
		if(ev->mx >= (120) && ev->mx <= (170) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){
			d -> select = 1; // focus on "iterations"
			ez_send_expose(ev->win);
		}
		else if(ev->mx >= (120) && ev->mx <= (170) && ev->my >= (HAUTEUR-MENU+45) && ev->my <= (HAUTEUR-MENU+95)){
		 	d -> select = 2; // focus on "type"
			ez_send_expose(ev->win);
		}
		else if(ev->mx >= (180) && ev->mx <= (280) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){ // reset button
			
			d -> focus = 1;	
			ez_start_timer (ev->win, 150);
			d -> cplx_x1 = -2.4;
			d -> cplx_x2 = 2.4;
			d -> cplx_y1 = -1.5;
			d -> cplx_y2 = 1.5;
			ez_image_destroy(d -> image);
			ez_pixmap_destroy(d -> pixmap);
			d -> image = draw_img_julia(ev->win,d->iter_max,d->type_julia); 
			d -> pixmap = ez_pixmap_create_from_image(d -> image);
			ez_send_expose(ev->win);
		}
		
		else if(ev->mx >= (180) && ev->mx <= (280) && ev->my >= (HAUTEUR-MENU+45) && ev->my <= (HAUTEUR-MENU+95)){ // save button
			d -> focus = 2;
						
			save_ppm_from_pixmap(d->image,"save/julia.ppm"); /* on lance la sauvegarde de la fractale */
			ez_start_timer (ev->win, 150);
			ez_send_expose(ev->win);
		}
		else if(ev->mx >= 0 && ev->mx <= LARGEUR && ev->my >= 0 && ev->my <= HAUTEUR){
			//ez_pixmap_destroy(d -> pixmap);
			ez_image_destroy(d -> image);
			
			d -> calcul = ON;

			d -> mx = ev -> mx;
			d -> my = ev -> my;

			pthread_create(&(d->thread_zoom),NULL,thread_zoom_julia,d);
				
				

			//d -> image = zoom_julia(ev->win,.50, ev->mx, ev->my);
			//d -> pixmap = ez_pixmap_create_from_image(d -> image);

			
			
			ez_start_timer(ev->win,150);
		}
	}

	if(ev->mb == 1 && !d->show_menu && d->button_checked == 1){ /* dans la fenetre de mandelbrot */
		 
		if(ev->mx >= (120) && ev->mx <= (170) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){
			d -> select = 1; // focus on "iterations"
			ez_send_expose(ev->win);
		}
		
		else if(ev->mx >= (180) && ev->mx <= (280) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){ // reset button
			
			d -> focus = 1;	
			ez_start_timer (ev->win, 150);
			d -> cplx_x1 = -2.4;
			d -> cplx_x2 = 2.4;
			d -> cplx_y1 = -1.5;
			d -> cplx_y2 = 1.5;
			ez_image_destroy(d -> image);
			ez_pixmap_destroy(d -> pixmap);
			d -> image = draw_img_julia(ev->win,d->iter_max,d->type_julia); 
			d -> pixmap = ez_pixmap_create_from_image(d -> image);
			ez_send_expose(ev->win);
		}
		
		else if(ev->mx >= (180) && ev->mx <= (280) && ev->my >= (HAUTEUR-MENU+45) && ev->my <= (HAUTEUR-MENU+95)){ // save button
			d -> focus = 2;
						
			save_ppm_from_pixmap(d->image,"save/mandelbrot.ppm"); /* on lance la sauvegarde de la fractale */
			ez_start_timer (ev->win, 150);
			ez_send_expose(ev->win);
		}
		else if(ev->mx >= 0 && ev->mx <= LARGEUR && ev->my >= 0 && ev->my <= HAUTEUR){
			ez_pixmap_destroy(d -> pixmap);
			ez_image_destroy(d -> image);
			d -> image = zoom_mandelbrot(ev->win,.50, ev->mx, ev->my);
			d -> pixmap = ez_pixmap_create_from_image(d -> image);
			ez_send_expose(ev->win);
		}
	}
	
} 

void win1_on_button_release(Ez_event *ev){
	Data *d = ez_get_data(ev -> win); 
	if(ev->mb == 1){
		if(ev->mx >= (380) && ev->mx <= (480) && ev->my >= (HAUTEUR-MENU-15) && ev->my <= (HAUTEUR-MENU+35)){ // reset button
			d -> focus = 0;	
		}
		
		else if(ev->mx >= (380) && ev->mx <= (480) && ev->my >= (HAUTEUR-MENU+45) && ev->my <= (HAUTEUR-MENU+95)){ // save button
			d -> focus = 0;
		}
	}
}

void win1_event (Ez_event *ev)                   
{   
				                                       
    switch (ev->type) {

	case TimerNotify:
		win1_on_timer_notify(ev);
		break;
		
	case Expose:
		win1_on_Expose(ev);
		break;

        case KeyPress :                                
            	ez_send_expose (ev->win);
        	win1_on_KeyPress(ev);
        	break;
            
        case ButtonPress :
        	win1_on_button_press(ev);
        	break;

	case ButtonRelease :
        	win1_on_button_release(ev);
        	break;
        	
        
    }
}

void reset(Ez_window win){

	Data *d = ez_get_data(win);
	d -> zoom = 0;
	d -> count = 0;
	int i = d -> nivKoch;
	char nf[12];
	
	sprintf(nf,"koch/k%d.in",i);
	FILE* file = fopen(nf,"r");
	
	if(!file){
		fclose(file);
		d->liste = koch_center(d->nivKoch,d->tailleKoch*50,d->button_checked); 
	}
	else {
		fclose(file);
		d -> liste = lire_liste(nf);
	}
}






