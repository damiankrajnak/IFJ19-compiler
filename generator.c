/* 
**	Part of IFJ Project 2019/2020
**	Author: Samuel Stuchly xstuch06
*/


/*
    --- INSTRUCTION SET --- 

10.4.1 Práce s rámci, volání funkcí

MOVE⟨var⟩ ⟨symb⟩    Přiřazení hodnoty do proměnné
Zkopíruje hodnotu⟨symb⟩do⟨var⟩.
Např.MOVE LF@par GF@varprovede zkopíro-vání hodnoty proměnnévarv globálním rámci do proměnnéparv lokálním rámci.

CREATEFRAME     Vytvoř nový dočasný rámec
Vytvoří nový dočasný rámec a zahodí případný obsah původního dočasného rámce.

PUSHFRAME   Přesun dočasného rámce na zásobník rámců
Přesuň TF na zásobník rámců. Rámec bude k dispozici přes LF a překryje původnírámce na zásobníku rámců.
TF bude po provedení instrukce nedefinován a je třeba jejpřed dalším použitím vytvořit pomocí CREATEFRAME. Pokus o přístup k nedefino-vanému rámci vede na chybu 55.

POPFRAME    Přesun aktuálního rámce do dočasného
Přesuň vrcholový rámec LF ze zásobníku rámců do TF. Pokud žádný rámec v LF neník dispozici, dojde k chybě 55.

DEFVAR⟨var⟩     Definuj novou proměnnou v rámci
Definuje proměnnou v určeném rámci dle⟨var⟩. Tato proměnná je zatím neinicializo-vaná a bez určení typu, který bude určen až přiřazením nějaké hodnoty.

CALL⟨label⟩     Skok na návěští s podporou návratu
Uloží inkrementovanou aktuální pozici z interního čítače instrukcí do zásobníku volánía provede skok na zadané návěští (případnou přípravu rámce musí zajistit jiné instrukce).

RETURN      Návrat na pozici uloženou instrukcí CALL        
Vyjme pozici ze zásobníku volání a skočí na tuto pozici nastavením interního čítačeinstrukcí (úklid lokálních rámců musí zajistit jiné instrukce).
Provedení instrukce připrázdném zásobníku volání vede na chybu 56.

    --------------------------------------------------------------------------------------------

10.4.2 Práce s datovým zásobníkem
Operační kód zásobníkových instrukcí je zakončen písmenem „S“.
Zásobníkové instrukcenačítají chybějící operandy z datového zásobníku a výslednou hodnotu operace ukládajízpět na datový zásobník.

PUSHS⟨symb⟩     Vlož hodnotu na vrchol datového zásobníku
Uloží hodnotu⟨symb⟩na datový zásobník.

POPS⟨var⟩       Vyjmi hodnotu z vrcholu datového zásobníku
Není-li zásobník prázdný, vyjme z něj hodnotu a uloží ji do proměnné⟨var⟩, jinak dojdek chybě 56.

CLEARS      Vymazání obsahu celého datového zásobníku
Pomocná instrukce, která smaže celý obsah datového zásobníku, aby neobsahoval za-pomenuté hodnoty z předchozích výpočtů.

    --------------------------------------------------------------------------------------------

10.4.3 Aritmetické, relační, booleovské a konverzní instrukce
V této sekci jsou popsány tříadresné i zásobníkové verze instrukcí pro klasické operace provýpočet výrazu. Zásobníkové verze instrukcí z datového zásobníku vybírají operandy sevstupními hodnotami dle popisu tříadresné instrukce od konce (tj. typicky nejprve⟨symb2⟩a poté⟨symb1⟩).

ADD⟨var⟩ ⟨symb1⟩ ⟨symb2⟩        Součet dvou číselných hodnot
Sečte⟨symb1⟩a⟨symb2⟩(musí být stejného číselného typu int nebo float) a výslednouhodnotu téhož typu uloží do proměnné⟨var⟩.

SUB⟨var⟩ ⟨symb1⟩ ⟨symb2⟩        Odečítání dvou číselných hodnot
Odečte⟨symb2⟩od⟨symb1⟩(musí být stejného číselného typu int nebo float) a výslednouhodnotu téhož typu uloží do proměnné⟨var⟩.

MUL⟨var⟩ ⟨symb1⟩ ⟨symb2⟩        Násobení dvou číselných hodnot
Vynásobí⟨symb1⟩a⟨symb2⟩(musí být stejného číselného typu int nebo float) a výsled-nou hodnotu téhož typu uloží do proměnné⟨var⟩.

DIV⟨var⟩ ⟨symb1⟩ ⟨symb2⟩        Dělení dvou desetinných hodnot
Podělí hodnotu ze⟨symb1⟩druhou hodnotou ze⟨symb2⟩(oba musí být typu float) avýsledek přiřadí do proměnné⟨var⟩(též typu float). Dělení nulou způsobí chybu 57.

IDIV⟨var⟩ ⟨symb1⟩ ⟨symb2⟩       Dělení dvou celočíselných hodnot
Celočíselně podělí hodnotu ze⟨symb1⟩druhou hodnotou ze⟨symb2⟩(musí být oba typuint) a výsledek přiřadí do proměnné⟨var⟩typu int. Dělení nulou způsobí chybu 57.

ADDS/SUBS/MULS/DIVS/IDIVS   Zásobníkové verze instrukcí ADD, SUB, MUL,DIV a IDIV

LT/GT/EQ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩       Relační operátory menší, větší, rovno
Instrukce vyhodnotí relační operátor mezi⟨symb1⟩a⟨symb2⟩(stejného typu; int, bool,float nebo string) a do booleovské proměnné⟨var⟩zapíše false při neplatnost nebo truev případě platnosti odpovídající relace. 
Řetězce jsou porovnávány lexikograficky a false je menší než true. Pro výpočet neostrých nerovností lze použít AND/OR/NOT. 
S ope-randem typu nil (druhý operand je libovolného typu) lze porovnávat pouze instrukcíEQ, jinak chyba 53.

LTS/GTS/EQS     Zásobníková verze instrukcí LT/GT/EQ

AND/OR/NOT⟨var⟩ ⟨symb1⟩ ⟨symb2⟩     Základní booleovské operátory
Aplikuje konjunkci (logické A)/disjunkci (logické NEBO) na operandy typu bool⟨symb1⟩a⟨symb2⟩nebo negaci na⟨symb1⟩(NOT má pouze 2 operandy) a výsledektypu bool zapíše do⟨var⟩.

ANDS/ORS/NOTS       Zásobníková verze instrukcí AND, OR a NOT

INT2FLOAT⟨var⟩ ⟨symb⟩       Převod celočíselné hodnoty na desetinnou
Převede celočíselnou hodnotu⟨symb⟩na desetinné číslo a uloží je do⟨var⟩.

FLOAT2INT⟨var⟩ ⟨symb⟩   Převod desetinné hodnoty na celočíselnou (oseknutí)
Převede desetinnou hodnotu⟨symb⟩na celočíselnou oseknutím desetinné části a uložíji do⟨var⟩.

INT2CHAR⟨var⟩ ⟨symb⟩        Převod celého čísla na znak
Číselná hodnota⟨symb⟩je dle ASCII převedena na znak, který tvoří jednoznakový ře-tězec přiřazený do⟨var⟩. Je-li⟨symb⟩mimo interval[0; 255], dojde k chybě 58.

STRI2INT⟨var⟩ ⟨symb1⟩ ⟨symb2⟩       Ordinální hodnota znaku
Do⟨var⟩uloží ordinální hodnotu znaku (dle ASCII) v řetězci⟨symb1⟩na pozici⟨symb2⟩(indexováno od nuly). Indexace mimo daný řetězec vede na chybu 58.

INT2FLOATS/FLOAT2INTS/INT2CHARS/STRI2INTS   Zásobníkové verze konverzních instrukcí

--------------------------------------------------------------------------------------------

10.4.4 Vstupně-výstupní instrukce

READ⟨var⟩ ⟨type⟩    Načtení hodnoty ze standardního vstupu
Načte jednu hodnotu dle zadaného typu⟨type⟩∈ {int, float, string, bool}(včetně případnékonverze vstupní hodnoty float při zadaném typu int) a uloží 
tuto hodnotu do proměnné⟨var⟩. Formát hodnot je kompatibilní s chováním vestavěných funkcíinputs,inputiainputfjazyka IFJ19.

WRITE⟨symb⟩     Výpis hodnoty na standardní výstup
Vypíše hodnotu⟨symb⟩na standardní výstup. Formát výpisu je kompatibilní s vestavě-ným příkazem print jazyka IFJ19
včetně výpisu desetinných čísel pomocí formátova-cího řetězce ”%a”.

--------------------------------------------------------------------------------------------

10.4.5 Práce s řetězci

CONCAT⟨var⟩ ⟨symb1⟩ ⟨symb2⟩     Konkatenace dvou řetězců
Do proměnné⟨var⟩uloží řetězec vzniklý konkatenací dvou řetězcových operandů⟨symb1⟩a⟨symb2⟩(jiné typy nejsou povoleny).

STRLEN⟨var⟩ ⟨symb⟩      Zjisti délku řetězce
Zjistí délku řetězce v⟨symb⟩a délka je uložena jako celé číslo do⟨var⟩.

GETCHAR⟨var⟩ ⟨symb1⟩ ⟨symb2⟩        Vrať znak řetězce
Do⟨var⟩uloží řetězec z jednoho znaku v řetězci⟨symb1⟩na pozici⟨symb2⟩(indexovánocelým číslem od nuly). Indexace mimo daný řetězec vede na chybu 58.

SETCHAR⟨var⟩ ⟨symb1⟩ ⟨symb2⟩        Změň znak řetězce
Zmodifikuje znak řetězce uloženého v proměnné⟨var⟩na pozici⟨symb1⟩(indexovánoceločíselně od nuly) na znak v řetězci⟨symb2⟩(první znak, pokud obsahuje⟨symb2⟩více znaků). Výsledný řetězec je opět uložen do⟨var⟩. Při indexaci mimo řetězec⟨var⟩nebo v případě prázdného řetězce v⟨symb2⟩dojde k chybě 58.

--------------------------------------------------------------------------------------------

10.4.6 Práce s typy

TYPE⟨var⟩ ⟨symb⟩        Zjisti typ daného symbolu
Dynamicky zjistí typ symbolu⟨symb⟩a do⟨var⟩zapíše řetězec značící tento typ (int,bool, float, string nebo nil).
Je-li⟨symb⟩neinicializovaná proměnná, označí její typprázdným řetězcem.

--------------------------------------------------------------------------------------------

10.4.7 Instrukce pro řízení toku programu
Neterminál⟨label⟩označuje návěští, které slouží pro označení pozice v kódu IFJcode19.V případě skoku na neexistující návěští dojde k chybě 52.

LABEL⟨label⟩        Definice návěští
Speciální instrukce označující pomocí návěští⟨label⟩důležitou pozici v kódu jako po-tenciální cíl libovolné skokové instrukce. Pokus o redefinici existujícího návěští je chy-bou 52.

JUMP⟨label⟩     Nepodmíněný skok na návěští
Provede nepodmíněný skok na zadané návěští⟨label⟩.

JUMPIFEQ⟨label⟩ ⟨symb1⟩ ⟨symb2⟩     Podmíněný skok na návěští při rovnosti
Pokud jsou⟨symb1⟩a⟨symb2⟩stejného typu nebo je některý operand nil (jinak chyba53) a zároveň se jejich hodnoty rovnají, tak provede skok na návěští⟨label⟩.

JUMPIFNEQ⟨label⟩ ⟨symb1⟩ ⟨symb2⟩        Podmíněný skok na návěští při nerovnosti
Jsou-li⟨symb1⟩a⟨symb2⟩stejného typu nebo je některý operand nil (jinak chyba 53),ale různé hodnoty, tak provede skok na návěští⟨label⟩.

JUMPIFEQS/JUMPIFNEQS⟨label⟩     Zásobníková verze JUMPIFEQ, JUMPIFNEQ
Zásobníkové skokové instrukce mají i jeden operand mimo datový zásobník, a to návěští⟨label⟩, na které se případně provede skok.

EXIT⟨symb⟩      Ukončení interpretace s návratovým kódem
Ukončí vykonávání programu a ukončí interpret s návratovou chybou⟨symb⟩, kde⟨symb⟩je celé číslo v intervalu 0 až 49 (včetně). 
Nevalidní celočíselná hodnota⟨symb⟩vede na chybu 57.

--------------------------------------------------------------------------------------------

10.4.8 Ladicí instrukce

BREAK       Výpis stavu interpretu nastderr
Na standardní chybový výstup (stderr) vypíše stav interpretu v danou chvíli (tj. běhemvykonávání této instrukce).
Stav se mimo jiné skládá z pozice v kódu, výpisu globálního,aktuálního lokálního a dočasného rámce a počtu již vykonaných instrukcí.

DPRINT⟨symb⟩        Výpis hodnoty nastderr
Vypíše zadanou hodnotu⟨symb⟩na standardní chybový výstup (stderr). Výpisy toutoinstrukcí bude možné vypnout pomocí volby interpretu (viz nápověda interpretu).

--------------------------------------------------------------------------------------------
*/


