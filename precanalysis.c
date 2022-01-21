/*
`*    Part of IFJ project 2019/2020
`*    Author: Martin Novotny Mlinarcsik xnovot1r
 *     
 *
 MAKRA */

#include "precanalysis.h"
#include "symstack.h"
#include "scanner.h"
#include "dl_list.h"
#include "symtable.h"
#include "parser.h"
//#include "main.c"




tsym_stack syms_Stack;
TOKEN exp_start, exp_end;
TOKEN help_tmp;
TOKEN dollar;
global_t glob_tmp;
int count;
bool red_found;
psa_rules rule;

int rule_array[120][40];





/* Prec analysis */
char psa_prec_table[PTABLE_ROWS][PTABLE_COLUMNS] = {

        /*          |+|     |-|     |*|     |/|     |//|    |(|      |)|     |==|    |!=|    |>=|   |<=|     |<|     |>|    |i|     $| */
        /*  +  */ { '>'  ,  '>'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  -  */ { '>'  ,  '>'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  *  */ { '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  /  */ { '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  // */ { '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  (  */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '='  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  'X' },
        /*  )  */ { '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  'X'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  'X'  ,  '>' },
        /*  == */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  != */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  >= */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  <= */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  <  */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  >  */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '<'  ,  '>' },
        /*  i  */ { '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  'X'   ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  '>'  ,  'X'  ,  '>' },
        /*  $  */ { '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'   ,  'X'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  '<'  ,  'X' },
};


/* Prevedie typ tokenu na symbol */
//UPRAVIT - typ tokenu podla Simona

////////////////////////////////////////////////////////////////////////////

psa_symbols psa_tokenToSymbol(TOKEN* token) {

        if (token->type == t_PLUS) 
            return T_PLUS;
        else if (token->type == t_MINUS) 
            return T_MINUS;
        else if (token->type == t_MULTIPLY) 
            return T_MUL;
        else if (token->type == t_DIVIDE_F) 
            return T_DIV;
        else if (token->type == t_DIVIDE_I) 
            return T_IDIV;
        else if (token->type == t_RIGHT_BRACKET) 
            return T_RIGHT_PARENTHESIS;
        else if (token->type == t_LEFT_BRACKET) 
            return T_LEFT_PARENTHESIS;
        else if (token->type == t_LESS) 
            return T_LESS;
        else if (token->type == t_GREATER) 
            return T_MORE;
        else if (token->type == t_LESSOREQUAL) 
            return T_LOE;
        else if (token->type == t_GREATEROREQUAL) 
            return T_MOE;
        else if (token->type == t_IDENTIFIER) {
            
            /*if (scope == 0) {

               if (!(BSTSearch(&GlobalBody, token->lex, &glob_tmp))) {
                   fprintf(stderr, "PSA Semantic Error\n");
                   exit(3);
               }

               else if (scope == 1) {
                   if (!(BSTSearchLocal(&LocalVariables, token->lex))) {
                       if (!(BSTSearch(&GlobalBody, token->lex, &glob_tmp))) {
                           fprintf(stderr, "PSA Semantic Error\n");
                       } else {
                    fprintf(stderr, "PSA Semantic Error\n");
                       }
                   }
               }
            }*/


            return T_ID;
        }
        else if (token->type == t_INT_NON_ZERO)   
            return T_ID;
        else if (token->type == t_INT_ZERO) 
            return T_ID;
        else if (token->type == t_FLOAT) 
            return T_ID;
        else if (token->type == t_STRING) 
            return T_ID;
        else if (token->type == t_EQUAL) 
            return T_EQUAL;
        else if (token->type == t_NOT_EQUAL) 
            return T_NEQUAL;
        else {
            return T_DOLLAR;
        }
    }

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////

/* Ake pravidlo sa uplatni pri vyraze*/

psa_rules psa_rule_application(int pocet, tsym_stack_symbol* sym1, tsym_stack_symbol* sym2, tsym_stack_symbol* sym3) {
 
    if (pocet == 1) {

        if (sym1->symbol == T_ID) {

            return R_OP;
        } else {

            return R_NOTDEFINED;
        }
    }

    // NON_TERM sa bude pushovat pocas reduce pravidla namiesto popnutych symbolov
    else if (pocet == 3) {
        if (sym1->symbol == T_LEFT_PARENTHESIS && sym2->symbol == T_NON_TERM && sym3->symbol == T_RIGHT_PARENTHESIS) {
            return R_EBRACES;
        }

        if (sym1->symbol == T_NON_TERM && sym3->symbol == T_NON_TERM) { 
            
            if(sym2->symbol == T_PLUS) {                   
                return R_PLUS;
            }

            else if (sym2->symbol == T_MINUS) 
                return R_MINUS;

            else if (sym2->symbol == T_MUL) 
                return R_MUL ;

            else if (sym2->symbol == T_DIV) 
                return R_DIV;

            else if (sym2->symbol == T_IDIV) 
                return R_IDIV;

            else if (sym2->symbol == T_EQUAL ) 
                return R_EQUAL;

            else if (sym2->symbol == T_NEQUAL ) 
                return R_NEQUAL;

            else if (sym2->symbol == T_MOE) 
                return R_MOE;

            else if (sym2->symbol == T_LOE ) 
                return R_LOE;

            else if (sym2->symbol == T_MORE ) {
                return R_MORE;
            }
            else if (sym2->symbol == T_LESS ) 
                return R_LESS;
 
            } else {
                return R_NOTDEFINED;
            }
        return R_NOTDEFINED;

    }

    return R_NOTDEFINED;
}

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
void evaluation(tDLList* psa_list) {

    //printf("VOSIEL SOM DO PSA\n");

    glob_tmp.defined = true;
    glob_tmp.is_function = false;
    glob_tmp.num_of_params = NULL;

    dollar.lex = '$';
    dollar.type = T_DOLLAR;

    int rule_counter = 0; 
    static int id_counter = 0;

    extern psa_rules rule;

    //TOKENY zaciatok a start
    exp_start.lex = id_counter;
    exp_end.lex = NULL;

    exp_start.type = EXP_START;
    exp_end.type = EXP_END;


    

    DLDeleteFirst(psa_list);
    DLFirst(psa_list);
    DLInsertFirst(psa_list, exp_start);
    DLInsertLast(psa_list, dollar);

    tsym_stack syms_Stack;
    symstack_init(&syms_Stack);

    symstack_push(&syms_Stack, T_DOLLAR); //DOLLAR NA SPODKU STACKU

    psa_symbols input_sym;
    tsym_stack_symbol* top_terminal;

    bool koniec = false;

    do {

        input_sym = psa_tokenToSymbol(&psa_list->Act->data);
        top_terminal = symstack_top_t(&syms_Stack);

        /* SHIFT */


        if (psa_prec_table[(psa_symbols)top_terminal->symbol][input_sym] == '<') {
           // printf("som v <\n");

            symstack_push_red(&syms_Stack, T_RED);

            symstack_push(&syms_Stack, input_sym);
            psa_list->Act = psa_list->Act->rptr;

        } 

        /* REDUKCIA */
        else if (psa_prec_table[(psa_symbols)top_terminal->symbol][input_sym] == '>') {
           // printf("som v >\n");
             tsym_stack_symbol* checked_symbol;
        ///////////////////////////////////////////////////////////////////

///////////////// TU POZOR /////////////////////////
            checked_symbol = syms_Stack.top;
/////////////////////////////////////////////////


            while (checked_symbol != NULL)
            {
                if (checked_symbol->symbol != T_RED)
                {
                    red_found = false;
                    count++;
                }
                else if (checked_symbol->symbol == T_RED)
                {
                    red_found = true;
                    break;
                }

                checked_symbol = checked_symbol->next;
            }
////////////////////////////////////////////////////////////////////////////////////////////////////

            if (count != 3 && count != 1) {

                //fprintf(stderr, "Syntax Error, zly pocet symbolov\n");
                exit(2);
            }

            if (count == 1 && red_found) {

                //3 symbolx potrebne pre redukciu
                tsym_stack_symbol* red1;

                red1 = syms_Stack.top;

                rule = psa_rule_application(count, red1, NULL, NULL);
                symstack_pop(&syms_Stack);
                symstack_pop(&syms_Stack); //popuje sa RED symbol
                symstack_push(&syms_Stack, T_NON_TERM);


            }   else if (count == 3 && red_found) {

                //3 symbolx potrebne pre redukciu
                tsym_stack_symbol* red1;         
                tsym_stack_symbol* red2;
                tsym_stack_symbol* red3;             


                red3 = syms_Stack.top;
                red2 = red3->next;
                red1 = red3->next->next;

                rule = psa_rule_application(count, red1, red2, red3);

                symstack_pop(&syms_Stack);
                symstack_pop(&syms_Stack);
                symstack_pop(&syms_Stack);
                symstack_pop(&syms_Stack); //popuje sa RED symbol

                symstack_push(&syms_Stack, T_NON_TERM);
            }

             if (rule == R_NOTDEFINED) {
                fprintf(stderr, "PSA - Syntax error\n");
                exit(2);
                } else {
                count = 0;
                rule_array[id_counter][rule_counter] = rule;
                rule_counter++;
                }
        }

        /* EQUAL */
         else if (psa_prec_table[(psa_symbols)top_terminal->symbol][input_sym] == '=') {
            // printf("som v =\n");

             symstack_push(&syms_Stack, input_sym);
             psa_list->Act = psa_list->Act->rptr;
         }

        else if (psa_prec_table[(psa_symbols)top_terminal->symbol][input_sym] == 'X') {
            //printf("som v x\n");

             if((input_sym == T_DOLLAR && top_terminal->symbol == T_DOLLAR) != true) {

                 fprintf(stderr, "PSA SYNTAX ERROR, EXIT (2)\n");

                exit(2); //situacia nemoze nastat
             } else 
                koniec = true;
         }

    } while (koniec != true);

    DLDeleteLast(psa_list); //removnem dollar na konci listu

    DLInsertLast(psa_list, exp_end);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // INSERT DO GLOBALNEHO STROMU //

    DLFirst(psa_list);

    while (psa_list->Act->data.type !=EXP_END ){

        help_tmp = psa_list->Act->data;
        DLInsertLast(&zoznam, help_tmp);
        DLSucc(psa_list);


    }
    help_tmp = psa_list->Act->data;
    DLInsertLast(&zoznam, help_tmp);
    id_counter++;

    //printf("PSA ENDED, SPRAVNE UKONCENIE \n");
    symstack_free(&syms_Stack);

}

/////////////////////////////////

