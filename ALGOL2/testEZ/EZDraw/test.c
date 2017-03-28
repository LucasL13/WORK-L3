#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#define ON 1
#define OFF 0

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {

	int calcul;
	int k;
	//pthread_mutex_t mutex;

}Bidule;

void *fn(void* arg){

	int k = 0;
	Bidule *bidule = arg;
	for(int i=0 ; i<INT_MAX ; i++){
		k++;
	}
	bidule -> k = k;
	printf("je termine le thread !\n");
	
	pthread_mutex_lock(&mutex);
	bidule -> calcul = OFF;
	pthread_mutex_unlock(&mutex);		

	pthread_exit(NULL);
	
}

void *fn2(){

	int i = 1;
	while(1){
		printf("animation %d...\n",i);
		sleep(1);
		i = (i+1)%4;
	}

}

int main(){

	int t = 0;
	pthread_t thread1;
	Bidule bidule;
	
	bidule.calcul = ON;
	bidule.k = 0;
	
	
	printf("création du thread \n");
	t = pthread_create(&thread1,NULL,fn,&bidule);
	
	while(1){
		printf("alive !\n");
		pthread_mutex_lock(&mutex);
		if(bidule.calcul == OFF) {printf("calcul terminé \n");break;}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
	//pthread_join(thread1,NULL);
		
	printf("a = %d\n",bidule.k);	

	return 0;
}