#include "generator.h"
#include "main.h"
#include "linked_list.h"


tList output_list;
tDLList zoznam;

tBSTNodePtrLocal  GFDefinedVarsTree ;
tBSTNodePtrLocal  LFDefinedVarsTree ;


int scope_now = 0;
bool allowed_def = true;



// ------------- writing output ------------- //
void generate_string(char * instruction_string){
    
    PostInsert(&output_list,instruction_string); 
    Succ(&output_list);


}

void generate_instruction(char * instruction){
    generate_string(instruction);
}


void generate_operand(char * operand){
    generate_string(" ");
    generate_string(operand);
    
}

void generate_newline(){
    generate_string("\n");
}


// --------- ZERO OPERAND --------

void generate_0op(char* inst){
    generate_instruction(inst);
    generate_newline();
}

// --------- ONE OPERAND --------

void generate_1opV(char* inst, char* var){
    if (is_var(var)){
    generate_instruction(inst);
    generate_operand(var);
    generate_newline();
    }
    else
    {
        fprintf(stderr, "INCORRECT FORMAT OF PARAMTERS OF INSTRUCTION in 1opV");
        exit(4);  // TODO FIX RETURN VALUE bud 4 abo 6 STILL UNDECIDED !!!!!!!!
    }
}

void generate_1opL(char* inst,char* label){
    if (is_label(label)){
    generate_instruction(inst);
    generate_operand(label);
    generate_newline();
    }
    else
    {
        fprintf(stderr, "INCORRECT FORMAT OF PARAMTERS OF INSTRUCTION in 1opL");
        exit(4);  // TODO FIX RETURN VALUE bud 4 abo 6 STILL UNDECIDED !!!!!!!!
    }
}

void generate_1opS(char* inst,char* symb){
    if (is_symb(symb)){
    generate_instruction(inst);
    generate_operand(symb);
    generate_newline();
    }
    else
    {
        fprintf(stderr, "INCORRECT FORMAT OF PARAMTERS OF INSTRUCTION in 1opS");
        exit(4);  // TODO FIX RETURN VALUE bud 4 abo 6 STILL UNDECIDED !!!!!!!!
    }
}

// --------- TWO OPERAND --------

void generate_2opVS(char* inst,char* var,char * symb){
    if (is_var(var) && is_symb(symb)){
    generate_instruction(inst);
    generate_operand(var);
    generate_operand(symb);
    generate_newline();
    }
    else
    {
        fprintf(stderr, "INCORRECT FORMAT OF PARAMTERS OF INSTRUCTION 2opVS");
        exit(4);  // TODO FIX RETURN VALUE bud 4 abo 6 STILL UNDECIDED !!!!!!!!
    }
}


void generate_2opVT(char* inst,char* var,char * type){
    if (is_var(var) && is_type(type)){
    generate_instruction(inst);
    generate_operand(var);
    generate_operand(type);
    generate_newline();
    }
    else
    {
        fprintf(stderr, "INCORRECT FORMAT OF PARAMTERS OF INSTRUCTION in 2opVT");
        exit(4);  // TODO FIX RETURN VALUE bud 4 abo 6 STILL UNDECIDED !!!!!!!!
    }
}

// --------- THREE OPERAND --------

void generate_3opVSS(char* inst,char* var,char *symb1, char* symb2){
    if (is_var(var) && is_symb(symb1) && is_symb(symb2)){
    generate_instruction(inst);
    generate_operand(var);
    generate_operand(symb1);
    generate_operand(symb2);
    generate_newline();
    }
    else
    {
        fprintf(stderr, "INCORRECT FORMAT OF PARAMTERS OF INSTRUCTION 3opVSS");
        exit(4);  // TODO FIX RETURN VALUE bud 4 abo 6 STILL UNDECIDED !!!!!!!!
    }
}

void generate_3opLSS(char* inst,char* label,char *symb1, char* symb2){
    if (is_label(label) && is_symb(symb1) && is_symb(symb2)){
    generate_instruction(inst);
    generate_operand(label);
    generate_operand(symb1);
    generate_operand(symb2);
    generate_newline();
    }
    else
    {
        fprintf(stderr, "INCORRECT FORMAT OF PARAMTERS OF INSTRUCTION in 3opLSS");
        exit(4);  // TODO FIX RETURN VALUE bud 4 abo 6 STILL UNDECIDED !!!!!!!!
    }
    
}

