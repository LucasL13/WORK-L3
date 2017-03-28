#include "bresenham.h"



void tracer_seg_bresenham(int x0, int y0, int x1, int y1, int pixmap[][LARGEUR]){

	if(x1 - x0 < 0) { // on trace dans le même sens 
		int tmp = x1;
		x1 = x0;
		x0 = tmp;
		tmp = y1;
		y1 = y0;
		y0 = tmp;
	}

	int dx = x1 - x0, dy = y1 - y0, x,y = y0,dp;
	double m = (double) dy/ (double) dx;
		

	if(m <= 0 && m >= -1){
		
		for(x = x0 ; x<=x1 ; x++){ 
			//printf("toto \n");
			
			dp = 2*dy*( (x+1)-x0)-dx*(2*y +1 -2*y0);
			if(dp <= 0){
				//dp = dp + 2*dy; // on bouge pas y ?, on choisit E
				if(y != 0) y --;
			}
			else {
				//dp = dp + 2*(dy-dx);
				//y --;// on choisit NE ?
			}
		if(x < LARGEUR && x > 0 && y > 0 && y < LARGEUR) pixmap[x][y] = 1;
		}
	}

	// pente dans le 3 eme octant

	if(m > 0 && m <= 1){
		
		for(x = x0 ; x<=x1 ; x++){
			
			//printf("toto \n");
			dp = 2*dy*( (x+1)-x0)-dx*(2*y +1 -2*y0);
			if(dp <= 0){
				//dp = dp + 2*dy; // on bouge pas y ?, on choisit E
				
			}
			else {
				//dp = dp + 2*(dy-dx);
				if(y != LARGEUR) y ++;
				//y --;// on choisit NE ?
			}
		if(x < LARGEUR && x > 0 && y > 0 && y < LARGEUR) pixmap[x][y] = 1;
		}
	}

	// pente dans le 4 eme octant

	if(m > 1){
		x = x0;
		for(y = y0 ; y<=y1 ; y++){
			
			//printf("toto \n");
			dp = 2*dy*( (x+1)-x0)-dx*(2*y +1 -2*y0);
			if(dp <= 0){
				//dp = dp + 2*dy; // on bouge pas y ?, on choisit E
				if(x != LARGEUR) x++;
			}
			else {
				//dp = dp + 2*(dy-dx);
				

				//y --;// on choisit NE ?
			}
		if(x < LARGEUR && x > 0 && y > 0 && y < LARGEUR) pixmap[x][y] = 1;
		}
	}
	
	// pente dans le 1er octant

	if(m < -1){
		x = x0;
		for(y = y0 ; y>=y1 ; y--){
			
			//printf("y =  %d\n",y);
			dp = 2*dy*( (x+1)-x0)-dx*(2*y +1 -2*y0);
			if(dp <= 0){
				//dp = dp + 2*dy; // on bouge pas y ?, on choisit E
				
			}
			else {
				//dp = dp + 2*(dy-dx);
				if(x != LARGEUR) x ++;

				//y --;// on choisit NE ?
			}
		if(x < LARGEUR && x > 0 && y > 0 && y < LARGEUR) pixmap[x][y] = 1;
		}
	}


}

