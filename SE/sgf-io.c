
/*
**  sgf-io.c
**
**  fonctions de lecture/�criture (de caract�res et de blocs)
**  dans un fichier ouvert.
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sgf-disk.h"
#include "sgf-data.h"
#include "sgf-fat.h"
#include "sgf-dir.h"
#include "sgf-io.h"


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"



/**********************************************************************
 *
 *  FONCTIONS DE LECTURE DANS UN FICHIER
 *
 *********************************************************************/

/**********************************************************************
 Lire dans le "buffer" le bloc logique "nubloc" dans le fichier
 ouvert "file".
 
 ATTENTION: Faites en sorte de ne pas recommencer le cha�nage �
            partir du bloc 0 si cela n'est pas utile. Pour �viter ce
            parcours vous pouvez ajouter un champ � la structure OFILE
            qui vous donne l'adresse physique du bloc courant.
 *********************************************************************/

void sgf_read_bloc(OFILE* file, int nubloc)
{
    int adr;
    
	assert(nubloc < (file->length + BLOCK_SIZE-1)/BLOCK_SIZE);
	
	adr = file->first;
	
	while(nubloc-- > 0)
	{
		assert(adr > 0);
		adr = get_fat(adr);
	}
	
	read_block(adr, &file->buffer);
}


/**********************************************************************
 Lire un caract�re dans un fichier ouvert. Cette fonction renvoie
 -1 si elle trouve la fin du fichier.
 *********************************************************************/

int sgf_getc(OFILE* file)
    {
    int c;
    
    assert (file->mode == READ_MODE);
    
    /* d�tecter la fin de fichier */
    if (file->ptr >= file->length){
        return (-1);
    }

    /* si le buffer est vide, le remplir */
    if ((file->ptr % BLOCK_SIZE) == 0)
    {
        sgf_read_bloc(file, file->ptr / BLOCK_SIZE);
    }

    c = file->buffer[ (file->ptr % BLOCK_SIZE) ];
    file->ptr ++;
    return (c);
    }



/**********************************************************************
 *
 *  FONCTIONS D'ECRITURE DANS UN FICHIER
 *
 *********************************************************************/

/**********************************************************************
 Ajouter le bloc contenu dans le tampon au fichier ouvert d�crit
 par "f".
 *********************************************************************/

int sgf_append_block(OFILE* f)
{
    TBLOCK b;
    int adr;
    
    if(f->mode == WRITE_MODE){
        adr = alloc_block();
        if(adr < 0)
            return -1;
    }
    else{
        adr = f->last;
    }

    write_block(adr, f->buffer);
	set_fat(adr, FAT_EOF);

    if(f->mode == APPEND_MODE)
        f->mode = WRITE_MODE;

	if(f->first == FAT_EOF)
	{
		f->first = adr;
		f->last = adr;
	}
	else
	{
		set_fat(f->last, adr);
		f->last = adr;
	}

	b.inode.length = f->ptr;
	b.inode.first = f->first;
	b.inode.last = f->last;
	
	write_block(f->inode, &b.data);

	return 0;
}


/**********************************************************************
 Ecrire le caract�re "c" dans le fichier ouvert d�crit par "file".
 *********************************************************************/

int sgf_putc(OFILE* f, char  c)
{
    assert (f->mode == WRITE_MODE || f->mode == APPEND_MODE);
    
    f->buffer[f->ptr % BLOCK_SIZE] = c;
    f->ptr++;

    if((f->ptr % BLOCK_SIZE) == 0)
    {
		if(sgf_append_block(f) < 0)
		{
			return -1;
		}
	}
	return 0;
}


/**********************************************************************
 �crire la cha�ne de caract�re "s" dans un fichier ouvert en �criture
 d�crit par "file".
 *********************************************************************/

void sgf_puts(OFILE* file, char* s)
{
    assert (file->mode == WRITE_MODE || file->mode == APPEND_MODE);
    for (; (*s != '\0'); s++) {
        sgf_putc(file, *s);
    }
}




int sgf_write(OFILE* f, char *data, int size){

    // printf("Last file (%d->%d) : (buff) %s\n", f->last, f->ptr, f->buffer);
    int local_ptr = 0;

    while(local_ptr < size){
        memcpy(f->buffer+(f->ptr%BLOCK_SIZE), data+local_ptr, 128-(f->ptr%BLOCK_SIZE) );
        local_ptr+= 128 - (f->ptr%BLOCK_SIZE);
        f->ptr += local_ptr;
        sgf_append_block(f);
    }
    
    printf("\n\x1B[32msgf_write: \x1B[33m%d \x1B[0mcaracteres ecrits\n", local_ptr);

    return 0;
}


/**********************************************************************
 *
 *  FONCTIONS D'OUVERTURE, DE FERMETURE ET DE DESTRUCTION.
 *
 *********************************************************************/

/************************************************************
 D�truire un fichier.
 ************************************************************/

