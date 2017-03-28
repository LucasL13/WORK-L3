#include "mandelbrot.h"


COMPLEXE* convertir_pixel(Ez_window win, int x, int y){
	
	Data *d = ez_get_data(win);
	COMPLEXE *cplx = malloc(sizeof(COMPLEXE));
	
	cplx -> re = ((x*((d -> cplx_x2) - (d -> cplx_x1)))/LARGEUR) + (d -> cplx_x1);
	
	cplx -> im = ((y*((d -> cplx_y2) - (d -> cplx_y1)))/HAUTEUR) + (d -> cplx_y1); 

	return cplx;
}


Ez_image* draw_img_mandelbrot(Ez_window win){
	COMPLEXE *cplx = NULL, *Z0 = NULL;
	Ez_image *img = ez_image_create(LARGEUR,HAUTEUR);
	int k = 0;
	

	for(int i=0 ; i<LARGEUR ; i++){
		for(int j=0 ; j<HAUTEUR ; j++){

			cplx = create_complexe(0,0);
			Z0 = convertir_pixel(win,i,j);
			k = 0;

			

			do{  /* calcul de mendelbrot */  
				
				cplx = mul_cplx(cplx,cplx);
				cplx = add_cplx(cplx,Z0);
				k++;
	
					

			}while(k < MAX_ITER && modcarre_cplx(cplx) <= 4);
			
			if(k == MAX_ITER){
				img -> pixels_rgba[(j*LARGEUR+i)*4] = 0;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 1] = 0;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 2] = 0;
			}
			else {
				img -> pixels_rgba[(j*LARGEUR+i)*4] = k*255/MAX_ITER;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 1] = 0;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 2] = 0;
			}
			
			
			
			if(i == 450 && j == 50) printf("re = %.3lf im = %.3lf\n",cplx -> re,cplx -> im);			

			free(cplx);
			free(Z0);
		}
	}
	return img;
}



Ez_image* draw_img_julia(Ez_window win, int iter_max, int n){

	COMPLEXE *cplx = NULL, *Z0 = NULL;
	Ez_image *img = ez_image_create(LARGEUR,HAUTEUR);
	
	int k = 0;
	if(n == 1) Z0 = create_complexe(0.285,0.013);
	if(n == 2) Z0 = create_complexe(0.285,0.01);
	if(n == 3) Z0 = create_complexe(0.3,0.5);
	if(n == 4) Z0 = create_complexe(0,1);
	if(n == 5) Z0 = create_complexe(0.28,-0.02);
	if(n == 5) Z0 = create_complexe(-0.75,0);
	if(n == 6) Z0 = create_complexe(-0.123,0.745);

	for(int i=0 ; i<LARGEUR ; i++){
		for(int j=0 ; j<HAUTEUR ; j++){

			cplx = convertir_pixel(win,i,j);
			
			k = 0;

			

			do{  /* calcul de mendelbrot */  
				
				cplx = mul_cplx(cplx,cplx);
				cplx = add_cplx(cplx,Z0);
				k++;
	
					

			}while(k < iter_max && modcarre_cplx(cplx) <= 4);
			
			if(k == iter_max){
				img -> pixels_rgba[(j*LARGEUR+i)*4] = 0;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 1] = 0;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 2] = 0;
			}
			else {
				img -> pixels_rgba[(j*LARGEUR+i)*4] = k*255/iter_max;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 1] = 0;
				img -> pixels_rgba[(j*LARGEUR+i)*4 + 2] = 0;
			}
			
			
			
						

			free(cplx);
			
		}
	}
	free(Z0);
	return img;
}

void *thread_zoom_julia(void* arg){

	Data *d = arg;
	
	d -> image = zoom_julia(d -> win,.50,d -> mx,d -> my);
	pthread_mutex_lock(d -> mutex);
	d -> calcul = OFF;
	pthread_mutex_unlock(d -> mutex);
	ez_pixmap_destroy(d->pixmap);
	d -> pixmap = ez_pixmap_create_from_image(d -> image);
	pthread_exit(NULL);

}

Ez_image* zoom_mandelbrot(Ez_window win, double zoom, int mx, int my){

		
	Data *d = ez_get_data(win);
	
	d -> cplx_x1 = (d -> cplx_x1) * zoom;
	d -> cplx_x2 = (d -> cplx_x2) * zoom;
	d -> cplx_y1 = (d -> cplx_y1) * zoom;
	d -> cplx_y2 = (d -> cplx_y2) * zoom;

	COMPLEXE *coord_clic = convertir_pixel(win, mx,my);

	d -> cplx_x1 = d -> cplx_x1 + coord_clic -> re;
	d -> cplx_x2 = d -> cplx_x2 + coord_clic -> re;
	d -> cplx_y1 = d -> cplx_y1 + coord_clic -> im;
	d -> cplx_y2 = d -> cplx_y2 + coord_clic -> im;


	return draw_img_mandelbrot(win);

}

Ez_image* zoom_julia(Ez_window win, double zoom, int mx, int my){

	
	Data *d = ez_get_data(win);
	
	d -> cplx_x1 = (d -> cplx_x1) * zoom;
	d -> cplx_x2 = (d -> cplx_x2) * zoom;
	d -> cplx_y1 = (d -> cplx_y1) * zoom;
	d -> cplx_y2 = (d -> cplx_y2) * zoom;

	COMPLEXE *coord_clic = convertir_pixel(win, mx,my);

	d -> cplx_x1 = d -> cplx_x1 + coord_clic -> re;
	d -> cplx_x2 = d -> cplx_x2 + coord_clic -> re;
	d -> cplx_y1 = d -> cplx_y1 + coord_clic -> im;
	d -> cplx_y2 = d -> cplx_y2 + coord_clic -> im;

	return draw_img_julia(win,d->iter_max,d->type_julia);

}
