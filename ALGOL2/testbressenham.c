#include <stdio.h>
#include <stdlib.h>




void tracer_segment_bressenham(int x1, int y1, int x2, int y2, int pixmap[][25]){

	int dx = x2 - x1, dy = y2 - y1, dp = 2*dy - dx,i;
	double m = dy/dx;
	x2 = x1 + dx;
	int y = y1;
	
	if(m <= 1){
		for(i=x1 ; i<=x2 ; i++){
			if(dp <= 0) dp = dp + 2*dy;
			else{
				dp = dp + 2*(dy-dx);
				y = y-1;
			}
		y += m;
		pixmap[i][(int) y] = 1;
	}
	}
}


int main(){

	int pixmap[25][25];
	
	for(int i=0 ; i<50 ; i++)
		for(int j=0 ; j<50 ; j++)
			pixmap[i][j] = 0;
	
	tracer_segment_bressenham(0, 25, 25, 20,pixmap);	
	
	for(int i=0 ; i<25; i++){
		for(int j=0 ; j<25 ; j++)
			printf("%d ",pixmap[i][j]);
		printf("\n");	
	}
	
	return 0;
}