// ========================================== //

// ---------- FORMAT CHECK ------------------ //




bool is_var (char * var){
    if(strncmp(var,"LF@",3) == 0 ){
        return true;
    }
    else if (strncmp(var,"GF@",3) == 0){
        return true;
    }
    else if (strncmp(var,"TF@",3) == 0)
    {   
        return true;
    }
    else
    {
        return false;
    }
    
}


bool is_symb(char * symb){
    if (is_var(symb) || is_const(symb)){
        return true;
    }
    else{
        return false;
    }
}

// TODO
/*
bool is_const(char * konst){
    char *c;
    c = konst + 0;
    for(int i = 1; *c != '\0' ;i++){    
        if(*c < 32){      //  TODO SPYTAT SA SIMONA CO NEMOZE BYT V KONSTATNE
            // ’\"’, ’\'’, ’\n’, ’\t’, ’\\'  these are fine thorugh escape sequences
            switch (*c)
            {
            case '\n':
            case '\t':
                break;
            
            default:
                return false;
            }
            
        }
        c = konst + i;
    }
     return true;
}
*/


bool is_const(char * konst){
    if(strncmp(konst,"string@",7) == 0 ){
        return true;
    }
    else if (strncmp(konst,"float@",6) == 0){
        return true;
    }
    else if (strncmp(konst,"int@",4) == 0)
    {   
        return true;
    }
    else if (strncmp(konst,"bool@",5) == 0)
    {   
        return true;
    }
    else if (strncmp(konst,"nil@nil",7) == 0)
    {   
        return true;
    }
    else
    {
        return false;
    }
    
}

bool is_label(char * label){
    if (!is_var(label)){
        if(strncmp(label,"$",1) == 0 ){
        return true;
        }
    }
    return false;
}
// nil is not acceptable 
bool is_type(char *type){
    if(strcmp(type,"bool") == 0 ){
        return true;
    }
    else if (strcmp(type,"float") == 0){
        return true;
    }
    else if (strcmp(type,"int") == 0)
    {   
        return true;
    }
    else if (strcmp(type,"string") == 0)
    {   
        return true;
    }
    else
    {
        return false;
    }
}

/* checks if function has correct number of parameters.  // TODO damian toot robi ?? 

void check_params(){

}
*/
// ------------------------------------------ //


// ======================== BUILT IN FUNCTIONS ========================= // 


/*
Vestavěné funkce ze standardního vstupu načtou jeden řádek ukončený odřádková-ním.
Funkceinputstento řetězec vrátí bez symbolu konce řádku (načítaný řetězecnepodporuje escape sekvence).
V případěinputiainputfjsou okolní bílé znakyignorovány.
Jakýkoli jiný nevhodný znak je známkou špatného formátu.
Funkcein-putinačítá a vrací celé číslo,inputfdesetinné číslo.
Obě funkce podporují i načí-tání hexadecimálního zápisu čísla (např.0x1FA3nebo0x1F.F1p-1, kde je šest-náctková soustava detekována podřetězci0xap).
V případě chybějící hodnoty navstupu nebo jejího špatného formátu bude výsledkem hodnotaNone
*/

// ======================== INPUTS() ========================= // 

// TODO: these functions might not work perfect -- need testing !!
// asi bude treba pridat typove kontroly atd 
void gen_inputs(){
    generate_1opL("LABEL","$inputs");
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    
    // this is hopefully enough 
    generate_2opVT("READ","LF@%retval","string");
    end_def_func();
}


// ======================== INPUTI() ========================= // 
void gen_inputi(){

    generate_1opL("LABEL","$inputi");
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    // this is hopefully enough  and tkaes care of None retunr and format check
    generate_2opVT("READ","LF@%retval","int");
    end_def_func();
}



// ======================== INPUTF() ========================= // 
void gen_inputf(){

    generate_1opL("LABEL","$inputf");
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    // this is hopefully enough 
    generate_2opVT("READ","LF@%retval","float");
    end_def_func();
}



// ======================== LEN(s) ========================= // 
//done
// check type for function len(s)
void check_for_len(char* s_param){
    char type_string[VAR_LEN] ="";
    char tmp_string[VAR_LEN] = "";
    char var[VAR_LEN] = "";
    char *var_string = "LF@";
    char *type_end = "$type";
    char *tmp_end = "$tmp";

    strcat(type_string,var_string);
    strcat(type_string,s_param);
    strcat(type_string,type_end);   // type_strng == LF@{param_name}$type

    strcat(tmp_string,var_string);
    strcat(tmp_string,s_param);
    strcat(tmp_string,tmp_end);     // tmp_strng == LF@{param_name}$tmp
    generate_1opV("DEFVAR",type_string);
    //printf("THIS IS TYPESTRING==================================================================== %s",type_string);
    generate_1opV("DEFVAR",tmp_string);

    strcat(var,var_string);
    strcat(var,s_param);

    generate_2opVS("TYPE",type_string,var);
    generate_2opVS("MOVE",tmp_string,var);

    generate_3opLSS("JUMPIFEQ","$len$is$string",type_string,"string@string");

    //generate_1opL("LABEL","$len$error");
    generate_1opS("EXIT","int@4");

    generate_1opL("LABEL","$len$is$string");
    generate_2opVS("STRLEN","LF@%retval",tmp_string);

}


// built in function len(s)
void gen_len(){
    /*
    int num_of_params = 1;  
    char *param_list[num_of_params]; //maybe malloc TODO
    def_func_gen("len",num_of_params,param_list);
    */
    generate_1opL("LABEL","$len");
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    generate_1opV("DEFVAR","LF@%Param_s");
    generate_2opVS("MOVE","LF@%Param_s","LF@%$1");

    check_for_len("%Param_s");
    end_def_func();

}


