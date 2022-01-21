/*
**    Part of IFJ Project 2019/2020
**    Author: Simon Fenko xfenko01
*/

#ifndef scanner_h
#define scanner_h

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define START 0
#define t_LESS 1
#define t_GREATER 2
#define t_ASSIGN 3
#define EXLAMATION 4
#define t_COMMA 5
#define t_LEFT_BRACKET 6
#define t_RIGHT_BRACKET 7
#define t_DIVIDE_F 8
#define t_MULTIPLY 9
#define t_PLUS 10
#define t_MINUS 11
#define ONE_LINE_COMMENT 12
#define t_COLON 13
#define IND_DED 14
#define QUOTES1 15
#define t_INT_ZERO 16
#define t_INT_NON_ZERO 17
#define STRING_START 18
#define t_IDENTIFIER 19
#define t_DEF 20
#define t_ELSE 21
#define t_IF 22
#define t_NONE 23
#define t_PASS 24
#define t_RETURN 25
#define t_WHILE 26
#define t_EOF 27
#define t_FUNCTION_CALL 28
//def, else, if, None, pass, return, while.
#define t_LESSOREQUAL 100
#define t_GREATEROREQUAL 98
#define t_EQUAL 96
#define t_NOT_EQUAL 95
#define t_DIVIDE_I 93
#define QUOTES2 92
#define COMMENT1 91
#define COMMENT2 90
#define COMMENT3 89
#define ES_COMMENT 87
#define DOT 86
#define EXPONENT 85
#define t_FLOAT 84
#define ES_STRING 83
#define t_STRING 82
#define STRING_HEXA1 81
#define STRING_HEXA2 77
#define PLUS_MINUS_EXPONENT 80
#define t_EOL 79
#define t_INDENT 78
#define t_DEDENT 77
#define EXPONENT2 76

#define EXP_START 69
#define EXP_END 420

typedef struct TOKEN
{
    char* lex;
    int type;
}TOKEN;

//mazanie current_tokenu
void delete_string(void);

/*najprv vytiahne znak zo suboru a hodi ho do current_char a prilepi ho
 na koniec stringu, do ktoreho sa uklada sučasny načitavany token, zvyši
 poziciu stringu (dlžku stringu a zakonči ho 0 )
*/
void load_c(FILE* text);

/* zavola sa unload a zaroven spravi ungetc - hladačik sa posunie o jedno
dozadu a odreze posledny character zo stringu c current_token */
void unload_c(FILE *text);

/* alokovanie miesta pre string v tokene */
void alloc(int length, TOKEN* token);

/* najprv alokujeme miesto pre textoy obsah tokenu, potom ho tam skopirujeme
 z current_token, potom skopirujeme type a vymazeme current_token */
void end_token(int type, TOKEN* token);

TOKEN get_next_token(FILE* text);


#endif /* scanner_h  */
