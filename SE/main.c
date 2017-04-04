
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

OFILE *file;
int c;
char *name = "essai.txt";

void ls()
{
    printf("\nListing du disque\n\n");
    list_directory();
}

void test1()
{

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
    sgf_puts(file, "Salut je m'apelle lucas je suis content d'ecrire dans ce buffer sinon bah je sais pas trop quoi dire d'autre! Il faut que je continue d'ecrire pour avoir un buffer avec plus de cent-vingt-huit caracteres");
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
    printf("\n\n");

    printf("\n---------- APPEND ------------\n");

    /*____________________________________________________________*/
    /* On 'append' du contenu au fichier essai.txt" */
    file = sgf_open("essai.txt", APPEND_MODE);

    //MARCHE BIEN
    //sgf_puts(file, " Salut salut salut salut salut");

    //MARCHE BIEN
    //sgf_puts(file, " Salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut");

    sgf_puts(file, " Salut salut salut salut salut salut  salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut");

    sgf_close(file);

    printf("\n---------- APPEND ------------\n");

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
}


void test_append(){
    /*________________________________*/
    /* On vide le fichier "essai.txt" */
    file = sgf_open("essai.txt", WRITE_MODE);
    // sgf_puts(file, " ");
    sgf_close(file);

    /*____________*/
    /* On vérifie */
    ls();


    /*__________________________________________________________*/
    /* On 'append' 500 fois un caractere au fichier "essai.txt" */

    int i;
    for(i=0; i<500; i++){
        file = sgf_open("essai.txt", APPEND_MODE);
        sgf_putc(file, ((i+97)%122));
        sgf_close(file);
    }

    /*____________________________________________________________*/
    /* On lit pour vérifier le contenu de "essai.txt" */
    file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
    {
        putchar(c);
        //sgf_seek(file, 8);
    }
    sgf_close(file);
}

int main()
{
    OFILE *file;
    int c;
    init_sgf();

    /*_________________________________________________*/
    /* On liste une premiere fois le contenu du disque */
    ls();


    //test1();
    test_append();

    printf("\n\n\n");
    return (EXIT_SUCCESS);
}