/* 
**	Part of IFJ Project 2019/2020
**	Author: Samuel Stuchly xstuch06
**
** 	Header file for generator.c
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#include "symtable.h"

#include "scanner.h" 
#include "helper.h"
#include "dl_list.h"
#include "parser.h"

#include "precanalysis.h"



#define LABEL_LEN 30
#define VAR_LEN 35
#define RULE_ARRAY_LEN 40
#define MAX_PARAM_COUNT 100 


	
void generate_string(char * instruction_string);
void generate_instruction(char * instruction);
void generate_operand(char * operand);
void generate_newline();
void generate_0op(char* inst);
void generate_1opV(char* inst, char* var);
void generate_1opL(char* inst,char* label);
void generate_1opS(char* inst,char* symb);
void generate_2opVS(char* inst,char* var,char * symb);
void generate_2opVT(char* inst,char* var,char * type);
void generate_3opVSS(char* inst,char* var,char *symb1, char* symb2);
void generate_3opLSS(char* inst,char* label,char *symb1, char* symb2);
bool is_var(char * var);
bool is_symb(char * symb);
bool is_const(char * konst);
bool is_label(char * label);
bool is_type(char *type);
void gen_inputs();
void gen_inputi();
void gen_inputf();
void check_for_len(char* s_param);
void gen_len();
void check_for_substr(char * s_param, char * i_param,char * n_param);
void gen_substr();
void check_for_ord(char * s_param, char * i_param);
void gen_ord();
const char * check_for_chr(char * i_param);
void gen_chr();
void def_built_in();
void generate_start();
void gen_expression();
void gen_if_else();
void generate_loop();
int get_param_names(char param_list[][VAR_LEN]);
void def_func_gen(char * func_name);
void end_def_func();
const char* assign_type(int type);
void call_func(char * func_name,int num_of_params);
int check_if_func_defined(char *name);
void assign_to_var(char * name);
void gen_return(char *val);
void gen_print(int num_of_params);
void generate_from_token_list(TOKEN token);
void second_pass();
void print_output();


#endif