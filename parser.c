/*
 **    Part of IFJ Project 2019/2020
 **    Author: Damián Krajňák xkrajn03
 */

#include "parser.h"
#include "main.h"



tDLList psa_list;
TOKEN token;
TOKEN help_t;
TOKEN help_t2;
TOKEN trash;
TOKEN eol;
//extern tBSTNodePtr *GlobalBody;
//extern tBSTNodePtrLocal *LocalVariables;

global_t tmp;
global_t tmp_v;
int param_count;
extern int scope = 0;
bool remember;



int parser(){

  
    
    eol.type = t_EOL;
    eol.lex = "\n";
    BSTInit(&GlobalBody);
    BSTInit(&LocalVariables);
    DLInitList(&zoznam);
    TOKEN tokenik; 
    tokenik.lex = "INIT";
    tokenik.type = 404;
    DLInsertFirst(&zoznam,tokenik);
    tStack indent_s;
    stackInit(&indent_s);
    
    
    
    // inputs function
    global_t inputs;
    inputs.defined = true;
    inputs.is_function = true;
    inputs.num_of_params = 0;
    BSTInsert(&GlobalBody, "inputs", inputs);
    
    // inputi function
    global_t inputi;
    inputi.defined = true;
    inputi.is_function = true;
    inputi.num_of_params = 0;
    BSTInsert(&GlobalBody, "inputi", inputi);
    
    // inputf function
    global_t inputf;
    inputf.defined = true;
    inputf.is_function = true;
    inputf.num_of_params = 0;
    BSTInsert(&GlobalBody, "inputf", inputf);
   
    // print function
    global_t print;
    print.defined = true;
    print.is_function = true;
    //print.num_of_params = ???
    BSTInsert(&GlobalBody, "print", print);
    
    // len(s) function
    global_t len;
    len.defined = true;
    len.is_function = true;
    len.num_of_params = 1;
    BSTInsert(&GlobalBody, "len", len);
    
    // substr(s, i, n) function
    global_t substr;
    substr.defined = true;
    substr.is_function = true;
    substr.num_of_params = 3;
    BSTInsert(&GlobalBody, "substr", substr);
    
    // ord(s, i) function
    global_t ord;
    ord.defined = true;
    ord.is_function = true;
    ord.num_of_params = 2;
    BSTInsert(&GlobalBody, "ord", ord);
    
    // chr(i) function
    global_t chr;
    chr.defined = true;
    chr.is_function = true;
    chr.num_of_params = 1;
    BSTInsert(&GlobalBody, "chr", chr);
    //printf("%d\n", eol.type);
    token = get_next_token(stdin);

    //global_t tmpaa;
    //int i = BSTSearch(GlobalBody,"inputi",&tmpaa);
    //printf("====================================== %i  %i    %i    %i======",i,tmpaa.num_of_params,tmpaa.is_function,tmpaa.defined);
    
    return (int)st_list();
}


