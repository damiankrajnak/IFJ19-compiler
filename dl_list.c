/*
**    Part of IFJ Project 2019/2020
**    Author: Simon Fenko xfenko01
**    Kostra bola vytvorena fakultou VUT FIT, ako časť projektu IAL robena Samuelom Stuchlym a upravena
**    Simonom Fenkom
*/
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "dl_list.h"

//int errflg;

//void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
//    printf ("*ERROR* The program has performed an illegal operation.\n");
  //  errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
//    return;
/*
}
*/
void DLError()
{
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
    //L->First = NULL;
    //L->Act = NULL;
    //L->Last = NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
	while(L->First != NULL) 			//loop sa vykonava az pokial je zoznam prazdny
	{
		tDLElemPtr elemPtr;				//pomocny pointer
		elemPtr = L->Last;
		if (L->First != L->Last)		//test ci ma zoznam uz len 1 prvok
		{
			L->Last = elemPtr->lptr;	//predchadzajuci prvok sa stava poslednym (L->Last)
			free(elemPtr);				//uvolnuje sa byvaly posledny prvok 
		}
		else{
			free(elemPtr);				//uvolnuje sa posleny prvok 
			L->First = NULL;			
    		L->Act = NULL;
    		L->Last = NULL;
		}
	}
}

void DLInsertFirst (tDLList *L, TOKEN val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	struct tDLElem *newElemPtr =  malloc(sizeof(struct tDLElem));  			//alokuje pamat pre novy prvok
	if (newElemPtr == NULL)							//test ci sa malloc podaril
	{

        DLError();
	}
	else {
		newElemPtr->data = val;
		newElemPtr->lptr = NULL;

		if (L->First != NULL)   				//test ci je zoznam prazdny 
		{
			L->First->lptr = newElemPtr;		//prepaja novy prvok s prvym prvkom 
			newElemPtr->rptr = L->First;
		}
		else{
			L->Last = newElemPtr;				//novy prvok je aj poslednym prvkom zoznamu 
			newElemPtr->rptr =NULL;
		}
	}	 L->First = newElemPtr; 				//nastavuje novy prvok ako prvy prvok zoznamu 
}

void DLInsertLast(tDLList *L, TOKEN val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
	struct tDLElem  *newElemPtr =  malloc(sizeof(struct tDLElem)); // alokuje pamat pre novy prvok
	if (newElemPtr == NULL)
	{
		DLError();
	}
	else {
		newElemPtr->data = val;
		
		newElemPtr->rptr = NULL;			
		if (L->Last != NULL)   				// test ci je zoznam prazdny 
		{
			L->Last->rptr = newElemPtr;		// zaraduje novy prvok za podleny prvok
			newElemPtr->lptr = L->Last;
		}
		else{
			L->First = newElemPtr;   		// novy prvok je aj prvym prvkom zoznamu 
			newElemPtr->lptr = NULL;
		}
		L->Last = newElemPtr;				// nastavuje novy prvok ako posledny prvok zoznamu
	}
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->First;		//nastavuje aktivitu na prvy prvok
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->Last;		//nastavuje aktivitu na posledny prvok
}

void DLCopyFirst (tDLList *L, TOKEN *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

	if (L->First != NULL)		//test ci je zoznam prazdny
	{
		*val = L->First->data;		//predava hodnotu prveho prvku pomocou ukazatela val
	}
	else {
		DLError();
	}
}

