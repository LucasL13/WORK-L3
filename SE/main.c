
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

int main()
{
    OFILE *file;
    int c;
    init_sgf();



    /*_________________________________________________*/
    /* On liste une premiere fois le contenu du disque */
    printf("\nListing du disque\n\n");
    list_directory();




    /*__________________________________________________*/
    /* On lit le contenu initial du fichier "essai.txt" */
    file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
    {
        putchar(c);
	//sgf_seek(file, 8);
    }
    sgf_close(file);



    /*_______________________*/
    /* On supprime essai.txt */
    printf("\nRemoving essai.txt : %d\n", file->inode);
    sgf_remove(file->inode);




    /*______________________________________________*/
    /* On ecrit dans le nouveau fichier "essai.txt" */
	file = sgf_open("essai.txt", WRITE_MODE);
	sgf_puts(file, "Salut je m'apelle lucas je suis content d'ecrire dans ce buffer sinon bah je sais pas trop quoi dire d'autre");
	sgf_close(file);



    /*_________________________________________________*/
    /* On liste une nouvelle fois le contenu du disque */
	printf("\nListing du disque\n\n");
    list_directory(); 




    /*____________________________________________________________*/
    /* On lit le nouveau contenu du "nouveau" fichier "essai.txt" */
	file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
    {
		putchar(c);
	    //sgf_seek(file, 8);
    }
    sgf_close(file);




    /*____________________________________________________________*/
    /* On 'append' du contenu au fichier essai.txt" */
    file = sgf_open("essai.txt", WRITE_MODE);
	sgf_puts(file, "\nJ'ajoute du nouveau contenu au fichier ! On va voir ce que ça peut donner'");
	sgf_close(file);



    /*_________________________________________________*/
    /* On liste une nouvelle fois le contenu du disque */
	printf("\nListing du disque\n\n");
    list_directory(); 




    /*____________________________________________________________*/
    /* On lit le nouveau contenu du "nouveau" fichier "essai.txt" */
	file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
    {
		putchar(c);
	    //sgf_seek(file, 8);
    }
    sgf_close(file);




    
	printf("\n\n\n");
    return (EXIT_SUCCESS);
}