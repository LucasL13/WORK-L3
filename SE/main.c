
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

void ls()
{
    printf("\n\n\x1B[32mListing du disque\x1B[0m\n");
    list_directory();
}

void test_remove(char *text)
{
    /* On liste une premiere fois le contenu du disque */
    ls();

    /* On lit le contenu initial du fichier "essai.txt" */
    file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
        putchar(c);
    sgf_close(file);

    /* On supprime essai.txt */
    printf("\n\x1B[32mRemoving essai.txt(%d)\n\x1B[0m", file->inode);
    sgf_remove(file->inode);

    /* On ecrit dans le nouveau fichier "essai.txt" */
    printf("\n\x1B[32mEcriture dans essai.txt(%d)\x1B[0m", file->inode);
    file = sgf_open("essai.txt", WRITE_MODE);
    sgf_puts(file, text);
    sgf_close(file);

    /* On liste une nouvelle fois le contenu du disque */
    ls();

    /* On lit le nouveau contenu du "nouveau" fichier "essai.txt" */
    printf("\n\x1B[32mLecture du fichier \"essai.txt\"\x1B[0m\n");
    file = sgf_open("essai.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
        putchar(c);
    sgf_close(file);
}

void test_append()
{

    /* On ouvre un fichier vide "essai_append.txt" */
    file = sgf_open("essai_append.txt", WRITE_MODE);
    sgf_close(file);

    /* On vérifie sa création */
    ls();

    /* On 'append' 500 fois un caractere au fichier "essai.txt" */
    int i;
    for (i = 0; i < 500; i++)
    {
        file = sgf_open("essai_append.txt", APPEND_MODE);
        sgf_putc(file, ('a' + (i % 26)));
        sgf_close(file);
    }

    /* On vérifie (length doit ête = 500) */
    ls();

    /* On lit pour vérifier le contenu de "essai_append.txt" */
    printf("\n\x1B[32mLecture du fichier \"essai_append.txt\"\x1B[0m\n");
    file = sgf_open("essai_append.txt", READ_MODE);
    while ((c = sgf_getc(file)) > 0)
        putchar(c);
    sgf_close(file);
}

void test_write(char *text)
{
    /* On ouvre un fichier "essai_write.txt" et on lui ajoute du contenu de départ*/
    /* Enlever la ligne "sgf_puts" pour partir d'un fichier vide */
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
    // Texte de 280 caracteres
    char *text2 = "\nMaecenas quam dui, dictum pharetra egestas ac, pretium varius nisl. Donec nec ante fringilla lacus vestibulum aliquam. Nulla venenatis lorem magna, at eleifend lacus feugiat sed. Donec iaculis massa nec tellus auctor fermentum. Fusce accumsan, turpis a finibus imperdiet posuere.";
    // Texte de 1000 caracteres
    char *text3 = "\nInteger posuere justo quis massa mollis, sed pulvinar leo laoreet. Aenean maximus vel neque ac faucibus. Ut non velit neque. Pellentesque ex erat, lacinia nec aliquam et, vehicula eu dolor. In vel posuere risus, ac feugiat eros. Sed et nibh euismod, aliquet quam mollis, consequat enim. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Cras semper, magna eu maximus dictum, nisl mauris euismod lorem, non faucibus nulla neque non augue. Curabitur convallis sem justo, non tempor metus dictum et. In hac habitasse platea dictumst. Quisque at tortor mi. Praesent maximus porta nisi eu ultricies. Donec gravida, mi ut fringilla accumsan, nulla velit suscipit dolor, sit amet suscipit metus lectus vitae libero. Nunc non mattis ante, lacinia faucibus velit. Curabitur euismod tristique nisl ut molestie.Donec faucibus nunc nec quam mattis pretium. Sed dui urna, tempus facilisis malesuada id, ornare et velit. Ut id aliquet diam. Suspendise efficitur finibus metus.";

    OFILE *file;
    int c;
    init_sgf();

    // test_remove(text2);
    // test_append();
    test_write(text3);

    printf("\n\n\n");
    return (EXIT_SUCCESS);
}