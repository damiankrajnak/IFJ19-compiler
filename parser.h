/*
 **    Part of IFJ Project 2019/2020
 **    Author: Damián Krajňák xskrajn03
 */

#ifndef parser_h
#define parser_h


#include <stdio.h>
#include "scanner.h"


#include "dl_list.h"
#include "symtable.h"
#include "stack.h"
#include "precanalysis.h"
#include "symstack.h"
int parser(void);
bool st_list(void);
bool statement(void);
bool params(void);
bool func_list(void);
bool command(void);
bool param_n(void);
bool func_cmd(void);
bool ass_func_expr(void);
bool f_ass_func_expr(void);
bool if_list(void);
bool else_list(void);
bool if_f_list(void);
bool else_f_list(void);
bool expr_id(void);
bool is_expression_eol(void);
bool is_expression_colon(void);
bool is_expression(void);
bool is_expression2(void);

extern tDLList zoznam;

#endif /* parser_h */
