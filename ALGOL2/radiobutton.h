#ifndef __RADIOBUTTON__
#define __RADIOBUTTON__
#define BUFFER_RB 25

typedef struct Radiobutton Radiobutton;

struct Radiobutton {

	int ENABLE;
	
	Radiobutton *next;
	char str[BUFFER_RB];

};

#endif
