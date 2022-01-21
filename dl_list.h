/*
**    Part of IFJ Project 2019/2020
**    Author: Simon Fenko xfenko01
**    Kostra bola vytvorena fakultou VUT FIT, ako časť projektu IAL robena Samuelom Stuchlym a upravena
**    Simonom Fenkom
*/
/* Předmět: Algoritmy (IAL) - FIT VUT v Brně
 * Hlavičkový soubor pro c206.c (Dvousměrně vázaný lineární seznam)
 * Vytvořil: Martin Tuček, září 2005
 * Upravil: Kamil Jeřábek, září 2019
 *  
 * Tento soubor, prosíme, neupravujte!  
 */

#ifndef dl_list_h
#define dl_list_h

#include<stdio.h>
#include<stdlib.h>
#include "scanner.h"

#define FALSE 0
#define TRUE 1
 
extern int err_flag;
typedef struct tDLElem {                 /* prvek dvousměrně vázaného seznamu */ 
        TOKEN data;                                            /* užitečná data */
        struct tDLElem *lptr;          /* ukazatel na předchozí prvek seznamu */
        struct tDLElem *rptr;        /* ukazatel na následující prvek seznamu */
} *tDLElemPtr;

typedef struct {                                  /* dvousměrně vázaný seznam */
    tDLElemPtr First;                      /* ukazatel na první prvek seznamu */
    tDLElemPtr Act;                     /* ukazatel na aktuální prvek seznamu */
    tDLElemPtr Last;                    /* ukazatel na posledni prvek seznamu */
} tDLList;

                                             /* prototypy jednotlivých funkcí */
void DLInitList (tDLList *);
void DLDisposeList (tDLList *);
void DLInsertFirst (tDLList *, TOKEN);
void DLInsertLast(tDLList *, TOKEN);
void DLFirst (tDLList *);
void DLLast (tDLList *);
void DLCopyFirst (tDLList *, TOKEN *);
void DLCopyLast (tDLList *, TOKEN *);
void DLDeleteFirst (tDLList *);
void DLDeleteLast (tDLList *);
void DLPostDelete (tDLList *);
void DLPreDelete (tDLList *);
void DLPostInsert (tDLList *, TOKEN);
void DLPreInsert (tDLList *, TOKEN);
void DLCopy (tDLList *, TOKEN *);
void DLActualize (tDLList *, TOKEN);
void DLSucc (tDLList *);
void DLPred (tDLList *);
int DLActive (tDLList *);

#endif /* dl_list_h  */
/* Konec hlavičkového souboru c206.h */