void DLCopyLast (tDLList *L, TOKEN *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	if (L->Last != NULL)		//test ci je zoznam prazdny
	{
		*val= L->Last->data;		//predava hodnotu prveho prvku pomocou ukazatela val
	}
	else {
		DLError();
	}
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	tDLElemPtr elemPtr;
	if (L->First != NULL)				// test ci je zoznam prazdny
	{
		if (L->Act == L->First)  		//test ci je prvy prvok aktivny
		{
			L->Act = NULL;				//aktivita sa straca
		}
			elemPtr = L->First;
		if (L->First == L->Last)		//test ci je prvok jedinym prvkom zoznamu
		{
			L->First = NULL;
			L->Last = NULL;
		}
		else {
			L->First = L->First->rptr;		//nasledujuci prvok sa stava prvym prvkom 
			L->First->lptr = NULL;
		}
		free(elemPtr);				// uvolnuje sa byvaly prvy prvok
	}  							
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	tDLElemPtr elemPtr;
	if (L->First != NULL)   		//test ci je zoznam prazdny 
	{	
		if (L->Act == L->Last)  		//test ci je posledny prvok aktivny
		{
			L->Act = NULL;				//aktivita sa straca
		}
		elemPtr = L->Last;
		if (L->First == L->Last)		//test ci je prvok jedinym prvkom zoznamu
		{
			L->First = NULL;
			L->Last = NULL;
		}
		else {
			L->Last = L->Last->lptr;	//predposledny provk sa stava poslednym 
			L->Last->rptr = NULL;
		}
		free(elemPtr);			//uvolnuje sa byvaly posledny provk zoznamu
	}
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	if (L->Act != NULL){
		if (L->Act->rptr != NULL) 			//test ci je zoznam aktivny a ci je aktivny posledny prvok
		{
			tDLElemPtr elemPtr;							//pomocny ukazatel
			elemPtr = L->Act->rptr;						// pomocny ukazatel sa nastavi na prvok za aktivnym
			L->Act->rptr = elemPtr->rptr;
			if (elemPtr == L->Last)						//test ci je pomocny poslednym 
			{
				L->Last = L->Act;						//aktivita na posledny 
			}
			else {
				elemPtr->rptr->lptr = L->Act;			//aktivny prvok sa spaja s nasledujucim 
			}
			free(elemPtr);								//uvolnenie prvku
		}
	}
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	if (L->Act != NULL){
		if (L->Act->lptr != NULL)			//test ci je zoznam aktivny a ci je aktivny prvy prvok
		{
			tDLElemPtr elemPtr;								//pomocny ukazatel
			elemPtr = L->Act->lptr;							//pomocny ukazatel sa nastavy na prvok pred aktivnym
			L->Act->lptr = elemPtr->lptr;
			if (elemPtr == L->First)						//test ci pomocny prvok prvym
			{
				L->First = L->Act;							//aktivita na prvy
			}
			else {
				elemPtr->lptr->rptr = L->Act;				//aktivny prvok sa spaja s predchadzajucim
			}
			free(elemPtr);									//uvolnenie prvku
		}	
	}
}
void DLPostInsert (tDLList *L, TOKEN val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	if (L->Act != NULL)								//test ci je zoznam aktivny
	{
		struct tDLElem *newElemPtr = malloc(sizeof(struct tDLElem)); 	//alokacia noveho prvku
		if (newElemPtr == NULL)						//test ci sa malloc podaril
		{
			DLError();
		}
		else {
			newElemPtr->data = val; 
			newElemPtr->rptr = L->Act->rptr;		//spaja nasledujuci prvok s novym prvkom
			newElemPtr->lptr = L->Act;				//vklada novy prvok za aktivny prvok
			L->Act->rptr = newElemPtr;

			if (L->Act == L->Last)			//test ci je aktivny podleny prvok zoznamu
			{
				L->Last = newElemPtr;		//novy prvok sa stava poslednym
			}
		}
	}
}

void DLPreInsert (tDLList *L, TOKEN val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	if (L->Act != NULL)				//test ci je zoznam aktivny
	{
		struct tDLElem *newElemPtr = malloc(sizeof(struct tDLElem));  //alokacia noveho prvku
		if (newElemPtr == NULL)				//test ci sa malloc podaril
		{
			DLError();
		}
		else {
			if (L->Act == L->First)			//test ci je aktivny prvy prvok zoznamu
			{
				L->First = newElemPtr;		// novy prvok sa stava prvym
			}
			else{
				newElemPtr->lptr = L->Act->lptr;			//spaja predchadajuci prvok s novym prvokom
				L->Act->lptr->rptr = newElemPtr;			//spaja pravy pointer predchadzajuceho prvku s novym prvkom
			}
			newElemPtr->data = val; 
			newElemPtr->rptr = L->Act;						//spaja aktivny prvok s novym
			L->Act->lptr = newElemPtr;						//vklada novy prvok pred aktivny

		}
	}
}
	

void DLCopy (tDLList *L, TOKEN *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
	if (L->Act != NULL)						//test ci je zoznam aktinvy
	{
		*val = L->Act->data;				//predava hodnotu pomocou ukazatela
	}
	else {
		DLError();
	}		
}

void DLActualize (tDLList *L, TOKEN val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
	if (L->Act != NULL)					//test ci je zoznam aktivny
	{
		L->Act->data = val;				//prepise data ativneho prvku 
	}
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	if (L->Act != NULL)						//test ci je zoznam aktivny
	{
		if (L->Act == L->Last) {			//test ci je aktivny posledny prvok
			L->Act = NULL;				
		}
		else{
			L->Act = L->Act->rptr;			//aktivita na nasledujuci prvok
		}
	}
	
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
	if (L->Act != NULL)						//test ci je zoznam aktivny
	{
		if (L->Act == L->First) {			//test ci je aktivny prvy prvok
			L->Act = NULL;				
		}
		else{
			L->Act = L->Act->lptr;			// aktivita na predchadzajuci prvok
		}
	}	
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	return L->Act != NULL;		
}

/* Konec c206.c*/
