/*
**    Part of IFJ Project 2019/2020
**    Author: Simon Fenko xfenko01
**    Kostra bola vytvorena fakultou VUT FIT, upravena Simonom Fenkom
*/

#include "stack.h"

void stackError(int error_code)
{
    return;
}
int STACK_SIZE = MAX_STACK;

//void stackError ( int error_code ){
/*   ----------
** Vytiskne upozornění, že došlo k chybě při práci se zásobníkem.
**
** TUTO FUNKCI, PROSÍME, NEUPRAVUJTE!
*/
/*    static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
    if ( error_code <= 0 || error_code > MAX_SERR )
        error_code = 0;
    printf ( "%s\n", SERR_STRINGS[error_code] );
    err_flag = 1;
}*/

void stackInit ( tStack* s )
{
/*   ---------
** Provede inicializaci zásobníku - nastaví vrchol zásobníku.
** Hodnoty ve statickém poli neupravujte - po inicializaci zásobníku
** jsou nedefinované.
**
** V případě, že funkce dostane jako parametr s == NULL,
** volejte funkci stackError(SERR_INIT). U ostatních funkcí pro zjednodušení
** předpokládejte, že tato situace nenastane.
*/

    if (s==NULL) //ak je null nastane serr init
    {
        stackError(SERR_INIT);
    } else
    {
        s->top = -1;
    }
}

int stackEmpty ( const tStack* s )
{
/*  ----------
** Vrací nenulovou hodnotu, pokud je zásobník prázdný, jinak vrací hodnotu 0.
** Funkci implementujte jako jediný příkaz. Vyvarujte se zejména konstrukce
** typu "if ( true ) b=true else b=false".
*/

    return s->top == -1; //prazdny zasobnik = -1
}

int stackFull ( const tStack* s )
{
/*  ---------
** Vrací nenulovou hodnotu, je-li zásobník plný, jinak vrací hodnotu 0.
** Dejte si zde pozor na častou programátorskou chybu "o jedničku"
** a dobře se zamyslete, kdy je zásobník plný, jestliže může obsahovat
** nejvýše STACK_SIZE prkvů a první prvek je vložen na pozici 0.
**
** Funkci implementujte jako jediný příkaz.
*/

    return s->top == STACK_SIZE - 1; //max. mozny index zasob. je stack size-1
}
void stackTop ( const tStack* s, int* c )
{
/*   --------
** Vrací znak z vrcholu zásobníku prostřednictvím parametru c.
** Tato operace ale prvek z vrcholu zásobníku neodstraňuje.
** Volání operace Top při prázdném zásobníku je nekorektní
** a ošetřete ho voláním funkce stackError(SERR_TOP).
**
** Pro ověření, zda je zásobník prázdný, použijte dříve definovanou
** funkci stackEmpty.
*/

    if (stackEmpty(s))
    {
        stackError(SERR_TOP); // keď je prazdny tak nastane serr top
    } else
    {
        *c = s->arr[s->top]; //priradenie hodnoty na vrchool zasobniku do ukazatela c
    }
}


void stackPop ( tStack* s )
{
/*   --------
** Odstraní prvek z vrcholu zásobníku. Pro ověření, zda je zásobník prázdný,
** použijte dříve definovanou funkci stackEmpty.
**
** Vyvolání operace Pop při prázdném zásobníku je sice podezřelé a může
** signalizovat chybu v algoritmu, ve kterém je zásobník použit, ale funkci
** pro ošetření chyby zde nevolejte (můžeme zásobník ponechat prázdný).
** Spíše než volání chyby by se zde hodilo vypsat varování, což však pro
** jednoduchost neděláme.
**
*/

    if (!stackEmpty(s))
    {
        s->top--;
    }
      
}


void stackPush ( tStack* s, int c )
{
/*   ---------
** Vloží znak na vrchol zásobníku. Pokus o vložení prvku do plného zásobníku
** je nekorektní a ošetřete ho voláním procedury stackError(SERR_PUSH).
**
** Pro ověření, zda je zásobník plný, použijte dříve definovanou
** funkci stackFull.
*/

    if (stackFull(s)) {
        stackError(SERR_PUSH); //ked je prazdny nastane ser push
    } else {
        s->top++;
        s->arr[s->top] = c; //zvysenie indexu vrcholu zasobniku a ulozi hodnoty c na zvyseny index
    }
}