// ======================== SUBSTR(s,i,n) ========================= // 
//  done
void check_for_substr(char * s_param, char * i_param,char * n_param){

    
    char s_type_string[VAR_LEN] ="";
    char s_tmp_string[VAR_LEN] = "";
    char s_var[VAR_LEN] = "";

    char i_type_string[VAR_LEN] ="";
    char i_tmp_string[VAR_LEN] = "";
    char i_var[VAR_LEN] = "";

    char n_type_string[VAR_LEN] ="";
    char n_tmp_string[VAR_LEN] = "";
    char n_var[VAR_LEN] = "";

    char *var_string = "LF@";
    char *type_end = "$type";
    char *tmp_end = "$tmp";

    // s_param
    strcat(s_type_string,var_string);
    strcat(s_type_string,s_param);
    strcat(s_type_string,type_end);  

    strcat(s_tmp_string,var_string);
    strcat(s_tmp_string,s_param);
    strcat(s_tmp_string,tmp_end);     

    generate_1opV("DEFVAR",s_type_string);
    generate_1opV("DEFVAR",s_tmp_string);

    strcat(s_var,var_string);
    strcat(s_var,s_param);

    generate_2opVS("TYPE",s_type_string,s_var);
    generate_2opVS("MOVE",s_tmp_string,s_var);

    // i_param
    strcat(i_type_string,var_string);
    strcat(i_type_string,i_param);
    strcat(i_type_string,type_end);  

    strcat(i_tmp_string,var_string);
    strcat(i_tmp_string,i_param);
    strcat(i_tmp_string,tmp_end);    

    generate_1opV("DEFVAR",i_type_string);
    generate_1opV("DEFVAR",i_tmp_string);

    strcat(i_var,var_string);
    strcat(i_var,i_param);

    generate_2opVS("TYPE",i_type_string,i_var);
    generate_2opVS("MOVE",i_tmp_string,i_var);

    // n_param
    strcat(n_type_string,var_string);
    strcat(n_type_string,n_param);
    strcat(n_type_string,type_end);  

    strcat(n_tmp_string,var_string);
    strcat(n_tmp_string,n_param);
    strcat(n_tmp_string,tmp_end);     

    generate_1opV("DEFVAR",n_type_string);
    generate_1opV("DEFVAR",n_tmp_string);

    strcat(n_var,var_string);
    strcat(n_var,n_param);

    generate_2opVS("TYPE",n_type_string,n_var);
    generate_2opVS("MOVE",n_tmp_string,n_var);



    // check types
    generate_3opLSS("JUMPIFEQ","$substr$s$is$string",s_type_string,"string@string");

    generate_1opL("LABEL","$substr$error");
    generate_1opS("EXIT","int@4");

    generate_1opL("LABEL","$substr$s$is$string");
    
    generate_3opLSS("JUMPIFEQ","$substr$i$is$int",i_type_string,"string@int");
    
    generate_3opLSS("JUMPIFEQ","$substr$i$is$float",i_type_string,"string@float");
    generate_1opL("JUMP","$substr$error");

    generate_1opL("LABEL","$substr$i$is$int");
    generate_1opL("JUMP","$substr$n$check");

    generate_1opL("LABEL","$substr$i$is$float");
    generate_2opVS("FLOAT2INT",i_tmp_string,i_var);
    
    generate_1opL("LABEL","$substr$n$check");
    
    generate_3opLSS("JUMPIFEQ","$substr$n$is$int",n_type_string,"string@int");
    
    generate_3opLSS("JUMPIFEQ","$substr$n$is$float",n_type_string,"string@float");
    generate_1opL("JUMP","$substr$error");

    generate_1opL("LABEL","$substr$n$is$int");
    generate_1opL("JUMP","$substr$value$check");

    generate_1opL("LABEL","$substr$n$is$float");
    generate_2opVS("FLOAT2INT",n_tmp_string,n_var);

    generate_1opL("LABEL","$substr$value$check");

    generate_1opV("DEFVAR","LF@$substr$help$bool");
    generate_2opVS("MOVE","LF@$substr$help$bool","bool@false");

    generate_3opVSS("LT","LF@$substr$help$bool",i_tmp_string,"int@0");
    generate_3opLSS("JUMPIFEQ","$substr$return$nil","LF@$substr$help$bool","bool@true"); // if less then 0  => return NONE
    // var for len(s)
    generate_1opV("DEFVAR","LF@$substr$help$int");
    
    // len(s)
    generate_2opVS("STRLEN","LF@$substr$help$int",s_tmp_string);
    
    generate_3opVSS("GT","LF@$substr$help$bool",i_tmp_string,"LF@$substr$help$int"); 
    generate_3opLSS("JUMPIFEQ","$substr$return$nil","LF@$substr$help$bool","bool@true"); // if more than len(s) => return None
    
    generate_3opVSS("LT","LF@$substr$help$bool",n_tmp_string,"int@0");
    generate_3opLSS("JUMPIFEQ","$substr$return$nil","LF@$substr$help$bool","bool@true"); // if less then 0  => return NONE
    
    // len(s) - i
    generate_1opV("DEFVAR","LF@$substr$help$int$minus$i");
    generate_3opVSS("SUB","LF@$substr$help$int$minus$i","LF@$substr$help$int",i_tmp_string);

    generate_3opVSS("GT","LF@$substr$help$bool",n_tmp_string,"LF@$substr$help$int"); 
    generate_3opLSS("JUMPIFEQ","$substr$return$all$from$i","LF@$substr$help$bool","bool@true"); // if n > (len(s) -1) => return all from i 

    // normal
    generate_1opV("DEFVAR","LF@$substr$char");
    generate_1opV("DEFVAR","LF@$substr$string");
    generate_2opVS("MOVE","LF@$substr$string","string@");

    generate_1opV("DEFVAR","LF@$substr$index");
    generate_2opVS("MOVE","LF@$substr$index",i_tmp_string);

    generate_1opV("DEFVAR","LF@$substr$counter");
    generate_2opVS("MOVE","LF@$substr$counter","int@0");
    // loop
    generate_1opL("LABEL","$substr$loop$normal");
    generate_3opVSS("GETCHAR","LF@$substr$char",s_tmp_string,"LF@$substr$index");
    // string = string + char 
    generate_3opVSS("CONCAT","LF@$substr$string","LF@$substr$string","LF@$substr$char");

    generate_3opVSS("ADD","LF@$substr$index","LF@$substr$index","int@1"); // index ++
    generate_3opVSS("ADD","LF@$substr$counter","LF@$substr$counter","int@1"); // counter ++

    generate_3opLSS("JUMPIFNEQ","$substr$loop$normal","LF@$substr$counter",n_tmp_string); // counter != n 

    generate_1opL("JUMP","$substr$end");
    

    //return all 
    generate_1opL("LABEL","$substr$return$all$from$i");
    
    generate_1opV("DEFVAR","LF@$substr$char");
    generate_1opV("DEFVAR","LF@$substr$string");
    generate_2opVS("MOVE","LF@$substr$string","string@");

    generate_1opV("DEFVAR","LF@$substr$index");
    generate_2opVS("MOVE","LF@$substr$index",i_tmp_string);

    // loop
    generate_1opL("LABEL","$substr$loop$special");
    generate_3opVSS("GETCHAR","LF@$substr$char",s_tmp_string,"LF@$substr$index");
    // string = string + char 
    generate_3opVSS("CONCAT","LF@$substr$string","LF@$substr$string","LF@$substr$char");

    generate_3opVSS("ADD","LF@$substr$index","LF@$substr$index","int@1"); // index ++

    generate_3opLSS("JUMPIFNEQ","$substr$loop$special","LF@$substr$index","LF@$substr$help$int"); // index != len(s)
    generate_1opL("JUMP","$substr$end");


    generate_1opL("LABEL","$substr$return$nil");
    generate_2opVS("MOVE","LF@retval","nil@nil");

    generate_1opL("LABEL","$substr$end");
}



void gen_substr(){
    /*
    int num_of_params = 3;
    char *param_list[num_of_params]; //maybe malloc TODO
    def_func_gen("substr",num_of_params,param_list);

*/
    generate_1opL("LABEL","$substr");
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    generate_1opV("DEFVAR","LF@%Param_s");
    generate_2opVS("MOVE","LF@%Param_s","LF@%$1");
    generate_1opV("DEFVAR","LF@%Param_i");
    generate_2opVS("MOVE","LF@%Param_i","LF@%$2");
    generate_1opV("DEFVAR","LF@%Param_n");
    generate_2opVS("MOVE","LF@%Param_n","LF@%$3");

    check_for_substr("%Param_s","%Param_i","%Param_n");
    end_def_func();
}
    

// ======================== ORD(s,i) ========================= // 
//done
void check_for_ord(char * s_param, char * i_param){
    
    char s_type_string[VAR_LEN] ="";
    char s_tmp_string[VAR_LEN] = "";
    char s_var[VAR_LEN] = "";

    char i_type_string[VAR_LEN] ="";
    char i_tmp_string[VAR_LEN] = "";
    char i_var[VAR_LEN] = "";

    char *var_string = "LF@";
    char *type_end = "$type";
    char *tmp_end = "$tmp";

    // s_param
    strcat(s_type_string,var_string);
    strcat(s_type_string,s_param);
    strcat(s_type_string,type_end);  

    strcat(s_tmp_string,var_string);
    strcat(s_tmp_string,s_param);
    strcat(s_tmp_string,tmp_end);     

    generate_1opV("DEFVAR",s_type_string);
    generate_1opV("DEFVAR",s_tmp_string);

    strcat(s_var,var_string);
    strcat(s_var,s_param);

    generate_2opVS("TYPE",s_type_string,s_var);
    generate_2opVS("MOVE",s_tmp_string,s_var);

    // i_param
    strcat(i_type_string,var_string);
    strcat(i_type_string,i_param);
    strcat(i_type_string,type_end);  

    strcat(i_tmp_string,var_string);
    strcat(i_tmp_string,i_param);
    strcat(i_tmp_string,tmp_end);    

    generate_1opV("DEFVAR",i_type_string);
    generate_1opV("DEFVAR",i_tmp_string);

    strcat(i_var,var_string);
    strcat(i_var,i_param);

    generate_2opVS("TYPE",i_type_string,i_var);
    generate_2opVS("MOVE",i_tmp_string,i_var);

    // check types
    generate_3opLSS("JUMPIFEQ","$ord$s$is$string",s_type_string,"string@string");

    generate_1opL("LABEL","$ord$error");
    generate_1opS("EXIT","int@4");

    generate_1opL("LABEL","$ord$s$is$string");

    generate_3opLSS("JUMPIFEQ","$ord$i$is$int",i_type_string,"string@int");

    generate_3opLSS("JUMPIFEQ","$ord$i$is$float",i_type_string,"string@float");
    generate_1opL("JUMP","$ord$error");

    generate_1opL("LABEL","$ord$i$is$int");
    generate_1opL("JUMP","$ord$value$check");

    generate_1opL("LABEL","$ord$i$is$float");
    generate_2opVS("FLOAT2INT",i_tmp_string,i_var);

    generate_1opL("LABEL","$ord$value$check");
    generate_1opV("DEFVAR","LF@$ord$help$bool");
    generate_2opVS("MOVE","LF@$ord$help$bool","bool@false");

    generate_3opVSS("LT","LF@$ord$help$bool",i_tmp_string,"int@0");
    generate_3opLSS("JUMPIFEQ","$ord$return$nil","LF@$ord$help$bool","bool@true"); // if less then 0  => error
    // var for len(s)
    generate_1opV("DEFVAR","LF@$ord$help$int");

    // len(s)
    generate_2opVS("STRLEN","LF@$ord$help$int",s_tmp_string);

    // len(s) - 1
    generate_3opVSS("SUB","LF@$ord$help$int","LF@$ord$help$int","int@1");

    generate_3opVSS("GT","LF@$ord$help$bool",i_tmp_string,"LF@$ord$help$int");  
    generate_3opLSS("JUMPIFEQ","$ord$return$nil","LF@$ord$help$bool","bool@true"); // if more than 255 => error
    generate_1opL("JUMP","$ord$normal");

    generate_1opL("LABEL","$ord$return$nil");
    generate_2opVS("MOVE","LF@retval","nil@nil");
    generate_1opL("JUMP","$ord$end");
    
    generate_1opL("LABEL","$ord$normal");
    generate_3opVSS("STRI2INT","LF@%retval",s_tmp_string,i_tmp_string);

    generate_1opL("LABEL","$ord$end");

}

