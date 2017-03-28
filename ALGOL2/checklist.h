#ifndef __CHECKLIST__
#define __CHECKLIST__
#include "ez-draw.h"
#include "radiobutton.h"

typedef struct {

	Radiobutton *rb;
	int elem;


}Checklist;

Checklist* init_checklist();
void enable_button(Radiobutton *rb, int i, int max);
Radiobutton* add_button(Radiobutton *rd, char str[BUFFER_RB]);


#endif