void sgf_remove(int adr_inode)
{
    TBLOCK b;
    int adr, k;
    
    read_block(adr_inode, &b.data);
    adr = b.inode.first;

    while(adr != FAT_EOF)
    {
        k = get_fat(adr);
        set_fat(adr, FAT_FREE);
        adr = k;
    }

    b.inode.first = FAT_EOF;
    b.inode.last = FAT_EOF;
    b.inode.length = 0;

    set_fat(adr_inode, FAT_FREE); 
}


/************************************************************
 Ouvrir un fichier en �criture seulement (NULL si �chec).
 ************************************************************/

static  OFILE*  sgf_open_write(const char* nom)
    {
    int inode, oldinode;
    OFILE* file;
    TBLOCK b;

    /* Rechercher un bloc libre sur disque */
    inode = alloc_block();
    assert (inode >= 0);

    /* Allouer une structure OFILE */
    file = malloc(sizeof(struct OFILE));
    if (file == NULL) return (NULL);
    
    /* pr�parer un inode vers un fichier vide */
    b.inode.length = 0;
    b.inode.first  = FAT_EOF;
    b.inode.last   = FAT_EOF;

    /* sauver ce inode */
    write_block(inode, &b.data);
    set_fat(inode, FAT_INODE);

    /* mettre a jour le repertoire */
    oldinode = add_inode(nom, inode);
   /* if (oldinode > 0) sgf_remove(oldinode); */
    
    file->length  = 0;
    file->first   = FAT_EOF;
    file->last    = FAT_EOF;
    file->inode   = inode;
    file->mode    = WRITE_MODE;
    file->ptr     = 0;

    return (file);
    }


/************************************************************
 Ouvrir un fichier en lecture seulement (NULL si �chec).
 ************************************************************/

static  OFILE*  sgf_open_read(const char* nom)
    {
    int inode;
    OFILE* file;
    TBLOCK b;
    
    /* Chercher le fichier dans le r�pertoire */
    inode = find_inode(nom);
    if (inode < 0) return (NULL);
    
    /* lire le inode */
    read_block(inode, &b.data);
    
    /* Allouer une structure OFILE */
    file = malloc(sizeof(struct OFILE));
    if (file == NULL) return (NULL);
    
    file->length  = b.inode.length;
    file->first   = b.inode.first;
    file->last    = b.inode.last;
    file->inode   = inode;
    file->mode    = READ_MODE;
    file->ptr     = 0;
    
    return (file);
    }


/************************************************************
 Ouvrir un fichier en APPEND_MODE.
 ************************************************************/

static  OFILE*  sgf_open_append(const char* nom)
{
    int inode;
    OFILE* file;
    TBLOCK b;
    
    /* Chercher le fichier dans le r�pertoire */
    inode = find_inode(nom);
    if (inode < 0) return (NULL);

    /* lire le inode */
    read_block(inode, &b.data);
    
    /* Allouer une structure OFILE */
    file = malloc(sizeof(struct OFILE));
    if (file == NULL) return (NULL);
    
    file->length  = b.inode.length;
    file->first   = b.inode.first;
    file->last    = b.inode.last;
    file->inode   = inode;
    file->mode    = APPEND_MODE;
    file->ptr     = b.inode.length; 

    if((b.inode.length % BLOCK_SIZE) == 0)
        file->mode = WRITE_MODE;
    else{
        read_block(file->last, &b.data);
        memcpy(file->buffer, b.data, sizeof(char)*BLOCK_SIZE);
    }

    return (file);
}


/************************************************************
 Ouvrir un fichier (NULL si �chec).
 ************************************************************/

OFILE* sgf_open (const char* nom, int mode)
    {
    switch (mode)
        {
        case READ_MODE:  
			return sgf_open_read(nom);
        case WRITE_MODE:
			return sgf_open_write(nom);
        case APPEND_MODE: 
			return sgf_open_append(nom);
        default:         return (NULL);
        }
    }


/************************************************************
 Fermer un fichier ouvert.
 ************************************************************/

int sgf_close(OFILE* file)
 {
	 if(file->mode == WRITE_MODE || file->mode == APPEND_MODE)
	 {
		if((file->ptr % BLOCK_SIZE) != 0)
		{
			if(sgf_append_block(file) < 0)
			{
				return -1;
			}
		}
	}
	free(file);
	return 0; 
}


/**********************************************************************
 initialiser le SGF
 *********************************************************************/

void init_sgf (void)
 {
    init_sgf_disk();
    init_sgf_fat();
 }


/**********************************************************************
 *
 *  AUTRES FONCTIONS.
 *
 *********************************************************************/

/************************************************************
 D�place le pointeur ptr
 ************************************************************/

int sgf_seek(OFILE* file, int pos)
{
	if(file->ptr+pos-1 >= file->length)
	{
		return -1;
	}
	else 
	{	
		if(pos-1 > BLOCK_SIZE - (file->ptr % BLOCK_SIZE))
		{
			file->ptr += pos-1;
			sgf_read_bloc(file, (file->ptr/BLOCK_SIZE));
			return 0;
		}
		else 
		{
			file->ptr += pos-1;
			return 0;
		}
	}
}