void gen_ord(){

    /*
    int num_of_params = 2;
    char *param_list[num_of_params]; //maybe malloc TODO
    def_func_gen("ord",num_of_params,param_list);

*/
    generate_1opL("LABEL","$ord");
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    generate_1opV("DEFVAR","LF@%sparam");
    generate_2opVS("MOVE","LF@%sparam","LF@%$1");
    generate_1opV("DEFVAR","LF@%iparam");
    generate_2opVS("MOVE","LF@%iparam","LF@%$2");

    check_for_ord("%sparam","%iparam");
    end_def_func();
}


// ======================== CHR(i) ========================= // 

// done example of correct way 
const char * check_for_chr(char * i_param){
    char type_string[VAR_LEN] ="";
    char tmp_string[VAR_LEN] = "";
    char var[VAR_LEN] = "";
    char *var_string = "LF@";
    char *type_end = "$type";
    char *tmp_end = "$tmp";

    strcat(type_string,var_string);
    strcat(type_string,i_param);
    strcat(type_string,type_end);   // type_strng == LF@{param_name}$type

    strcat(tmp_string,var_string);
    strcat(tmp_string,i_param);
    strcat(tmp_string,tmp_end);     // tmp_strng == LF@{param_name}$tmp
    generate_1opV("DEFVAR",type_string);
    generate_1opV("DEFVAR",tmp_string);

    strcat(var,var_string);
    strcat(var,i_param);

    generate_2opVS("TYPE",type_string,var);
    generate_2opVS("MOVE",tmp_string,var);

    
    generate_3opLSS("JUMPIFEQ","$chr$is$int",type_string,"string@int");
    
    generate_3opLSS("JUMPIFEQ","$chr$is$float",type_string,"string@float");

    generate_1opL("LABEL","$chr$error");
    generate_1opS("EXIT","int@4");


    generate_1opL("LABEL","$chr$is$int");
    generate_1opL("JUMP","$chr$value$check");

    generate_1opL("LABEL","$chr$is$float");
    generate_2opVS("FLOAT2INT",tmp_string,var);

    generate_1opL("LABEL","$chr$value$check");
    generate_1opV("DEFVAR","LF@$chr$help$bool");
    generate_2opVS("MOVE","LF@$chr$help$bool","bool@false");
    generate_3opVSS("LT","LF@$chr$help$bool",tmp_string,"int@0");
    generate_3opLSS("JUMPIFEQ","$chr$error","LF@$chr$help$bool","bool@true"); // if less then 0  => error
    generate_3opVSS("GT","LF@$chr$help$bool",tmp_string,"int@255");  
    generate_3opLSS("JUMPIFEQ","$chr$error","LF@$chr$help$bool","bool@true"); // if more than 255 => error
    const char *help = tmp_string;
    return help;
}

void gen_chr(){

    generate_1opL("LABEL","$chr");
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    generate_1opV("DEFVAR","LF@%i_param");
    generate_2opVS("MOVE","LF@%i_param","LF@%$1");

    const char ret_val[VAR_LEN];
    sprintf(ret_val,"%s",check_for_chr("%i_param"));
    generate_2opVS("INT2CHAR","LF@%retval",ret_val); 
    end_def_func();
}

// ========================================================================================== //

void def_built_in(){
    gen_inputs();
    gen_inputi();
    gen_inputf();
    gen_len();
    gen_substr();
    gen_ord();
    gen_chr();
}

void generate_start(){
    InsertFirst(&output_list,"INIT");
    First(&output_list);
    generate_string(".IFJcode19");
    generate_newline();
    generate_1opL("JUMP","$$main");
    def_built_in(); //generate built in functions definitions
    generate_1opL("LABEL","$$main");
    BSTInitLocal(&GFDefinedVarsTree); // initialize a tree to remember what vars i defined already in assembler
    BSTInsertLocal(&GFDefinedVarsTree,"INITGB");
    //printf("V STOME JE INIT : %d", BSTSearchLocal(GFDefinedVarsTree,"INIT"));
}

/*

var = d + ( a + b ) / ( c + a )  - 3 * x

E -> i      //  d
E ->i       //  a
E -> i      //  b
E -> E + E  //  a+b = var1
E -> (E)    
E -> i      //  c
E -> i      //  a
E -> E + E  //  c+a = var2
E -> (E)
E -> E / E  //  var3 = var1/var2
E -> i      //  3
E -> i      //  x
E -> E * E  //  3 *x = var4
E -> E - E  // var3 - var4 = var5
E -> E + E  // var = d + var5

*/



