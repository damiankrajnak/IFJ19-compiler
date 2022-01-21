/*
`*    Part of IFJ project 2019/2020
`*    Author: Martin Novotny Mlinarcsik xnovot1r
 *     
 *
 */


#ifndef PRECANALYSIS_H
#define PRECANALYSIS_H


#include "dl_list.h"
#include "symstack.h"
#include "helper.h"

#define PTABLE_ROWS 15
#define PTABLE_COLUMNS 15
#define SYNTAX_ERROR -1
#define SYNTAX_IN_ORDER 1

psa_symbols psa_tokenToSymbol(TOKEN* token);
psa_rules psa_rule_application(int pocet, tsym_stack_symbol* sym1, tsym_stack_symbol* sym2, tsym_stack_symbol* sym3);
void evaluation(tDLList* psa_list);

extern int rule_array[120][40];


#endif






