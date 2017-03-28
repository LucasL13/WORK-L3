#include "save_ppm.h"
#include "Fractale.h"
#include "draw.h"
#include "bresenham.h"

void init_pixmap(int pixmap[][LARGEUR]){

	for(int i = 0 ; i<LARGEUR ; i++){
		for(int j = 0 ; j<LARGEUR ; j++){
			pixmap[j][i] = 0;
		}
	}

}




void save_ppm_koch(char* name, int pixmap[][LARGEUR], int largeur, int hauteur){

	FILE* file = fopen(name,"w");
	fprintf(file,"P3\n");
	fprintf(file,"%d %d\n",largeur,largeur);
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

void draw_and_save(PLISTE list, int pixmap[][LARGEUR]){

	PLISTE tmp = list;

	while(tmp -> next != NULL){
		
		tracer_seg_bresenham((int)tmp->x,(int)tmp->y,(int)tmp->next->x,(int)tmp->next->y,pixmap);
		tmp = tmp -> next;
		

	}
	
	tracer_seg_bresenham(list->x,list->y,tmp->x,tmp->y,pixmap);

	save_ppm_koch("save/koch.ppm",pixmap,LARGEUR,LARGEUR);

}


void save_koch(int n, double c, int choix){

	PLISTE list;
	
	
	for(int i=0 ; i<=n ; i++){
		
		list = koch_center(i,c,choix);

		switch(i){
			case 0:
				ecrire_liste("koch/k0.in",list);
				break;
			case 1:
				ecrire_liste("koch/k1.in",list);
				break;
			case 2:
				ecrire_liste("koch/k2.in",list);
				break;
			case 3:
				ecrire_liste("koch/k3.in",list);
				break;
			case 4:
				ecrire_liste("koch/k4.in",list);
				break;
			case 5:
				ecrire_liste("koch/k5.in",list);
				break;
			case 6:
				ecrire_liste("koch/k6.in",list);
				break;
			case 7:
				ecrire_liste("koch/k7.in",list);
				break;
			case 8:
				ecrire_liste("koch/k8.in",list);
				break;
			case 9:
				ecrire_liste("koch/k9.in",list);
				break;
			
		}
	}	
}


void save_ppm_from_pixmap(Ez_image *img, char* name){

	FILE* file = fopen(name,"w");
	fprintf(file,"P3\n");
	fprintf(file,"%d %d\n",LARGEUR,HAUTEUR);
	fprintf(file,"255\n");
	
	for(int i = 0 ; i<(LARGEUR*HAUTEUR*4) ; i+=4){
		
			
			fprintf(file,"%d ",img -> pixels_rgba[i]);
			fprintf(file,"%d ",img -> pixels_rgba[i + 1]);
			fprintf(file,"%d ",img -> pixels_rgba[i + 2]);
			
		
	}


	fclose(file);

}



















