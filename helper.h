//
//  helper.h
//  parser
//
//  Created by Damián Krajňák on 30/11/2019.
//  Copyright © 2019 Damián Krajňák. All rights reserved.
//

#ifndef helper_h
#define helper_h

#include <stdio.h>




typedef enum  {
    R_placehoder, // point is to have one rule that is 0 to ptimize genrating
    R_PLUS, // E -> E + E 0
    R_MINUS, // E -> E - E 1
    R_MUL, // E -> E * E 2
    R_DIV, // E -> E / E 3
    R_IDIV, // E -> E // E 4
    R_EQUAL, // E -> E = E 5
    R_NEQUAL, // E -> E != E 6
    R_MOE, // E -> E >= E  7
    R_LOE, // E -> E <= E 8
    R_LESS, // E -> E < E 9
    R_MORE, // E -> E > E 10
    R_EBRACES, // E -> (E) 11
    R_OP, // E -> i  12
    R_NOTDEFINED // Nedefinovane pravidlo 13

} psa_rules;



    
typedef enum PSA_SYMBOLS {

    T_PLUS, T_MINUS, // + -
    T_MUL, T_DIV, T_IDIV, // * / //
    T_LEFT_PARENTHESIS, T_RIGHT_PARENTHESIS, // ( )
    T_EQUAL, T_NEQUAL, T_MOE, T_LOE, T_LESS, T_MORE, // = != >= <= < >
    T_ID, // identifikator
    T_DOLLAR, T_RED, T_NON_TERM // $ , neterminal, znak redukcie

} psa_symbols;

#endif /* helper_h */