//done
void gen_expression(){
    static int expression_id;
    char str[10]; // yes i support giant programs
    sprintf(str, "%d", expression_id);
    
     char  name1[VAR_LEN] = "";
    char  name2 [VAR_LEN]= "";
    char  name1_type[VAR_LEN] = "";
    char  name2_type [VAR_LEN]= "";
    char  helper_val [VAR_LEN]= "";
    
    if (scope_now == 0){
        strcat(name1,"GF@$%");
        strcat(name2,"GF@$%");
        strcat(name1_type,"GF@$%");
        strcat(name2_type,"GF@$%");
        strcat(helper_val,"GF@$%");
        
        
    }
    else
    {
        strcat(name1,"LF@$%");
        strcat(name2,"LF@$%");
        strcat(name1_type,"LF@$%");
        strcat(name2_type,"LF@$%");
        strcat(helper_val,"LF@$%");
        
    }
    strcat(name1,str);
    strcat(name2,str);
    strcat(name1,"$helper%1");
    strcat(name2,"$helper%2");
    strcat(name1_type,str);
    strcat(name2_type,str);
    strcat(name1_type,"$helper%1$type");
    strcat(name2_type,"$helper%2$type");
    strcat(helper_val,str);
    strcat(helper_val,"$expr$helper$val");
 

    generate_1opV("DEFVAR",name1);
    generate_1opV("DEFVAR",name2);

    generate_1opV("DEFVAR",name1_type);
    generate_1opV("DEFVAR",name2_type);

    generate_1opV("DEFVAR",helper_val);


    TOKEN token;

    if (&(*zoznam.Act) != &(*zoznam.Last) ) {
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
    }
    if (*token.lex == '\n'){
        return;
    }
     DLPred(&zoznam);
     DLCopy(&zoznam,&token);

    char str2[10] = "";
    // tTODO GET lenghts of rule array 
    for(int i=0; i < RULE_ARRAY_LEN; i++){
        char c = rule_array[expression_id][i];
        if (c == 0){
            break;
        }
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);

        sprintf(str2, "%d", i);
        strcat(str,str2);

        
        // TOOD MUSI TU BYT VELKOST V TYCHTO POLIACH ZADANA INAK RIP !!!
        char same_type_label[LABEL_LEN] = "";
        char first_is_int_label[LABEL_LEN] = "";
        char error_label[LABEL_LEN] = "";
        char add_label[LABEL_LEN] = "";
        char end_label[LABEL_LEN] = "";
        char division_by_zero_label[LABEL_LEN] = "";

        strcat(same_type_label,"$add$same$type$label$%");
        strcat(same_type_label,str);
        strcat(first_is_int_label,"$add$is$int$label$%");
        strcat(first_is_int_label,str);
        strcat(error_label,"$add$error$label$%");
        strcat(error_label,str);
        strcat(add_label,"$add$add$label$%");
        strcat(add_label,str);
        strcat(end_label,"$add$end$label$%");
        strcat(end_label,str);
        strcat(division_by_zero_label,"$dev$by$zero$label$%");
        strcat(division_by_zero_label,str);
        
        sprintf(str,"%d",expression_id);
    

        const char * help;
        char  complete_var[VAR_LEN] = "";

        switch (c)
        {
            case R_PLUS:
                
                
                generate_1opV("POPS",name2);        // order of vars doesnt matter in addition
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                // not bool or nil 
                generate_1opL("LABEL",add_label);
                generate_3opVSS("ADD",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);

                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                break;

            case R_MINUS:


                generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                //not nill 
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); // jump na chybu ak je to string

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("SUB",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);

                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                break;

            case R_MUL:
              
                generate_1opV("POPS",name2);        // order does not matter here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                //not nill 
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); // jump na chybu ak je to string

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("MUL",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);

                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                
                break;

            case R_DIV:
                // BOTH MUST BE FLAOT
                generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // NOT SAME TYPE
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // SAME TYPE
                generate_1opL("LABEL",same_type_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                //not nill 
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); // jump na chybu ak je to string

                // not bool or nil or string
                generate_3opLSS("JUMPIFEQ",add_label,name1_type,"string@float"); // jump na add if both float
                // both are int 
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted

                generate_1opL("LABEL",add_label);
                
                generate_3opLSS("JUMPIFEQ",division_by_zero_label,name2,"float@0x0p+0"); // jump if devision by 0
                
                generate_3opVSS("DIV",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);

                // error division by 0 
                generate_1opL("LABEL",division_by_zero_label);
                generate_1opS("EXIT","int@9");

                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                break;

            case R_IDIV: 
            // BOTH MUST BE INTEGER // page 8 section 5 in assignemnt states that only INT2FLOAT can be done no other conversion.
                generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@float"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@float");   // jump na chybu ak je to float

                // both are int 
                generate_1opL("JUMP",add_label);
                generate_3opLSS("JUMPIFEQ",division_by_zero_label,name2,"int@0"); // jump if devision by 0
                generate_3opVSS("IDIV",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);

                generate_1opL("JUMP",end_label);

                 // error division by 0 
                generate_1opL("LABEL",division_by_zero_label);
                generate_1opS("EXIT","int@9");
                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                break;
            
            case R_LESS:
               generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                // WIHTOUT BOOLOP EXTENTION , BOOLS CANNOT BE COMPARED
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                //not nill 

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("LT",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);

                

                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);

                break;
            
            case R_MORE:
             generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                // WIHTOUT BOOLOP EXTENTION , BOOLS CANNOT BE COMPARED
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                //not nill 

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("GT",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);


                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                break;
            
            case R_EQUAL:
             generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                // WIHTOUT BOOLOP EXTENTION , BOOLS CANNOT BE COMPARED
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                
                // nill is allowed

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("EQ",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);


                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("PUSHS","bool@false");

                generate_1opL("LABEL",end_label);
                break;
            
            case R_NEQUAL:
             generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                // WIHTOUT BOOLOP EXTENTION , BOOLS CANNOT BE COMPARED
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                
                // nill is allowed

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("EQ",helper_val,name1,name2);
                generate_2opVS("NOT",helper_val,helper_val);
                generate_1opS("PUSHS",helper_val);
                generate_1opL("JUMP",end_label);


                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("PUSHS","bool@true");

                generate_1opL("LABEL",end_label);

                break;
            
            case R_MOE:
            generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                // WIHTOUT BOOLOP EXTENTION , BOOLS CANNOT BE COMPARED
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                //not nill 

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("GT",helper_val,name1,name2);
              //  generate_3opLSS("JUMPIFEQ",,helper_val,"bool@true"); // jump na chybu ak je to nil
                generate_1opS("PUSHS",helper_val);

                // GT is false 
                generate_3opVSS("EQ",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);

                generate_0op("ORS");  // gt OR eq 
                // value is on top of stack
                generate_1opL("JUMP",end_label);


                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                break;
            
            case R_LOE:
                generate_1opV("POPS",name2);        // order matters here 
                generate_1opV("POPS",name1);   

                generate_2opVS("TYPE",name2_type,name2);
                generate_2opVS("TYPE",name1_type,name1);

                generate_3opLSS("JUMPIFEQ",same_type_label,name1_type,name2_type); //jump if same type 

                  // not same type 
                //generate_1opL("LABEL",not_same_label);
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@bool");     // jump na chybu ak je to bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@nil");      // jump na chybu ak je to nil
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@string"); 
                generate_3opLSS("JUMPIFEQ",error_label,name2_type,"string@string");   // jump na chybu ak je to string

                // both are either int or float 
                generate_3opLSS("JUMPIFEQ",first_is_int_label,name1_type,"string@int"); // jump if 1 is int 

                // 1 is float 
                generate_2opVS("INT2FLOAT",name2,name2); // 2 is int and is converted
                generate_1opL("JUMP",add_label);

                // 1 is int so 2 is float 
                generate_1opL("LABEL",first_is_int_label);
                generate_2opVS("INT2FLOAT",name1,name1); // 1 is int and is converted
                generate_1opL("JUMP",add_label);


                // same type
                generate_1opL("LABEL",same_type_label);
                // WIHTOUT BOOLOP EXTENTION , BOOLS CANNOT BE COMPARED
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@bool"); // jump na chybu ak je to bool
                // not bool
                generate_3opLSS("JUMPIFEQ",error_label,name1_type,"string@nil"); // jump na chybu ak je to nil
                //not nill 

                // not bool or nil or string
                generate_1opL("LABEL",add_label);
                generate_3opVSS("LT",helper_val,name1,name2);
              //  generate_3opLSS("JUMPIFEQ",,helper_val,"bool@true"); // jump na chybu ak je to nil
                generate_1opS("PUSHS",helper_val);

                // GT is false 
                generate_3opVSS("EQ",helper_val,name1,name2);
                generate_1opS("PUSHS",helper_val);

                generate_0op("ORS");  // gt OR eq 
                // value is on top of stack
                generate_1opL("JUMP",end_label);


                // error
                generate_1opL("LABEL",error_label);
                generate_1opS("EXIT","int@4");

                generate_1opL("LABEL",end_label);
                break;

            case R_OP:
                //DLSucc(&zoznam);
                //DLCopy(&zoznam,&token);
              
                while((token.type != t_STRING) && (token.type != t_FLOAT) && (token.type != t_INT_NON_ZERO) && (token.type != t_INT_ZERO) && (token.type != t_IDENTIFIER) && (token.type != EXP_END )){  // EXP_END doesnt need to be heer 
                    DLSucc(&zoznam);
                    DLCopy(&zoznam,&token);
                }
               
              
                if(token.type == t_IDENTIFIER){
                    char name[VAR_LEN] = "";
                    if (scope_now == 0){
                        strcat(name,"GF@");

                    }
                    else
                    {
                        strcat(name,"LF@");

                    }
                    strcat(name,token.lex);
                    generate_1opS("PUSHS",name);
                    //generate_0op("PUSHUJEM NAME TETAZ");
                    sprintf(name,"%s","");
                    break;
                }
                else if(token.type == t_FLOAT || token.type == t_STRING || token.type == t_INT_ZERO || token.type == t_INT_NON_ZERO){
                    help = assign_type(token.type);
                    sprintf(complete_var,"%s",help);
                    strcat(complete_var,token.lex); // building var value  example:  string@Hello
                    generate_1opS("PUSHS",complete_var);
                    break;
                }
                else if(token.type == t_NONE){
                    generate_1opS("PUSHS","nil@nil");
                    break;
                }
                else
                {
                    fprintf(stderr,"I SHOULD NOT BE HERE, I HAVE GOTTEN SOMETHING ELSE IN EXPRESSION THAT IS NOT CONSTANT OR ID ");
                    exit(3);
                }
                


            case R_EBRACES:
                //  do noting
                break;

            case R_NOTDEFINED:
                //  do noting 
                break;
            
            default :
             fprintf(stderr,"I SHOULD NOT BE HERE, ERROR IN PRECEDENCE RULES");
                    exit(2);
                break;
        }
    }

    while(token.type != EXP_END && Active(&zoznam)){
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
    }
   //DLSucc(&zoznam); // token after END_EXPR
    DLCopy(&zoznam,&token);
    expression_id++;
}



void gen_if_else(){
    allowed_def = false;
    DLSucc(&zoznam);
    static int number;
    
    char if_label[LABEL_LEN] = "$if$%";
    char  number_str[VAR_LEN] = "";
    sprintf(number_str,"%d",number);
    strcat(if_label,number_str);
    char bool_var[VAR_LEN] = "";
    if (scope_now == 0){
        strcat(bool_var,"GF@$if%");
    }
    else
    {
        strcat(bool_var,"LF@$if%");
    }
    
    strcat(bool_var,number_str);
    strcat(bool_var,"bool");
    gen_expression(); 

    generate_1opV("DEFVAR",bool_var);
    generate_1opV("POPS",bool_var); 
    //////////////////////////////
    // 0 None ''  su false  inak true 


    /// DOROBIT CHECKNUTIE TYPOV
    //generate_3opLSS("JUMPIFEQ",if_label,bool_var,"nil@nil");    // if expr == None
    //generate_3opLSS("JUMPIFEQ",if_label,bool_var,"int@0");      // if expr == 0 
    //generate_3opLSS("JUMPIFEQ",if_label,bool_var,"string@");    // if expr == ""
    generate_3opLSS("JUMPIFEQ",if_label,bool_var,"bool@false");     // if expr == false 
    /////////////////////////////
    //if part 
    TOKEN token;
    DLCopy(&zoznam,&token);
    while(token.type != t_ELSE){
        generate_from_token_list(token);
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
    }
    char end_label[LABEL_LEN] = "";
    strcat(end_label,if_label);
    strcat(end_label,"$end");
    generate_1opL("JUMP",end_label);
    

    //else part 
    generate_1opL("LABEL",if_label);

    DLSucc(&zoznam);
    DLCopy(&zoznam,&token);
    while(token.type != t_DEDENT && token.type != t_EOF){
        generate_from_token_list(token);
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
    }
    
    generate_1opL("LABEL",end_label);
    number++;
    allowed_def = true;

}

