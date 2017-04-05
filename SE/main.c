
/*
**  main.c
**
**  Utilisation des fonctions du mini SGF.
**
**  04/04/2007
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sgf-disk.h"
#include "sgf-fat.h"
#include "sgf-dir.h"
#include "sgf-io.h"

OFILE *file;
int c;
char *name = "essai.txt";

void ls(){
    printf("\n\n\x1B[32mListing du disque\x1B[0m\n");
    list_directory();
}

void test1()
{
    /* On lit le contenu initial du fichier "essai.txt" */
    file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
    {
        putchar(c);
        //sgf_seek(file, 8);
    }
    sgf_close(file);

    /* On supprime essai.txt */
    printf("\nRemoving essai.txt : %d\n", file->inode);
    sgf_remove(file->inode);

    /* On ecrit dans le nouveau fichier "essai.txt" */
    file = sgf_open("essai.txt", WRITE_MODE);
    sgf_puts(file, "Salut je m'apelle lucas je suis content d'ecrire dans ce buffer sinon bah je sais pas trop quoi dire d'autre! Il faut que je continue d'ecrire pour avoir un buffer avec plus de cent-vingt-huit caracteres");
    sgf_close(file);

    /* On liste une nouvelle fois le contenu du disque */
    printf("\nListing du disque\n\n");
    list_directory();

    /* On lit le nouveau contenu du "nouveau" fichier "essai.txt" */
    file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
    {
        putchar(c);
        //sgf_seek(file, 8);
    }
    sgf_close(file);
    printf("\n\n");

    /* On 'append' du contenu au fichier essai.txt" */
    file = sgf_open("essai.txt", APPEND_MODE);

    //MARCHE BIEN
    //sgf_puts(file, " Salut salut salut salut salut");

    //MARCHE BIEN
    //sgf_puts(file, " Salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut");

    sgf_puts(file, " Salut salut salut salut salut salut  salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut salut");

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
}

void test_append()
{

    /*_____________________________________________*/
    /* On ouvre un fichier vide "essai_append.txt" */
    file = sgf_open("essai_append.txt", WRITE_MODE);
    // sgf_puts(file, " ");
    sgf_close(file);

    /*________________________*/
    /* On vérifie sa création */
    ls();

    /*__________________________________________________________*/
    /* On 'append' 500 fois un caractere au fichier "essai.txt" */

    int i;
    for (i = 0; i < 500; i++)
    {
        file = sgf_open("essai_append.txt", APPEND_MODE);
        sgf_putc(file, ('a' + (i % 26)));
        sgf_close(file);
    }

    /*________________________*/
    /* On vérifie (length doit ête = 500) */
    printf("_________________\n");
    ls();
    printf("_________________\n");

    /*____________________________________________________________*/
    /* On lit pour vérifier le contenu de "essai.txt" */
    file = sgf_open("essai_append.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
    {
        putchar(c);
        //sgf_seek(file, 8);
    }

    sgf_close(file);
}

void test_write(char *text)
{
    /* On ouvre un fichier "essai_write.txt" et on lui ajoute du contenu de départ*/
    file = sgf_open("essai_write.txt", WRITE_MODE);
    sgf_puts(file, "Ceci est du contenu par defaut\nOn va ajouter du contenu avec la fonction write \n");
    sgf_close(file);

    /* On vérifie que la création et l'écriture ont réussi */
    ls();

    /* On lit pour vérifier le contenu de "essai.txt" */
    printf("\n\x1B[32mLecture du fichier \"essai_write.txt\"\x1B[0m\n");
    file = sgf_open("essai_write.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
        putchar(c);
    sgf_close(file);

    file = sgf_open("essai_write.txt", APPEND_MODE);
    sgf_write(file, text, strlen(text));
    sgf_close(file);

    /* On lit pour vérifier l'ecriture avec write de "essai.txt" */
    printf("\n\x1B[32mLecture du fichier \"essai_write.txt\"\x1B[0m\n");
    file = sgf_open("essai_write.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
        putchar(c);
    sgf_close(file);


    ls();
}

int main()
{
    // Texte de 140 caracteres
    char *text1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc in rhoncus elit. Phasellus finibus ornare augue in dictum. Nam malesuada amet.";
    
    OFILE *file;
    int c;
    init_sgf();

    // test1();
    // test_append();
    test_write(text1);

    printf("\n\n\n");
    return (EXIT_SUCCESS);
}