#include <stdio.h>
#include <stdlib.h>


void tracer_seg_bresenham(int x0, int y0, int x1, int y1, int pixmap[][500]){

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
	printf("m = %.2lf \n",m);	

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
		pixmap[x][y] = 1;
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
				if(y != 499) y ++;
				//y --;// on choisit NE ?
			}
		pixmap[x][y] = 1;
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
				if(x != 499) x ++;
			}
			else {
				//dp = dp + 2*(dy-dx);
				

				//y --;// on choisit NE ?
			}
		pixmap[x][y] = 1;
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
				if(x != 499) x ++;

				//y --;// on choisit NE ?
			}
		pixmap[x][y] = 1;
		}
	}


}

void save_ppm(char* name, int pixmap[][500], int largeur, int hauteur){

	FILE* file = fopen(name,"w");
	fprintf(file,"P3\n");
	fprintf(file,"%d %d\n",largeur,hauteur);
	fprintf(file,"255\n");
	
	for(int i = 0 ; i<largeur ; i++){
		for(int j = 0 ; j<largeur ; j++){
			if(pixmap[j][i]){
				fprintf(file,"0 0 0 ");
			}
			else fprintf(file,"255 255 255 ");
		}
	}

	fclose(file);

}

int main(){

	int pixmap[500][500];

	for(int i=0 ; i<500 ; i++){
		for(int j=0 ; j<500 ; j++)
			pixmap[i][j] = 0;
	}

	tracer_seg_bresenham(0, 300, 40, 500,pixmap);

	/*	
	for(int i=0 ; i<25 ; i++){
		for(int j=0 ; j<25 ; j++)
			printf("%d ",pixmap[i][j]);
	printf("\n");
	}
	*/
	save_ppm("test.ppm",pixmap,500,500);
	
	return 0;
}