// TODO opravit eby sa nedefinovali furt veci dokola 
void generate_loop(){
    allowed_def = false;
    static int loop_num;
    TOKEN token;
    char * while_label = "$while$%";
    char label_name[VAR_LEN]="";
    char str[4];
    sprintf(str, "%d", loop_num);
    strcat(label_name,while_label);
    strcat(label_name,str);
    DLSucc(&zoznam);
    DLCopy(&zoznam,&token);
    generate_1opL("LABEL",label_name);
    gen_expression();
    // here do the same as in evaluating the if else

    // check all DEFVARs inside while and define them before somehow
    ///////////////////////////////////////////
    char name[VAR_LEN]="";
    int token_counter = 0;
    while(token.type != t_DEDENT && token.type != t_EOF){
            //generate_from_token_list(token);
            token_counter++;
            DLSucc(&zoznam);
            DLCopy(&zoznam,&token);
            tBSTNodePtrLocal  *tree;
            if (token.type == t_ASSIGN){
                DLPred(&zoznam); // move to prev assign
                DLCopy(&zoznam,&token);
            
                if (scope_now == 0){
                    strcat(name,"GF@");
                    tree = GFDefinedVarsTree;
                    
                }
                else
                {
                    strcat(name,"LF@");
                    tree = LFDefinedVarsTree;
                }
                
                strcat(name,token.lex);
                // if var has not been DEFVARed 
                if (!BSTSearchLocal(tree,token.lex)){
                     generate_1opV("DEFVAR",name);
                     BSTInsertLocal(&tree,name);
                }
                DLSucc(&zoznam); // move to assign
            }
            sprintf(name,"%s","");
           // DLSucc(&zoznam);
            DLCopy(&zoznam,&token);

    }
    // get back to while
    for (int i = 0;i< token_counter;i++){
                DLPred(&zoznam);
    }
    ///////////////////////////////////////////
    // i think its solved but needs testing TODO
    

     while(token.type != t_DEDENT && token.type != t_EOF){             /// POSIBLE ERROR !
        generate_from_token_list(token);
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
    }
    loop_num++;
    allowed_def =true;
}


// TODO : parametre by asi mali byt normalne mena ne param1 param2
// pomocu get_param_names funkcie  treba potom zmenit kod v def_func_gen

// funcion reads list of tokens and gets param names  
// funcke bude volana v def_func_gen() a vrati mena parametrov a pocet 
int get_param_names(char param_list[][VAR_LEN]){
    TOKEN tmp;
    int i = 0;
    DLCopy(&zoznam,&tmp);
    while (tmp.type != t_COLON)    //gets all params   // TOOD: fill in hodnota
    {      
        sprintf((param_list)[i],"%s", tmp.lex);
        i++;
        DLSucc(&zoznam);
        DLCopy(&zoznam,&tmp);
    }
    return i;
    // CURRENT TOKEN IS COLON
    
}

// DEFINICE FUNKCE  
void def_func_gen(char * func_name){
    BSTInitLocal(&LFDefinedVarsTree);
    BSTInsertLocal(&LFDefinedVarsTree,"%$");
    char help[LABEL_LEN] = "$";
    strcat(help,func_name);
    generate_1opL("LABEL",help);
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    scope_now = 1;
    char param_list[MAX_PARAM_COUNT][VAR_LEN];

    DLSucc(&zoznam); // CURRENT TOKEN MOVES FROM FUNC NAME TO FIRST PARAM
    int num_of_params = get_param_names(&param_list);    // put parameter names into param_list
    // TOKEN IS COLON

    char  var_name[VAR_LEN] = "";
    char  *tmp_LF = "LF@";
    char  tmp_TF[VAR_LEN] = "LF@%$";
    char number[VAR_LEN] = "";
    for( int i= 1;i < num_of_params+1 ;i++){
        strcat(var_name,tmp_LF);
        strcat(var_name,param_list[i]);
        sprintf(number,"%d",i);
        strcat(tmp_TF,number);
        generate_1opV("DEFVAR",var_name);
        BSTInsertLocal(&LFDefinedVarsTree,var_name);
        generate_2opVS("MOVE",var_name,tmp_TF);  //tmp_TF is actually LF  it is fixed already
         sprintf(var_name,"%s","");   // make varname ready for next param
         sprintf(tmp_TF,"%s","LF@%$");
    }
    TOKEN token;
    DLSucc(&zoznam); // TOKEN AFTER COLON
    DLCopy(&zoznam,&token);
    while (token.type != t_DEDENT ){             /// POSIBLE ERROR !
        if (&(*zoznam.Act) == NULL){
            break;
        }
    generate_from_token_list(token);
        if (&zoznam.Act == &zoznam.Last){
            return;
        }
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
    }
    //func_body(param_list); // TODO : bosy bude vykonavat normalne prikazy a posuvat sa po liste tokenov
    //generate_2opVS("MOVE","LF@%retval","LF@%retval");

    end_def_func();
    BSTDisposeLocal(&LFDefinedVarsTree);
}


void end_def_func(){
    generate_0op("POPFRAME");
    generate_0op("RETURN");
    scope_now = 0;
}



const char* assign_type(int type){
    switch (type)
    {
    case t_IDENTIFIER:
        if (scope_now == 0){
            return "GF@";
        }
        else {
            return "LF@";
        }
    case t_INT_ZERO:
    case t_INT_NON_ZERO:
        return "int@";
    case t_STRING:
        return "string@";
    
    case t_FLOAT:
        return "float@";
    // SEEMS WE DONT SUPPORT NIL AND BOOL TYPES SO FAR BECAUSE NOBODY DID THEM :) IM NOT SAD AT ALL :) 
    /*
    case BOOL_CODE:
        return "bool@";

    case NIL_CODE:
        return "nil@";    
    */    
    default:
        fprintf(stderr,"ERROR in function assign_type, Unknown token type provided."); // ONLY FOR TESTING,  SHOULD NOT BE NEEDED IN FINAL PRODUCT
        exit(2);
    }
}


void call_func(char * func_name,int num_of_params){
    generate_0op("CREATEFRAME");
    char  tmp[10] = "TF@%$";
    char  complete_var[VAR_LEN] = "";
    const char * help;
    TOKEN param_tmp;
    char str[4];
    for( int i= 0;i< num_of_params;i++){
        if (i < 10){
            tmp[4] = i + '0';
        }
        else{
            sprintf(str, "%d", i);
            strcat(tmp,str);
        }
        generate_1opV("DEFVAR",tmp);
        DLCopy(&zoznam,&param_tmp);
        if(param_tmp.type == t_FUNCTION_CALL){
            DLSucc(&zoznam);
            DLSucc(&zoznam);
            DLCopy(&zoznam,&param_tmp);
        }
        help = assign_type(param_tmp.type);
        sprintf(complete_var,"%s",help);
        strcat(complete_var,param_tmp.lex); // building var value  example:  string@Hello
        generate_2opVS("MOVE",tmp,complete_var); //TODO
        DLSucc(&zoznam); // move activity to next token
        if (param_tmp.type == t_RIGHT_BRACKET){
            DLSucc(&zoznam);
            DLCopy(&zoznam,&param_tmp);
        }
        sprintf(tmp,"%s","TF@%$");
    }
    char helper[LABEL_LEN] = "$";
    strcat(helper,func_name);
    generate_1opL("CALL",helper);  // call function
    
}



int check_if_func_defined(char *name){
    global_t content;
    if (BSTSearch(GlobalBody,name,&content)){
        if (content.defined){
            if(content.is_function){
                return content.num_of_params;
            }
            else{
                fprintf(stderr,"somehow sa dostala variable ako function call cez parser");
                exit(3);
            }
        }
        else{
            fprintf(stderr,"function not defined");
            exit(3);
        }
    }
    else{
            fprintf(stderr,"function not defined, toto by sa nemalo printovat nikdy kedze parser sa o to ma postarat");
            exit(3);
        }
}

