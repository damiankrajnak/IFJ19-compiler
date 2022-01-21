
/* Předmět: Algoritmy (IAL) - FIT VUT v Brně
 * Hlavičkový soubor pro c201.c (Jednosměrně vázaný lineární seznam)
 * Vytvořil: Martin Tuček, září 2005
 * Upravil: Kamil Jeřábek, září 2018
 *
 *
 * Tento soubor, prosíme, neupravujte!
 * Please, do not modify this file!
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#define TRUE 1
#define FALSE 0
#define MAX_LEN 40
                                                            
                                                                /* Error flag */
extern int errflg;
                                                             
                                                /* Definition of list element */
typedef struct tElem {
    struct tElem *ptr;
    char data[MAX_LEN];
} *tElemPtr;
                                                    
                                                        /* Definition of list */
typedef struct {
    tElemPtr Act;
    tElemPtr First;
} tList;
                                            
                                               /* Functions to be implemented */
void InitList (tList *);
void DisposeList (tList *);
void InsertFirst (tList *, char *);
void First (tList *);
void CopyFirst (tList *, char **);
void DeleteFirst (tList *);
void PostDelete (tList *);
void PostInsert (tList *, char *);
void Succ (tList *);
void Copy (tList *, char **);
void Actualize (tList *, char *);
int Active (tList *);

