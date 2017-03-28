#include "koch.h"
#include "Fractale.h"
#include "draw.h"



PLISTE triangle(double x, double y, double c){
	
	PLISTE list = init_liste(x,y), point;
	point = insert_after(list,x+c,y);

	insert_after(point, x + (1/2.0)*c, y - (sqrt(3.0)/2.0)*c);	

	return list;

}


PLISTE koch(int n, double x, double y, double c){

	double i, x1, y1, xp,yp, cotex,cotey;
	double alpha = PI * (60) / 180;

	PLISTE list = triangle(x,y,c), tmp = list, maillon;
	PLISTE p1,p2;

	for(i = 0 ; i<n ; i++){
		
		while (tmp -> next != NULL){

			p1 = tmp;
			p2 = tmp -> next;
			cotex = p2->x - p1->x;
			cotey = p2->y - p1->y;

			

			maillon = insert_after(tmp,p1 -> x + (cotex/3.0),p1 -> y + (cotey/3.0));

			insert_after(maillon,p1->x + (cotex/3.0)*2,p1 -> y + (cotey/3.0)*2);

			x1 = maillon -> next -> x - maillon -> x;			
			y1 = maillon -> next -> y - maillon -> y;

			xp = x1*cos(alpha) - y1*sin(alpha);
			yp = x1*sin(alpha) + y1*cos(alpha);

			insert_after(maillon,maillon -> x +xp, maillon -> y + yp);
			
			tmp = p2;

		}
		
		cotex = list->x - p2->x;
		cotey = list->y - p2->y;
		

		maillon = insert_after(p2,p2 -> x + (cotex/3.0),p2 -> y + (cotey/3.0));

		insert_after(maillon,p2->x + (cotex/3.0)*2,p2 -> y + (cotey/3.0)*2);

		x1 = maillon -> next -> x - maillon -> x;			
		y1 = maillon -> next -> y - maillon -> y;

		xp = x1*cos(alpha) - y1*sin(alpha);
		yp = x1*sin(alpha) + y1*cos(alpha);

		insert_after(maillon,maillon -> x +xp, maillon -> y + yp);

		
		tmp = list;		

	}

	return list;

}

PLISTE koch_inverse(int n, double x, double y, double c){

	double i, x1, y1, xp,yp, cotex,cotey;
	double alpha = PI * (-60) / 180;

	PLISTE list = triangle(x,y,c), tmp = list, maillon;
	PLISTE p1,p2;

	for(i = 0 ; i<n ; i++){
		
		while (tmp -> next != NULL){

			p1 = tmp;
			p2 = tmp -> next;
			cotex = p2->x - p1->x;
			cotey = p2->y - p1->y;

			

			maillon = insert_after(tmp,p1 -> x + (cotex/3.0),p1 -> y + (cotey/3.0));

			insert_after(maillon,p1->x + (cotex/3.0)*2,p1 -> y + (cotey/3.0)*2);

			x1 = maillon -> next -> x - maillon -> x;			
			y1 = maillon -> next -> y - maillon -> y;

			xp = x1*cos(alpha) - y1*sin(alpha);
			yp = x1*sin(alpha) + y1*cos(alpha);

			insert_after(maillon,maillon -> x +xp, maillon -> y + yp);
			
			tmp = p2;

		}
		
		cotex = list->x - p2->x;
		cotey = list->y - p2->y;
		

		maillon = insert_after(p2,p2 -> x + (cotex/3.0),p2 -> y + (cotey/3.0));

		insert_after(maillon,p2->x + (cotex/3.0)*2,p2 -> y + (cotey/3.0)*2);

		x1 = maillon -> next -> x - maillon -> x;			
		y1 = maillon -> next -> y - maillon -> y;

		xp = x1*cos(alpha) - y1*sin(alpha);
		yp = x1*sin(alpha) + y1*cos(alpha);

		insert_after(maillon,maillon -> x +xp, maillon -> y + yp);

		
		tmp = list;		

	}

	return list;

}


PLISTE koch_a(int n, double x, double y, double c, int angle){

	double i, x1, y1, xp,yp, cotex,cotey;
	double alpha = PI * angle / 180;

	PLISTE list = triangle(x,y,c), tmp = list, maillon;
	PLISTE p1,p2;

	for(i = 0 ; i<n ; i++){
		
		while (tmp -> next != NULL){

			p1 = tmp;
			p2 = tmp -> next;
			cotex = p2->x - p1->x;
			cotey = p2->y - p1->y;

			

			maillon = insert_after(tmp,p1 -> x + (cotex/3.0),p1 -> y + (cotey/3.0));

			insert_after(maillon,p1->x + (cotex/3.0)*2,p1 -> y + (cotey/3.0)*2);

			x1 = maillon -> next -> x - maillon -> x;			
			y1 = maillon -> next -> y - maillon -> y;

			xp = x1*cos(alpha) - y1*sin(alpha);
			yp = x1*sin(alpha) + y1*cos(alpha);

			insert_after(maillon,maillon -> x +xp, maillon -> y + yp);
			
			tmp = p2;

		}
		
		cotex = list->x - p2->x;
		cotey = list->y - p2->y;
		

		maillon = insert_after(p2,p2 -> x + (cotex/3.0),p2 -> y + (cotey/3.0));

		insert_after(maillon,p2->x + (cotex/3.0)*2,p2 -> y + (cotey/3.0)*2);

		x1 = maillon -> next -> x - maillon -> x;			
		y1 = maillon -> next -> y - maillon -> y;

		xp = x1*cos(alpha) - y1*sin(alpha);
		yp = x1*sin(alpha) + y1*cos(alpha);

		insert_after(maillon,maillon -> x +xp, maillon -> y + yp);

		
		tmp = list;		

	}

	return list; 

}

PLISTE koch_center(int n, double c, int choix){
	
	int x = LARGEUR/2 - c/2 ,y = (HAUTEUR-HMENU)/2 + (sqrt(3.0)/2.0*(c/2.0))/1.4;	

	if(choix == 4) return koch(n,x,y,c);
	if(choix == 3) return koch_inverse(n,x,y,c);

}


PLISTE zoom_koch(PLISTE list, double i, int x, int y){
	
	PLISTE tmp = list;
	double centerx = x, centery = y, vectorx, vectory;
	if(i == 1){
		return list;
	}
	
	while(tmp != NULL){
		
		if(tmp -> x < 2*LARGEUR && tmp -> x > -LARGEUR && tmp -> y > -HAUTEUR && tmp -> y < 2*HAUTEUR){
			vectorx = tmp -> x - centerx;
			vectory = tmp -> y - centery;
		
		
		
			vectorx = vectorx * i;
			vectory = vectory * i;
		
			
		
			tmp -> x = centerx + vectorx;
			tmp -> y = centery + vectory;		
		}
		
		tmp = tmp -> next;
	
	}
	
	return list;

}


