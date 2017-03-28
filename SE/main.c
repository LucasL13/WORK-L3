
/*
**  main.c
**
**  Utilisation des fonctions du mini SGF.
**
**  04/04/2007
*/

#include <stdio.h>
#include <stdlib.h>

#include "sgf-disk.h"
#include "sgf-fat.h"
#include "sgf-dir.h"
#include "sgf-io.h"

int main() {
	OFILE* file;
	int c;

	init_sgf();

	printf("\nListing du disque :\n____________________________________________\n\n");
	list_directory();
	printf("____________________________________________\n\n\n");



	printf("____________________________________________\n");
	file = sgf_open("essai.txt", READ_MODE);

	while ((c = sgf_getc(file)) > 0) {
		putchar(c);
		// if(sgf_seek(file, 1) < 0)
		// 	break;
	}

	sgf_close(file);
	printf("____________________________________________\n\n");

	file = sgf_open("essai.txt", WRITE_MODE);

	// printf("____________________________________________\n");

	int i;
	for(i=0; i < 26; i++){
		sgf_putc(file, 'a'+i);
	}
	sgf_putc(file, '\n');

	sgf_close(file);
	//
	// i	mnt i;
	// for(i=0; i < 100; i++){
	// 	sgf_putc(file, 'a');
	// }
	//
	// sgf_close(file);
	// file = sgf_open("essai.txt", READ_MODE);
	// sgf_seek(file, -(file->length));
	//
	// while ((c = sgf_getc(file)) > 0) {
	// 	putchar(c);
	// 	// if(sgf_seek(file, 7) < 0)
	// 	// 	break;
	// }

	//sgf_close(file);

	return (EXIT_SUCCESS);
	}