bool st_list(){
    bool result = false;
    switch(token.type){
        case t_DEF:
        case t_IDENTIFIER:
        case t_FLOAT:
        case t_INT_ZERO:
        case t_INT_NON_ZERO:
        case t_STRING:
        case t_IF:
        case t_WHILE:
        case t_PASS:
            // Rule: <st-list>  ->  <statement> EOL <st-list>
            if(statement()){
                if(token.type == t_EOF){
                    return true;
                }
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if (token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(st_list()){
                        result = true;
                        if(token.type != t_EOF){
                            token = get_next_token(stdin);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error.1\n");
                        exit(2);
                    }
                }
                else{
                    //printf("%d\n", token.type);
                    fprintf(stderr, "Syntax error.2\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error.3\n");
                exit(2);
            }
            break;
        case t_EOL:
            //printf("hovno\n");
            // Rule: <st-list>  ->  EOL <st-list>
            token = get_next_token(stdin);
            if(st_list()){
                result = true;
                token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error.4\n");
                exit(2);
            }
            break;
        case t_EOF:
            // Rule: <st-list>  ->  EOF
            DLInsertLast(&zoznam, token);
            result = true;
            //token = get_next_token(stdin);
            break;
        default:
            fprintf(stderr, "Syntax error st-list.\n");
            exit(2);
    }
    return result;
}

bool statement(){
    bool result = false;
    switch(token.type){
        case t_DEF:
            scope = 1;
            tmp.defined = false;
            tmp.is_function = true;
            tmp.num_of_params = 0;

            tmp_v.defined = false;
            tmp_v.is_function = false;
            tmp_v.num_of_params = 0;


            // Rule: <statement>  ->  def ID ( <params>  : EOL INDENT <func-list>
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(token.type == t_IDENTIFIER){

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Semanticka

                if(BSTSearch(GlobalBody, token.lex, &tmp)) {
                    fprintf(stderr, "Semantic error. 204\n");
                    exit(3);
                }
                else {
                    BSTInsert(&GlobalBody, token.lex, tmp);
                }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

                DLInsertLast(&zoznam, token);
                token = get_next_token(stdin);
                if(token.type == t_LEFT_BRACKET){
                    token = get_next_token(stdin);
                    //printf("IDEM DO PARAMS\n");
                    if(params()){
                        //printf("TOKEN TYPE za celym params %d\n",token.type);
                        token = get_next_token(stdin);
                        //printf("IDEM TESTOVAT COLON\n");
                        if(token.type == t_COLON){
                            DLInsertLast(&zoznam, token);
                            if(token.type != t_EOL){
                                token = get_next_token(stdin);
                            }
                            if(token.type == t_EOL){
                                token = get_next_token(stdin);
                                if(token.type == t_INDENT){
                                    DLInsertLast(&zoznam, token);
                                    token = get_next_token(stdin);
                                    //printf("IDEM TESTOVAT FUNC_LIST\n");
                                    if(func_list()){
                                        result = true;
                                        //token = get_next_token(stdin);
                                    }
                                    else{
                                        fprintf(stderr, "Syntax error192.\n");
                                        exit(2);
                                    }
                                }
                                else{
                                    fprintf(stderr, "Syntax error.198\n");
                                    exit(2);
                                }
                            }
                            else{
                                fprintf(stderr, "Syntax error.203\n");
                                exit(2);
                            }
                        }
                        else{
                            //printf("TUSOM\n");
                            fprintf(stderr, "Syntax error.208\n");
                            exit(2);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error.213\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error.218\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error223.\n");
                exit(2);
            }
            scope = 0;
            break;
            
        case t_IDENTIFIER:
        case t_FLOAT:
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
        case t_STRING:
        case t_IF:
        case t_WHILE:
        case t_PASS:
            // Rule: <statement>  ->  <command>
            if(command()){
                result = true;
                //token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error.241\n");
                exit(2);
            }
            break;
        default:
        fprintf(stderr, "Syntax error statement.\n");
        exit(2);
    }
    return result;
}

bool params(){
    bool result = false;
    switch(token.type){
        case t_IDENTIFIER:
        case t_STRING:
        case t_FLOAT:
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
            // Rule: <params>  ->  ID <param_n>
            param_count++;
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(param_n()){
                result = true;
                //printf("TOKEN TYPE v params pred%d\n",token.type);
                //token = get_next_token(stdin);
                //printf("TOKEN TYPE v params po %d\n",token.type);
            }
            else{
                fprintf(stderr, "Syntax error261.\n");
                exit(2);
            }
            break;
        case t_RIGHT_BRACKET:
            // Rule: <params>  ->  )
            DLInsertLast(&zoznam, token);
            result = true;
            //token = get_next_token(stdin);
           // printf("I WAS AT RIGHT BRACKET IN params()");
            break;
        default:
        //printf("TOKEN TYPE v params pred  %d   %s\n",token.type,token.lex);
        fprintf(stderr, "Syntax error params.\n");
        exit(2);
    }
    return result;
}

bool func_list(){
    //printf("FUNCTON LIST \n");
    bool result = false;
    switch(token.type){
        case t_EOF:
            return true;
        case t_EOL:
            // Rule: <func-list>  ->  EOL <func-list>
            token = get_next_token(stdin);
            if(func_list()){
                result = true;
                //token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error.286\n");
                exit(2);
            }
            break;
        case t_DEDENT:
            // Rule: <func-list>  ->  DEDENT
            DLInsertLast(&zoznam, token);
            result = true;
            token = eol;
            //token = get_next_token(stdin);
            break;
        case t_IDENTIFIER:
        case t_FLOAT:
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
        case t_STRING:
        case t_IF:
        case t_WHILE:
        case t_PASS:
        case t_RETURN:
            // Rule: <func-list>  ->  <func-command> EOL <func-list>
            if(func_cmd()){
                //printf("TOKEN TYPE v if func_cmd pred %d\n",token.type);
                if(token.type == t_EOF){
                    return true;
                }
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                //printf("TOKEN TYPE v if func_cmd po %d\n",token.type);
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(func_list()){
                        result = true;
                        //token = get_next_token(stdin);
                    }
                    else{
                        fprintf(stderr, "Syntax error 314.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 319.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 324.\n");
                exit(2);
            }
            break;
        default:
        fprintf(stderr, "Syntax error func-list.\n");
        exit(2);
    }
    return result;
}

bool command(){
    bool result = false;
    switch(token.type){
        case t_FLOAT:
            // Rule: <command>  ->  FLOAT
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 342.\n");
                exit(2);
            }
            result = true;
            break;
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
            // Rule: <command>  ->  INT
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 355.\n");
                exit(2);
            }
            result = true;
            break;
        case t_STRING:
            // Rule: <command>  ->  STRING
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 367.\n");
                exit(2);
            }
            result = true;
            break;
        case t_IDENTIFIER:
            // Rule: <command>  ->  ID <AS/FUN/EX>
            help_t2 = token;
            token = get_next_token(stdin);
            if((token.type != t_ASSIGN) && (token.type != t_LEFT_BRACKET)){
                if(is_expression2()){
                    evaluation(&psa_list);
                    DLDisposeList(&psa_list);
                }
                else{
                    fprintf(stderr, "Syntax error 36 382.\n");
                    exit(2);
                }
            }
            if(token.type == t_LEFT_BRACKET){
                help_t2.type = t_FUNCTION_CALL;
            }
            DLInsertLast(&zoznam, help_t2);
            
            if(ass_func_expr()){
                result = true;
                //token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error 394.\n");
                exit(2);
            }
            break;
        case t_IF:
            // Rule: <command>  ->  if (expression) : EOL INDENT <if-list>
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(is_expression_colon()){
                //printf("is expression\n");
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Invalid expression after \"if\" keyword.\n");
                exit(2);
            }
            if(token.type == t_COLON){
                DLInsertLast(&zoznam, token);
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(token.type == t_INDENT){
                        token = get_next_token(stdin);
                        if(if_list()){
                            result = true;
                            //token = get_next_token(stdin);
                        }
                        else{
                            fprintf(stderr, "Syntax error 422.\n");
                            exit(2);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error 427.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 427432.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 437.\n");
                exit(2);
            }
            break;
        case t_WHILE:
            // Rule: <command>  ->  while (expression) : EOL INDENT <else-list>
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(is_expression_colon()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Invalid expression after \"while\" keyword.\n");
                exit(2);
            }
            if(token.type == t_COLON){
                DLInsertLast(&zoznam, token);
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(token.type == t_INDENT){
                        token = get_next_token(stdin);
                        if(else_list()){
                            result = true;
                            //token = get_next_token(stdin);
                        }
                        else{
                            fprintf(stderr, "Syntax error 465.\n");
                            exit(2);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error 465.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 465.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 465.\n");
                exit(2);
            }
            break;
        case t_PASS:
            // Rule: <command>  ->  pass
            DLInsertLast(&zoznam, token);
            result = true;
            //token = get_next_token(stdin);
            break;
        default:
        fprintf(stderr, "Syntax error command.\n");
        exit(2);
    }
    return result;
}

bool param_n(){
    //printf("VOLAL SOM PARAMN\n");
    bool result = false;
    switch (token.type){
        case t_COMMA:
            // Rule: <param_n>  ->  , ID <param_n>
            token = get_next_token(stdin);
            if((token.type == t_IDENTIFIER) ||
               (token.type == t_STRING) ||
               (token.type == t_FLOAT) ||
               (token.type == t_INT_ZERO) ||
               (token.type == t_INT_NON_ZERO)){
                DLInsertLast(&zoznam, token);
                token = get_next_token(stdin);
                param_count++;
                if(param_n()){
                    result = true;
                    //printf("TOKEN TYPE v param_n pred nextoken%d\n",token.type);
                    //token = get_next_token(stdin);
                    //printf("TOKEN TYPE v param_n za nextotoken%d\n",token.type);
                    
                }
                else{
                    fprintf(stderr, "Syntax error 508.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 513.\n");
                exit(2);
            }
            break;
        case t_RIGHT_BRACKET:
            // Rule: <param_n>  ->  )
            DLInsertLast(&zoznam, token);
            result = true;
            //printf("TOKEN TYPE param_n bracket %d\n",token.type);
            //token = get_next_token(stdin);
            //printf("TOKEN TYPEparam_n bracket %d\n",token.type);
            //printf("I WAS AT RIGHT BRACKET\n");
            break;
        default:
        fprintf(stderr, "Syntax error param_n.\n");
        exit(2);
    }
    
    return result;
}
                                       
bool func_cmd(){
    //printf("som v func_cmd\n");
    bool result = true;
    switch(token.type){
        case t_FLOAT:
            // Rule: <func-command>  ->  FLOAT
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 536.\n");
                exit(2);
            }
            result = true;
            break;
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
            // Rule: <func-command>  ->  INT
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 53549.\n");
                exit(2);
            }
            result = true;
            break;
        case t_STRING:
            // Rule: <func-command>  ->  STRING
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 561.\n");
                exit(2);
            }
            result = true;
            break;
        case t_IDENTIFIER:
            // Rule: <func-command>  ->  ID <AS/FUN/EX>
            help_t2 = token;

            //printf("token type pred nexttoken %d\n",token.type);
            token = get_next_token(stdin);
            //printf("token type po nexttoken %d\n",token.type);
            if((token.type != t_ASSIGN) && (token.type != t_LEFT_BRACKET)){
                //printf("token type v ife ze neni ( a neni t_equal = %d\n",token.type);
                if(is_expression2()){
                    evaluation(&psa_list);
                    DLDisposeList(&psa_list);
                }
                else{
                    fprintf(stderr, "Syntax error 576.\n");
                    exit(2);
                }
            }
            else{
                DLInsertLast(&zoznam, help_t2);
            }
            if(f_ass_func_expr()){
                result = true;
                //printf("token type v if f_ass pred  %d\n",token.type);
                //token = get_next_token(stdin);
                //printf("token type  v if f_ass po %d\n",token.type);
            }
            else{
                //printf("token type v else pri IDENT v func_cmd() %d\n",token.type);
                fprintf(stderr, "Syntax error 601.\n");
                exit(2);
            }
            break;
        case t_IF:
            // Rule: <func-command>  ->  if (expression) : EOL INDENT <if-func-list>
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(is_expression_colon()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Invalid expression after \"if\" keyword.\n");
                exit(2);
            }
            if(token.type == t_COLON){
                DLInsertLast(&zoznam, token);
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(token.type == t_INDENT){
                        token = get_next_token(stdin);
                        if(if_f_list()){
                            result = true;
                            //token = get_next_token(stdin);
                        }
                        else{
                            fprintf(stderr, "Syntax error 616.\n");
                            exit(2);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error 616.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 616.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 616.\n");
                exit(2);
            }
            break;
        case t_WHILE:
            // Rule: <func-command>  ->  while (expression) : EOL INDENT <else-func-list>
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(is_expression_colon()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Invalid expression after \"while\" keyword.\n");
                exit(2);
            }
            if(token.type == t_COLON){
                DLInsertLast(&zoznam, token);
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(token.type == t_INDENT){
                        token = get_next_token(stdin);
                        if(else_f_list()){
                            result = true;
                            //token = get_next_token(stdin);
                        }
                        else{
                            fprintf(stderr, "Syntax error 659.\n");
                            exit(2);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error 659.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 659.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 659.\n");
                exit(2);
            }
            break;
        case t_PASS:
            // Rule: <func-command>  ->  pass
            DLInsertLast(&zoznam, token);
            result = true;
            //token = get_next_token(stdin);
            break;
        case t_RETURN:
            // Rule: <func-command>  ->  return (expression)
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Expected expression.\n");
                exit(2);
            }
            result = true;
            break;
        default:
        fprintf(stderr, "Syntax error func-cmd.\n");
        exit(2);
    }
    //printf("VYCHADZAM Z FUNC_CMD  a tokentype je %d\n",token.type);
    return result;
}

bool ass_func_expr(){
    //printf("SOM V ASS\n");
     //printf("pri cvhode to ASS je token  %d\n",token.type);
    bool result = false;
    switch(token.type){
        case t_ASSIGN:
            // Rule: <AS/FUN/EX>  ->  =  <EXPR/ID>

            if (scope == 1) {
                if (!(BSTSearchLocal(LocalVariables, help_t2.lex))) {
                    if(!(BSTSearch(GlobalBody, help_t2.lex, &tmp_v))) {
                        BSTInsertLocal(&LocalVariables, help_t2.lex);
                    }
                }
            }

            if (scope == 0) {
                if (!(BSTSearch(GlobalBody, help_t2.lex, &tmp_v))) {
                    BSTInsert(&GlobalBody, help_t2.lex, tmp_v);
                }
            }

            //DLInsertLast(&zoznam, help_t2);
            DLInsertLast(&zoznam, token);
            //printf("token type pred nexttoken %d\n",token.type);
            token = get_next_token(stdin);
            //printf("token type po nexttoken %d\n",token.type);
            if(expr_id()){
                result = true;
                //printf("token type pred nexttoken %d\n",token.type);
                //token = get_next_token(stdin);
                //printf("token type ponexttoken %d\n",token.type);
            }
            else{
                fprintf(stderr, "Syntax error 714.\n");
                exit(2);
            }
            break;
        case t_LEFT_BRACKET:
            // Rule: <AS/FUN/EX>  ->  ( <params>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (!(BSTSearch(GlobalBody, help_t2.lex, &tmp))){
                fprintf(stderr, "Semantic error 784\n");
                exit(3);
            } /*else {
                if (!(tmp.defined)) {
                    fprintf(stderr, "Semantic error 788\n");
                    exit(3);
                } else {
                   if (!(tmp.is_function)) {
                        fprintf(stderr, "Syntactic error 792\n");
                        exit(2);
                    }
                }


            }*/
            
//////////////////////////////////////////////////////////////////////////////////////////////////////////////            
            DLInsertLast(&zoznam, token);
            token = get_next_token(stdin);
            if(params()){
                result = true;
                token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error 726.\n");
                exit(2);
            }
            break;
        case t_EOL:
            // Rule: <AS/FUN/EX>  ->  ε
            result = true;
            break;
        default:
        fprintf(stderr, "Syntax error ass_func_expr.\n");
        exit(2);
    }
    //printf("VYCHADZAM Z ASS  a tokentype je %d\n",token.type);
    return result;
}
                                       
bool f_ass_func_expr(){
     //printf("SOM V F_ASS\n");
     //printf("pri cvhode to f-ass je token  %d\n",token.type);
   bool result = false;
   switch(token.type){
       case t_ASSIGN:

            if (scope == 1) {
                if (!(BSTSearchLocal(LocalVariables, help_t2.lex))) {
                    if(!(BSTSearch(GlobalBody, help_t2.lex, &tmp_v))) {
                        BSTInsertLocal(&LocalVariables, help_t2.lex);
                    }
                }
            }

            if (scope == 0) {
                if (!(BSTSearch(GlobalBody, help_t2.lex, &tmp_v))) {
                    BSTInsert(&GlobalBody, help_t2.lex, tmp_v);
                }
            }
           // Rule: <AS/FUN/EX>  ->  =  <EXPR/ID>
           DLInsertLast(&zoznam, help_t2);
           DLInsertLast(&zoznam, token);
           //printf("token type pred  v f_ass %d\n",token.type);
           token = get_next_token(stdin);
           //printf("token type po v f_ass %d\n",token.type);
           if(expr_id()){
               result = true;
              //printf("token type if expr_id pred  %d\n",token.type);
                //token = get_next_token(stdin);
                //printf("token type if expr_id po  %d\n",token.type);
                
           }
           break;
       case t_LEFT_BRACKET:
           // Rule: <AS/FUN/EX>  ->  ( <params>

                remember = false;
            if (!(BSTSearch(GlobalBody, help_t2.lex, &tmp))){
                remember = true;
            } else {
                   if (!(tmp.is_function)) {
                        fprintf(stderr, "Syntactic error\n");
                        exit(2);
                    }   
                }

           token = get_next_token(stdin);
           if(params()){
               if (remember) {
                global_t tmp2;
                tmp2.is_function = true;
                tmp2.defined = false;
                tmp2.num_of_params = param_count;
                param_count = 0;    
               }
               result = true;
               token = get_next_token(stdin);
           }
           break;
       case t_EOL:
           // Rule: <AS/FUN/EX>  ->  ε
           result = true;
           break;
        default:
        fprintf(stderr, "Syntax error f_ass_func_expr.\n");
        exit(2);
   }
   //printf("VYCHADZAM Z F_ASS  a tokentype je %d a returnujem %d\n",token.type,result);
   return result;
}
                                       
bool if_list(){
    bool result = false;
    switch(token.type){
        case t_EOL:
            // Rule: <if-list>  ->  EOL <if-list>
            token = get_next_token(stdin);
            if(if_list()){
                result = true;
                //token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error 777.\n");
                exit(2);
            }
            break;
        case t_DEDENT:
            // Rule: <if-list>  ->  DEDENT else : EOL INDENT <command> EOL <else-list>
            token = get_next_token(stdin);
            if(token.type == t_ELSE){
                DLInsertLast(&zoznam, token);
                token = get_next_token(stdin);
                if(token.type == t_COLON){
                    DLInsertLast(&zoznam, token);
                    if(token.type != t_EOL){
                        token = get_next_token(stdin);
                    }
                    if(token.type == t_EOL){
                        token = get_next_token(stdin);
                        if(token.type == t_INDENT){
                            token = get_next_token(stdin);
                            if(command()){
                                if(token.type != t_EOL){
                                    token = get_next_token(stdin);
                                }
                                if(token.type == t_EOL){
                                    token = get_next_token(stdin);
                                    if(else_list()){
                                        result = true;
                                        //token = get_next_token(stdin);
                                    }
                                    else{
                                        fprintf(stderr, "Syntax error 803.\n");
                                        exit(2);
                                    }
                                }
                                else{
                                    fprintf(stderr, "Syntax error 803.\n");
                                    exit(2);
                                }
                            }
                            else{
                                fprintf(stderr, "Syntax error 803.\n");
                                exit(2);
                            }
                        }
                        else{
                            fprintf(stderr, "Syntax error 803.\n");
                            exit(2);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error 803.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 803.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 803.\n");
                exit(2);
            }
            break;
        case t_IDENTIFIER:
        case t_FLOAT:
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
        case t_STRING:
        case t_IF:
        case t_WHILE:
        case t_PASS:
            // Rule: <if-list>  ->  <command> EOL <if-list>
            if(command()){
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(if_list()){
                        result = true;
                        //token = get_next_token(stdin);
                    }
                    else{
                        fprintf(stderr, "Syntax error 851.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 852.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 853.\n");
                exit(2);
            }
            break;
        default:
        fprintf(stderr, "Syntax error if_list.\n");
        exit(2);
    }
    return result;
}
                                       
bool else_list(){
    bool result = false;
    switch(token.type){
        case t_EOF:
            result = true;
            token = eol;
            break;
        case t_EOL:
            // Rule: <else-list>  ->  EOL <else-list>
            token = get_next_token(stdin);
            if(else_list()){
                result = true;
                //token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error 884.\n");
                exit(2);
            }
            break;
        case t_DEDENT:
            // Rule: <else-list>  ->  DEDENT
            DLInsertLast(&zoznam, token);
            result = true;
            token = eol;
            break;
        case t_IDENTIFIER:
        case t_FLOAT:
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
        case t_STRING:
        case t_IF:
        case t_WHILE:
        case t_PASS:
            // Rule: <else-list>  ->  <command> EOL <else-list>
            if(command()){
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(else_list()){
                        result = true;
                        //token = get_next_token(stdin);
                    }
                    else{
                        fprintf(stderr, "Syntax error 911.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 910.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 913.\n");
                exit(2);
            }
            break;
        default:
        fprintf(stderr, "Syntax error else_list.\n");
        exit(2);
    }
    return result;
}
                                       
bool if_f_list(){
    bool result = false;
    switch(token.type){
        case t_EOL:
            // Rule: <if-func-list>  ->  EOL <if-func-list>
            token = get_next_token(stdin);
            if(if_f_list()){
                result = true;
                //token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error 941.\n");
                exit(2);
            }
            break;
        case t_DEDENT:
            // Rule: <if-func-list>  ->  DEDENT else : EOL INDENT <func-command> EOL <else-func-list>
            token = get_next_token(stdin);
            if(token.type == t_ELSE){
                DLInsertLast(&zoznam, token);
                token = get_next_token(stdin);
                if(token.type == t_COLON){
                    DLInsertLast(&zoznam, token);
                    if(token.type != t_EOL){
                        token = get_next_token(stdin);
                    }
                    if(token.type == t_EOL){
                        token = get_next_token(stdin);
                        if(token.type == t_INDENT){
                            token = get_next_token(stdin);
                            if(func_cmd()){
                                if(token.type != t_EOL){
                                    token = get_next_token(stdin);
                                }
                                if(token.type == t_EOL){
                                    token = get_next_token(stdin);
                                    if(else_f_list()){
                                        result = true;
                                        //token = get_next_token(stdin);
                                    }
                                    else{
                                        fprintf(stderr, "Syntax error 960.\n");
                                        exit(2);
                                    }
                                }
                                else{
                                    //printf("tokentype je %d \n",token.type);
                                    fprintf(stderr, "Syntax error 961.\n");
                                    exit(2);
                                }
                            }
                            else{
                                fprintf(stderr, "Syntax error 962.\n");
                                exit(2);
                            }
                        }
                        else{
                            fprintf(stderr, "Syntax error 963.\n");
                            exit(2);
                        }
                    }
                    else{
                        fprintf(stderr, "Syntax error 964.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 965.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 966.\n");
                exit(2);
            }
            break;
        case t_IDENTIFIER:
        case t_FLOAT:
        case t_INT_ZERO:
        case t_INT_NON_ZERO:
        case t_STRING:
        case t_IF:
        case t_WHILE:
        case t_PASS:
        case t_RETURN:
            // Rule: <if-func-list>  ->  <func-command> EOL <if-func-list>
            if(func_cmd()){
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(if_f_list()){
                        result = true;
                        //token = get_next_token(stdin);
                    }
                    else{
                        fprintf(stderr, "Syntax error 1020.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 1020.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 1020.\n");
                exit(2);
            }
            break;
        default:
        fprintf(stderr, "Syntax error if_f_list.\n");
        exit(2);
    }
    return result;
}

bool else_f_list(){
    bool result = false;
    switch(token.type){
        case t_EOF:
            result = true;
            token = eol;
            break;
        case t_EOL:
            // Rule: <else-func-list>  ->  EOL <else-func-list>
            token = get_next_token(stdin);
            if(else_f_list()){
                result = true;
                //token = get_next_token(stdin);
            }
            else{
                fprintf(stderr, "Syntax error 1049.\n");
                exit(2);
            }
            break;
        case t_DEDENT:
            // Rule: <else-func-list>  ->  DEDENT
            DLInsertLast(&zoznam, token);
            result = true;
            token = eol;
            break;
        case t_IDENTIFIER:
        case t_FLOAT:
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
        case t_STRING:
        case t_IF:
        case t_WHILE:
        case t_PASS:
        case t_RETURN:
            // Rule: <else-func-list>  ->  <func-command> EOL <else-func-list>
            if(func_cmd()){
                if(token.type != t_EOL){
                    token = get_next_token(stdin);
                }
                if(token.type == t_EOL){
                    token = get_next_token(stdin);
                    if(else_f_list()){
                        result = true;
                        //token = get_next_token(stdin);
                    }
                    else{
                        fprintf(stderr, "Syntax error 1078.\n");
                        exit(2);
                    }
                }
                else{
                    fprintf(stderr, "Syntax error 1078.\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr, "Syntax error 1078.\n");
                exit(2);
            }
            break;
        default:
        fprintf(stderr, "Syntax error else_f_list.\n");
        exit(2);
    }
    return result;
}
                                       
bool expr_id(){
    //printf("SOM V EXPR_ID()\n");
    bool result = false;
    switch(token.type){
        case t_LEFT_BRACKET:
            //printf("SOM TU\n");
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
                result = true;
            }
            else{
                fprintf(stderr, "Expected expression.\n");
                exit(2);
            }
        case t_IDENTIFIER:
            // Rule: <EXPR/ID>  ->  ID ( <params>
            help_t = token;
            //printf("TOKEN TYPE v is_expression_id pred %d\n",token.type);
            token = get_next_token(stdin);
            //printf("TOKEN TYPE v is_expression_id po %d\n",token.type);
            if(token.type != t_LEFT_BRACKET){
                if(is_expression()){
                    //printf("IDEM DO PSA\n");

                    evaluation(&psa_list);
                    DLDisposeList(&psa_list);
                    result =true;
                }
                else{
                    fprintf(stderr, "Invalid syntax v 1142.\n");
                    exit(2);
                }
            }
            else {
                //printf("%s\n",help_t.lex);
                if (!(BSTSearch(GlobalBody, help_t.lex, &tmp))) {
                    //fprintf(stderr, "Semantic erro 1385r\n");
                    //exit(3);
                    ;
                } else {
                    if (!(tmp.defined)) {
                     //printf("%d   %d     %d",tmp.defined,tmp.is_function,tmp.num_of_params);   
                    //fprintf(stderr, "Semantic error 1389\n");
                    //exit(3);
                    }
                }

                //printf("INEDEM DO PSA\n");
                help_t.type = t_FUNCTION_CALL;
                DLInsertLast(&zoznam, help_t);
                DLInsertLast(&zoznam, token);
                token = get_next_token(stdin);
                
                if(params()){
                    result = true;
                    token = get_next_token(stdin);
                }
                else{
                    fprintf(stderr, "Syntax error 1121.\n");
                    exit(2);
                }
            }

            break;
        case t_FLOAT:
            // Rule: <EXPR/ID>  ->  FLOAT
             //printf("SOM FLOAT\n");
            if(is_expression_eol()){
               /* DLFirst(&psa_list);
                while (psa_list.Act->lptr != NULL) {

                    //printf("%d\n", psa_list.Act->data)
                }*/
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 1133.\n");
                exit(2);
            }
            result = true;
            break;
        case t_INT_NON_ZERO:
        case t_INT_ZERO:
            // Rule: <EXPR/ID>  ->  INT
            //printf("SOM INT\n");
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error 1146.\n");
                exit(2);
            }
            result = true;
            break;
        case t_STRING:
        //printf("SOM STRING\n");
            // Rule: <EXPR/ID>  ->  STRING
            if(is_expression_eol()){
                evaluation(&psa_list);
                DLDisposeList(&psa_list);
            }
            else{
                fprintf(stderr, "Syntax error.5\n");
                exit(2);
            }
            result = true;
            break;
        default:
        fprintf(stderr, "Syntax error expr_id.\n");
        exit(2);
    }
    //printf("VYCHADZAM Z EXPR_ID  a tokentype je %d  a returnujem %d\n",token.type,result);
    return result;
}
                                       
bool is_expression_eol(){
    //printf("SOM V is_EXPR_EOL()\n");
    //printf("pri vchode do is_EXPR_EOL tokentype je %d\n",token.type);
    DLInitList(&psa_list);
    DLInsertFirst(&psa_list, trash);
    while(token.type != t_EOL){
        if((token.type != t_PLUS)
           && (token.type != t_MINUS)
           && (token.type != t_DIVIDE_I)
           && (token.type != t_DIVIDE_F)
           && (token.type != t_MULTIPLY)
           && (token.type != t_GREATER)
           && (token.type != t_GREATEROREQUAL)
           && (token.type != t_LESS)
           && (token.type != t_LESSOREQUAL)
           && (token.type != t_EQUAL)
           && (token.type != t_NOT_EQUAL)
           && (token.type != t_IDENTIFIER)
           && (token.type != t_STRING)
           && (token.type != t_FLOAT)
           && (token.type != t_INT_ZERO)
           && (token.type != t_INT_NON_ZERO)
           && (token.type != t_NONE)
           && (token.type != t_LEFT_BRACKET)
           && (token.type != t_RIGHT_BRACKET)){
            return false;
//            //printf("VYCHADZAM Z is_EXPR_EOL ako FASLE a tokentype je %d\n",token.type);
        }
        DLInsertLast(&psa_list, token);
        //printf("TOKEN TYPE v is_expression_eol pred %d\n",token.type);
        token = get_next_token(stdin);
        //printf("TOKEN TYPE v is_expression_eol po %d\n",token.type);
        
    }
    
    //printf("VYCHADZAM Z is_EXPR_EOL ako TRUE a tokentype je %d\n",token.type);
    return true;
}

bool is_expression_colon(){
    DLInitList(&psa_list);
    DLInsertFirst(&psa_list, trash);
    while(token.type != t_COLON){
        if((token.type != t_PLUS)
           && (token.type != t_MINUS)
           && (token.type != t_DIVIDE_I)
           && (token.type != t_DIVIDE_F)
           && (token.type != t_MULTIPLY)
           && (token.type != t_GREATER)
           && (token.type != t_GREATEROREQUAL)
           && (token.type != t_LESS)
           && (token.type != t_LESSOREQUAL)
           && (token.type != t_EQUAL)
           && (token.type != t_NOT_EQUAL)
           && (token.type != t_IDENTIFIER)
           && (token.type != t_STRING)
           && (token.type != t_FLOAT)
           && (token.type != t_INT_ZERO)
           && (token.type != t_INT_NON_ZERO)
           && (token.type != t_NONE)
           && (token.type != t_LEFT_BRACKET)
           && (token.type != t_RIGHT_BRACKET)){
            return false;
        }
        DLInsertLast(&psa_list, token);
        token = get_next_token(stdin);
    }
    //printf("VYCHADZAM Z is_EXPR_COLON  a tokentype je %d\n",token.type);
    return true;
}

bool is_expression(){
    //printf("SOM V is_EXPR()\n");
    //printf("pri vchode do is_EXPR tokentype je %d\n",token.type);
    DLInitList(&psa_list);
    DLInsertFirst(&psa_list, trash);
    if((help_t.type != t_PLUS)
       && (help_t.type != t_MINUS)
       && (help_t.type != t_DIVIDE_I)
       && (help_t.type != t_DIVIDE_F)
       && (help_t.type != t_MULTIPLY)
       && (help_t.type != t_GREATER)
       && (help_t.type != t_GREATEROREQUAL)
       && (help_t.type != t_LESS)
       && (help_t.type != t_LESSOREQUAL)
       && (help_t.type != t_EQUAL)
       && (help_t.type != t_NOT_EQUAL)
       && (help_t.type != t_IDENTIFIER)
       && (help_t.type != t_STRING)
       && (help_t.type != t_FLOAT)
       && (help_t.type != t_INT_ZERO)
       && (help_t.type != t_INT_NON_ZERO)
       && (help_t.type != t_NONE)
       && (token.type != t_LEFT_BRACKET)
       && (token.type != t_RIGHT_BRACKET)){
        fprintf(stderr, "Invalid syntax 1246.\n");
        exit(2);
    }
    DLInsertLast(&psa_list, help_t);
    while(token.type != t_EOL){
        if((token.type != t_PLUS)
           && (token.type != t_MINUS)
           && (token.type != t_DIVIDE_I)
           && (token.type != t_DIVIDE_F)
           && (token.type != t_MULTIPLY)
           && (token.type != t_GREATER)
           && (token.type != t_GREATEROREQUAL)
           && (token.type != t_LESS)
           && (token.type != t_LESSOREQUAL)
           && (token.type != t_EQUAL)
           && (token.type != t_NOT_EQUAL)
           && (token.type != t_IDENTIFIER)
           && (token.type != t_STRING)
           && (token.type != t_FLOAT)
           && (token.type != t_INT_ZERO)
           && (token.type != t_INT_NON_ZERO)
           && (token.type != t_NONE)
           && (token.type != t_LEFT_BRACKET)
           && (token.type != t_RIGHT_BRACKET)){
            fprintf(stderr, "Invalid syntax 1268.\n");
            exit(2);
        }
        DLInsertLast(&psa_list, token);
        token = get_next_token(stdin);
    }
    //printf("VYCHADZAM Z is_EXPR ako TRUE a tokentype je %d\n",token.type);
    return true;
}

bool is_expression2(){
    DLInitList(&psa_list);
    DLInsertFirst(&psa_list, trash);
    if((help_t2.type != t_PLUS)
       && (help_t2.type != t_MINUS)
       && (help_t2.type != t_DIVIDE_I)
       && (help_t2.type != t_DIVIDE_F)
       && (help_t2.type != t_MULTIPLY)
       && (help_t2.type != t_GREATER)
       && (help_t2.type != t_GREATEROREQUAL)
       && (help_t2.type != t_LESS)
       && (help_t2.type != t_LESSOREQUAL)
       && (help_t2.type != t_EQUAL)
       && (help_t2.type != t_NOT_EQUAL)
       && (help_t2.type != t_IDENTIFIER)
       && (help_t2.type != t_STRING)
       && (help_t2.type != t_FLOAT)
       && (help_t2.type != t_INT_ZERO)
       && (help_t2.type != t_INT_NON_ZERO)
       && (help_t2.type != t_NONE)
       && (token.type != t_LEFT_BRACKET)
       && (token.type != t_RIGHT_BRACKET)){
        fprintf(stderr, "Invalid syntax 1297.\n");
        exit(2);
    }
    DLInsertLast(&psa_list, help_t2);
    while(token.type != t_EOL){
        if((token.type != t_PLUS)
           && (token.type != t_MINUS)
           && (token.type != t_DIVIDE_I)
           && (token.type != t_DIVIDE_F)
           && (token.type != t_MULTIPLY)
           && (token.type != t_GREATER)
           && (token.type != t_GREATEROREQUAL)
           && (token.type != t_LESS)
           && (token.type != t_LESSOREQUAL)
           && (token.type != t_EQUAL)
           && (token.type != t_NOT_EQUAL)
           && (token.type != t_IDENTIFIER)
           && (token.type != t_STRING)
           && (token.type != t_FLOAT)
           && (token.type != t_INT_ZERO)
           && (token.type != t_INT_NON_ZERO)
           && (token.type != t_NONE)
           && (token.type != t_LEFT_BRACKET)
           && (token.type != t_RIGHT_BRACKET)){
            fprintf(stderr, "Invalid syntax. 1319\n");
            exit(2);
        }
        DLInsertLast(&psa_list, token);
        token = get_next_token(stdin);
    }
    //printf("VYCHADZAM Z is_EXPR_2 a tokentype je %d\n",token.type);
    return true;
}