// assign value to global variable, value can be either constant or variable or function retval from TF, but it has to be in IFJCODE19
// WIHTOUT BOOLOP RETURN VALUE CANNOT BE OF TYPE BOOL !! TODO 
void assign_to_var(char * name){
    DLSucc(&zoznam); // next token is probably assign
    DLSucc(&zoznam); // this one is interesting
    TOKEN token;
    DLCopy(&zoznam,&token);
    //printf("som %d==============================================  \n",token.type);
    tBSTNodePtrLocal  *tree;
    if (scope_now == 0){
        tree = &GFDefinedVarsTree;
    }
    else
    {
        tree = &LFDefinedVarsTree;
    }
    if (BSTSearchLocal(*tree,name)){
            //generate_1opV("POPS",name);
            generate_1opS("DPRINT",name);
        }
        else
        {
            generate_1opV("DEFVAR",name);
            BSTInsertLocal(&tree,name);
            //generate_1opV("POPS",name);
            generate_1opS("DPRINT",name);
        }
    //  assigning expresion  
    if (token.type == EXP_START && Active(&zoznam)){
        gen_expression();
         if (BSTSearchLocal(tree,name)){
            generate_1opV("POPS",name);
            generate_1opS("DPRINT",name);
        }
        else
        {
            //generate_1opV("DEFVAR",name);
            //BSTInsertLocal(&tree,name);
            generate_1opV("POPS",name);
            generate_1opS("DPRINT",name);
        }
        

    }
    //  assigning function call  
    else if (token.type == t_FUNCTION_CALL)
    {
        //printf("SOM VO FUNC CALL\n");
        int num_of_params = check_if_func_defined(token.lex);
        call_func(token.lex,num_of_params);
        if (BSTSearchLocal(&tree,name)){
            generate_2opVS("MOVE",name,"TF@%retval");
        }
        else
        {
            generate_1opV("DEFVAR",name);
            BSTInsertLocal(&tree,name);
            generate_2opVS("MOVE",name,"TF@%retval");
        }
    }
    //  assigning another variable
    else{
        char str[VAR_LEN] = "";
        char *prefix;
         prefix = assign_type(token.type);
         strcat(str,prefix);
        strcat(str,token.lex);
        
        if (BSTSearchLocal(tree,name)){
            generate_2opVS("MOVE",name,str);
        }
        else
        {
            generate_1opV("DEFVAR",name);
            BSTInsertLocal(&tree,name);
            generate_2opVS("MOVE",name,str);
        }
    }
}

void gen_return(char *val){
    
    generate_2opVS("MOVE","LF@%retval",val);
    end_def_func();
}


// ======================== PRINT(UNCAPPED) ========================= // 
// done 
// function isnt defined , it is just a piece of code that gets printed everytime print() is called
void gen_print(int num_of_params){
    generate_0op("CREATEFRAME");
    char tmp [10] = "TF@%$";  //supports a lot of print parmeters
    char num[4] = "";
    char  complete_var[VAR_LEN] = "";
    TOKEN param_tmp;
    const char * help;
    for (int i = 1; i < (num_of_params + 1); i++)
    {
        sprintf(num,"%d",i);
        strcat(tmp,num);
        //generate_1opS("WRITE",str);
        //sprintf(str,"%s","TF@"); // THIS WORKS
        generate_1opV("DEFVAR",tmp);
        DLCopy(&zoznam,&param_tmp);   
        help = assign_type(param_tmp.type);
        sprintf(complete_var,"%s",help);
        strcat(complete_var,param_tmp.lex); // building var value  example:  string@Hello
        generate_2opVS("MOVE",tmp,complete_var); //TODO
        DLSucc(&zoznam); // move activity to next token   
        sprintf(tmp,"%s","TF@%$");
    }
    // po tade ok 
    generate_0op("PUSHFRAME");
    generate_1opV("DEFVAR","LF@%retval");
    generate_2opVS("MOVE","LF@%retval","nil@nil");
    //scope_now = 1; 
    
    char  passed_param[VAR_LEN] = "";
    char  tmp_LF[VAR_LEN] = "LF@%$";
    for (int i = 1; i < (num_of_params + 1); i++)
    {
        strcat(passed_param,tmp_LF);
        sprintf(num,"%d",i);
        strcat(passed_param,num);
        //generate_1opS("DPRINT","LF@%$1");
        //generate_0op("BREAK");
        generate_1opS("WRITE",passed_param);
        sprintf(passed_param,"%s","");   // make varname ready for next param
        sprintf(tmp_LF,"%s","LF@%$");
    }
     generate_0op("POPFRAME");
    
}



// sort of main function for generator
void generate_from_token_list(TOKEN token){
    char c = token.type;
    char  name[VAR_LEN] = "";
    int num_of_params = 0; 
    switch (c)
    {
    case t_DEF:
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
        if (scope_now == 0 && allowed_def){
            def_func_gen(token.lex);
        }
        //TODO : skontrolovat ci toto damian checkuje a ked hej tak tento if else vymazat lebo je pointless
        else{
            fprintf(stderr,"ERROR, tyring to define function not in main body but in either loop , if else statements or inside function");
            exit(2); //TODO fix error code 
        }
        break;

    case t_IDENTIFIER:
        
        if (scope_now == 0){
            strcat(name,"GF@");
            
        }
        else
        {
            strcat(name,"LF@");
        }
        strcat(name,token.lex);
        assign_to_var(name);
        break;

    case EXP_START:
        generate_1opV("DEFVAR","GF@$p$l$a$c$e$h$o$l$d$e$r"); // this variable is equvalent to /dev/null
        gen_expression();
        generate_1opV("POPS","GF@$p$l$a$c$e$h$o$l$d$e$r");
        break;

    case t_FUNCTION_CALL:
        DLSucc(&zoznam); // move to left bracket 
        DLSucc(&zoznam); // move to first param 
        // INLY PRINT FUNCTION 
        if (strcmp(token.lex,"print")==0){
            while(token.type != t_RIGHT_BRACKET){        //TODO FIX MACRO HERE
                num_of_params++;
                DLSucc(&zoznam);
                DLCopy(&zoznam,&token);
            }
            // moving activity to fisrt param
            for (int i = 0;i< num_of_params;i++){
                DLPred(&zoznam);
            }
            gen_print(num_of_params);
        }
        // ALL FUNCTIONS EXCEPT PRINT
        else{
            while(token.type != t_RIGHT_BRACKET){        //TODO FIX MACRO HERE
                num_of_params++;
                DLSucc(&zoznam);
                DLCopy(&zoznam,&token);
            } 
            int param_num = check_if_func_defined(name);
            if(param_num == num_of_params){
                call_func(name,num_of_params);
            }
            else
            {
                fprintf(stderr,"SOMEHOW FUNCTION WITH INCORRECT PARAM NUMBERS GOT HERE, SHOULD NEVER BE LET THROUGH PARSER, THIS CODE SHOULD NEVER BE PREINTED!");
                exit(5);
            }
              
        }
        break;

    case t_WHILE:
        generate_loop();
        break;

    case t_IF:
        gen_if_else();
        break;

    case t_RETURN:  
        if (scope_now == 1){
            DLSucc(&zoznam);
            DLCopy(&zoznam,&token);
            if (token.type == t_DEDENT){  // if no expr after return then return None
                 end_def_func();  // LF@retval is already nil@nil 
            }
            else{
                char str[VAR_LEN] = "";
                const char * return_val = assign_type(token.type);
                sprintf(str,"%s",return_val);
                strcat(str,token.lex); // building var value  example:  string@Hello
                gen_return(str); 
            }
        }
        //TODO : skontrolovat ci toto damian checkuje a ked hej tak tento if else vymazat lebo je pointless
        else{
            fprintf(stderr,"RETURN pouzity v hlavnom tele programu ! TOTO by sa nikdy nemalo printnut btw, mal by to handlenut parser!");
            exit(2); //TODO fix error code 
        }
        break;

    case t_PASS:
        break;

    default:
        break;
    }
    //sprintf(name,"%s","");
}

void second_pass(){
    // initializing linked list for output 
    InitList(&output_list);
    generate_start();
    //printf("DPRINT HELLO");
    TOKEN token;
    DLFirst(&zoznam);
    DLCopy(&zoznam,&token);
    while(token.type != t_EOF && DLActive(&zoznam)){
        generate_from_token_list(token);
        DLSucc(&zoznam);
        DLCopy(&zoznam,&token);
    }
}


void print_output(){
    First(&output_list);
    Succ(&output_list);
    char * value;
    while(true){
        Copy(&output_list,&value);
        printf("%s",value);
        Succ(&output_list);
        if (!Active(&output_list)){
            break;
        }
    }
}




