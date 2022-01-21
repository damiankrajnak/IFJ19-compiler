/*
**    Part of IFJ Project 2019/2020
**    Author: Simon Fenko xfenko01
**    Kostra bola vytvorená fakultou VUT FIT, upravena Simonom Fenkom
*/

#ifndef stack_h
#define stack_h
#include <stdio.h>
#define MAX_STACK 100
/*
 * Hodnota MAX_STACK udává skutečnou velikost statického pole pro uložení
 * hodnot zásobníku. Při implementaci operací nad ADT zásobník však
 * předpokládejte, že velikost tohoto pole je pouze STACK_SIZE. Umožní to
 * jednoduše měnit velikost zásobníku v průběhu testování. Při implementaci
 * tedy hodnotu MAX_STACK vůbec nepoužívejte
 */
//extern int err_flag;
                                        /* Chybové kódy pro funkci stackError */
#define MAX_SERR    3                                   /* počet možných chyb */
#define SERR_INIT   1                                  /* chyba při stackInit */
#define SERR_PUSH   2                                  /* chyba při stackPush */
#define SERR_TOP    3                                   /* chyba při stackTop */


extern int STACK_SIZE;

                             /* ADT zásobník implementovaný ve statickém poli */
typedef struct {
    int arr[MAX_STACK];                             /* pole pro uložení hodnot */
    int top;                                /* index prvku na vrcholu zásobníku */
} tStack;

                                  /* Hlavičky funkcí pro práci se zásobníkem. */
void stackError ( int error_code );
void stackInit ( tStack* s );
int stackEmpty ( const tStack* s );
int stackFull ( const tStack* s );
void stackTop ( const tStack* s, int* c );
void stackPop ( tStack* s );
void stackPush ( tStack* s, int c );

#endif /* stack_h */
