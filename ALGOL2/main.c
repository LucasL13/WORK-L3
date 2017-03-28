#include "ez-draw.h"
#include "main.h"

#define LARGEUR 800
#define HAUTEUR 600
#define INCR 3

int x = 100,y = 100;
int stop = 0, back_x = 0, back_y = 0, trace = 0;

int main ()
{
    if (ez_init() < 0) exit(1);

    Ez_window win = ez_window_create (LARGEUR, HAUTEUR, "la balle qui rebondis partout partout", win1_event);
    ez_window_dbuf(win, 1);
    ez_start_timer (win, 1);
    ez_main_loop();
    exit(0);
}

void win1_on_timer_notify (Ez_event *ev)            /* The timer has expired */
{
    
    
    ez_send_expose (ev->win);
    
    ez_start_timer (ev->win, 5);
}

void win1_on_Expose(Ez_event *ev){

	ez_set_color (ez_white);
	if(!trace) ez_fill_rectangle(ev->win,0,0,LARGEUR,HAUTEUR);
	ez_set_color (ez_red);
        
        if(!stop){
        
        	if(x >= LARGEUR-50) back_x = 1;
        	if(x <= 0) back_x = 0;
        	if(y >= HAUTEUR-50) back_y = 0;
        	if(y <= 0) back_y = 1;
        
        	if(back_x){
        		x = x - INCR;
        	}
        	else x = x + INCR;
        	
        	if(back_y){
        		y = y + INCR;
        	}
        	else y = y - INCR;
        }
        
        ez_fill_circle(ev->win, x, y, x+50, y+50);
        
        

}

void win1_on_KeyPress(Ez_event *ev){

	switch(ev->key_sym){
		
		case XK_space : stop = !stop;
		case XK_t : trace = !trace;
	}
}

void win1_event (Ez_event *ev)                   /* Called by ez_main_loop() */
{   
	
		
		                                          /* for each event on win1   */
    switch (ev->type) {

	case TimerNotify:
		win1_on_timer_notify(ev);
		break;
		
	case Expose:
		win1_on_Expose(ev);
		break;

        case KeyPress :                                 /* A key was pressed */
            
            win1_on_KeyPress(ev);
            
            break;
    }
}


