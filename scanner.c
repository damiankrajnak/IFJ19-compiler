/*
**    Part of IFJ Project 2019/2020
**    Author: Simon Fenko xfenko01
*/


#include "stack.h"
#include "scanner.h"

bool is_dedent = false;
bool First_token = false;
char current_token[100];
int current_token_position = 0;
char current_char;

tStack indent_s;
int spacecount = 0;
int i;

/* Vymazavanie current_tokenu (napr. chodia medzery-vtedy ich vyhodime a
pokracujeme dalej)*/

/* int main()
{
    stackInit(&indent_s);
    stackPush(&indent_s, 0);
    stackTop(&indent_s, &i);
    while (1)
    {
        TOKEN a;
        a = get_next_token(stdin);
        //printf("%d\n", a.type );
        if (a.type == t_EOF)
        {
            break;
        }
    }
    return 0;
} */

void delete_string(void)
{
    current_token[0] = 0x00;
    current_token_position = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*najprv vytiahne znak zo suboru a hodi ho do current_char a prilepi ho
 na koniec stringu, do ktoreho sa uklada sučasny načitavany token, zvyši
 poziciu stringu (dlžku stringu a zakonči ho 0)
*/
 
void load_c(FILE* text)
{
    current_char = getc(text);
    current_token[current_token_position] = current_char;
    current_token_position++;
    current_token[current_token_position] = 0x00;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* zavola sa unload a zaroven spravi ungetc - hladačik sa posunie o jedno
 dozadu a odreze posledny character zo stringu c current_token */

void unload_c(FILE *text)
{
    ungetc(current_char,text);
    current_token_position--;
    current_token[current_token_position] = 0x00;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* alokovanie miesta pre string v tokene */

void alloc(int length, TOKEN* token)
{
    token->lex = (char*) malloc(length * sizeof(char));
}
/*
void alloc2(int length, TOKEN* token)
{
    token->lex = (char*) malloc((length-2) * sizeof(char));
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* najprv alokujeme miesto pre textoy obsah tokenu, potom ho tam skopirujeme
 z current_token, potom skopirujeme type a vymazeme current_token*/
/*
void end_token2(int type, TOKEN* token)
{
    alloc(current_token_position+1, token);
    char * a = current_token;
    a = current_token + sizeof(char);
    *(&a[strlen(a)-1]) = '\0';
    strcpy(token->lex, current_token);
    token->type = type;
    //printf("token %d lex %s\n",token->type, token->lex);
    delete_string();
}
*/

void end_token(int type, TOKEN* token)
{
    alloc(current_token_position+1, token);
    strcpy(token->lex, current_token);
    token->type = type;
    if(token->type == t_FLOAT){
        sprintf(token->lex, "%d", (int)token->lex);
        sprintf(token->lex, "%a", (double)*(token->lex));
    }
    //printf("token %d lex %s\n",token->type, token->lex);
    delete_string();
}

TOKEN get_next_token(FILE* text)
{

    
    
       // printf("HELOOO ++++++++++++++++++++++++");
    
    

    TOKEN token;
    static int state;
    if(state != IND_DED){
        state = START;
    }
    
    while (true)
    {
        load_c(text);
        if (current_char == EOF && strlen(current_token) == 1 )
        {
            token.type = t_EOF;
            return token;
        }
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int i;
        stackTop(&indent_s, &i);
        switch (state)
        {
            case START:
                if (current_char == ' ' && !First_token)
                {
                    state = START;
                    delete_string();
                }
                else if (current_char == ' ' && First_token)
                {
                    state = IND_DED;
                    spacecount++;
                }
                else if (current_char == '<')
                {
                    state = t_LESS;
                }
                else if (current_char == '>')
                {
                    state = t_GREATER;
                }
                else if (current_char == '=')
                {
                    state = t_ASSIGN;
                }
                else if (current_char == '!')
                {
                    state = EXLAMATION;
                }
                else if (current_char == ',')
                {
                    end_token(t_COMMA, &token);
                    return token;
                    break;
                }
                else if (current_char == '(')
                {
                    end_token(t_LEFT_BRACKET, &token);
                    return token;
                    break;
                }
                else if (current_char == ')')
                {
                    end_token(t_RIGHT_BRACKET, &token);
                    return token;
                    break;
                }
                else if (current_char == '/')
                {
                    state = t_DIVIDE_F;
                }
                else if (current_char == '*')
                {
                    end_token(t_MULTIPLY, &token);
                    return token;
                    break;
                }
                else if (current_char == '+')
                {
                    end_token(t_PLUS, &token);
                    return token;
                    break;
                }
                else if (current_char == '-')
                {
                    end_token(t_MINUS, &token);
                    return token;
                    break;
                }
                else if (current_char == '#')
                {
                    state = ONE_LINE_COMMENT;
                }
                else if (current_char == ':')
                {
                    end_token(t_COLON, &token);
                    return token;
                    break;
                }
                else if (current_char == '"')
                {
                    state = QUOTES1;
                }
                else if (current_char == '0')
                {
                    state = t_INT_ZERO;
                }
                else if ((isdigit(current_char)) && (current_char != '0'))
                {
                    state = t_INT_NON_ZERO;
                }
                else if (current_char == 39)
                {
                    state = STRING_START;
                    current_token_position--;
                    current_token[current_token_position] = 0x00;
                }
                else if ((isalpha(current_char)) || (current_char == '_'))
                {
                    state = t_IDENTIFIER;
                }
                else if (current_char == '\n')
                {
                    end_token(t_EOL, &token);
                    state = IND_DED;
                    First_token = true;
                    return token;
                }
                
                break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            case t_LESS:
                if (current_char == '=')
                {
                    end_token(t_LESSOREQUAL, &token);
                    return token;
                }
                else
                {
                    unload_c(text);
                    end_token(t_LESS, &token);
                    return token;
                }
                break;

            case t_GREATER:
                if (current_char == '=')
                {
                    end_token(t_GREATEROREQUAL, &token);
                    return token;
                }
                else
                {
                    unload_c(text);
                    end_token(t_GREATER, &token);
                    return token;
                }
                break;
            
            case t_ASSIGN:
                if (current_char == '=')
                {
                    end_token(t_EQUAL, &token);
                    return token;
                }
                else
                {
                    unload_c(text);
                    end_token(t_ASSIGN, &token);
                    return token;
                }
                break;
            
            case EXLAMATION:
                if (current_char == '=')
                {
                    end_token(t_NOT_EQUAL, &token);
                    return token;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
            
            //DIVIDE FLOAT AND INTEGER
            case t_DIVIDE_F:
                if (current_char == '/')
                {
                    end_token(t_DIVIDE_I, &token);
                    return token;
                }
                else
                {
                    unload_c(text);
                    end_token(t_DIVIDE_F, &token);
                    return token;
                }
                break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                
            case t_IDENTIFIER:
                if (isalpha(current_char) || isdigit(current_char) || current_char == '_')
                {
                    state = t_IDENTIFIER;
                }
                else
                {
                    unload_c(text);
                    if(!strcmp(current_token, "if")){
                        end_token(t_IF, &token);
                    }
                    else if(!strcmp(current_token, "while")){
                        end_token(t_WHILE, &token);
                    }
                    else if(!strcmp(current_token, "def")){
                        end_token(t_DEF, &token);
                    }
                    else if(!strcmp(current_token, "else")){
                        end_token(t_ELSE, &token);
                    }
                    else if(!strcmp(current_token, "return")){
                        end_token(t_RETURN, &token);
                    }
                    else if(!strcmp(current_token, "None")){
                        end_token(t_NONE, &token);
                    }
                    else if(!strcmp(current_token, "pass")){
                        end_token(t_PASS, &token);
                    }
                    else{
                        end_token(t_IDENTIFIER, &token);
                    }
                    return token;
                }
                break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                
            //FAILED ONE LINE COMMENT #
            case ONE_LINE_COMMENT:
                 if (current_char == '\n')
                 {
                     end_token(t_EOL, &token);
                     state = IND_DED;
                     First_token = true;
                     return token;
                 }
                 else if (current_char == EOF)
                 {
                     unload_c(text);
                     end_token(t_EOL, &token);
                     return token;
                 }
                 else
                 {
                     state = ONE_LINE_COMMENT;
                 }
                 break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                
            // MULTILINE COMMENT WITH "
            case QUOTES1:
                if (current_char == '"')
                {
                    state = QUOTES2;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
            
            case QUOTES2:
                if (current_char == '"')
                {
                    state = COMMENT1;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
                
            case COMMENT1:
                if (current_char == '"')
                {
                    state = COMMENT2;
                }
                else if (current_char == '/')
                {
                    state = ES_COMMENT;
                }
                else if (current_char == EOF)
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                else
                {
                    state = COMMENT1;
                }
                break;
            
            case COMMENT2:
                if (current_char == '"')
                {
                    state = COMMENT3;
                }
                else if (current_char == EOF)
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                else
                {
                    state = COMMENT1;
                }
                break;
            
            case COMMENT3:
                if (current_char == '"')
                {
                    end_token(t_EOL, &token);
                    First_token = true;
                    return token;
                }
                else
                {
                    state = COMMENT1;
                }
                
            case ES_COMMENT:
                state = COMMENT1;
                break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                
            // okrem nuly
            case t_INT_NON_ZERO:
                if (current_char == '.')
                {
                    state = DOT;
                }
                else if ((current_char == 'e') || (current_char == 'E'))
                {
                    state = EXPONENT;
                }
                else if (isdigit(current_char))
                {
                    state = t_INT_NON_ZERO;
                }
                else
                {
                    unload_c(text);
                    end_token(t_INT_NON_ZERO, &token);
                    return token;
                }
                break;
            
            // zacina nulou
            case t_INT_ZERO:
                if ((current_char == 'e') || (current_char == 'E'))
                {
                    state = EXPONENT;
                }
                else if (current_char == '.')
                {
                    state = DOT;
                }
                else
                {
                    unload_c(text);
                    end_token(t_INT_ZERO, &token);
                    return token;
                }
                break;
                
            case DOT:
                if (isdigit(current_char))
                {
                    state = t_FLOAT;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
                
            case t_FLOAT:
                if (current_char == 'e' || current_char == 'E')
                {
                    state = EXPONENT;
                }
                else if (isdigit(current_char))
                {
                    state = t_FLOAT;
                }
                else
                {
                    unload_c(text);
                    end_token(t_FLOAT, &token);
                    return token;
                }
                break;
                
            case EXPONENT:
                
                if (isdigit(current_char))
                {
                    state = EXPONENT2;
                }
                else if (current_char == '+' || current_char == '-'  )
                {
                    state = PLUS_MINUS_EXPONENT;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
                
            case PLUS_MINUS_EXPONENT:
                if(isdigit(current_char))
                {
                    state = EXPONENT2;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
                
            case EXPONENT2:
                if (isdigit(current_char))
                {
                    state = EXPONENT2;
                }
                else
                {
                    unload_c(text);
                    end_token(t_FLOAT, &token);
                    return token;
                }
                break;
                
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                
            case STRING_START:
                if (current_char == 39 )
                {
                    current_token[strlen(current_token)-1] = '\0';
                    end_token(t_STRING, &token);
                    return token;
                }
                else if (current_char == 92)
                {
                    state = ES_STRING;
                }
                else if (current_char == EOF)
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                else if (current_char == 0)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 1)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 2)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 3)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 4)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '4';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 5)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '5';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 6)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '6';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 7)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '7';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 8)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '8';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 9)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '9';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 10)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 11)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 12)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 13)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 14)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '4';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 15)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '5';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 16)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '6';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 17)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '7';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 18)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '8';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 19)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '9';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 20)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 21)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 22)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 23)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 24)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '4';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 25)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '5';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 26)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '6';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 27)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '7';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 28)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '8';
                    current_token_position++;
                    state = STRING_START;
                }else if(current_char == 29)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    current_token[current_token_position] = '9';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 30)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 31)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 32)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;

                    state = STRING_START;
                }
                else if(current_char == 35)
                {
                    current_token[current_token_position-1] = 92;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    current_token[current_token_position] = '5';
                    current_token_position++;


                    state = STRING_START;
                }
                else
                {
                    state = STRING_START;
                }
                break;
                
            case ES_STRING:
                
                
                if(current_char == 34)
                {
                    current_token[current_token_position-1] = '0';
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    current_token[current_token_position] = '4';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 39)
                {
                    current_token[current_token_position-1] = '0';
                    current_token[current_token_position] = '3';
                    current_token_position++;
                    current_token[current_token_position] = '9';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 92)
                {
                    current_token[current_token_position-1] = '0';
                    current_token[current_token_position] = '9';
                    current_token_position++;
                    current_token[current_token_position] = '2';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 'n')
                {
                    current_token[current_token_position-1] = '0';
                    current_token[current_token_position] = '1';
                    current_token_position++;
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    state = STRING_START;
                }
                else if(current_char == 't')
                {
                    current_token[current_token_position-1] = '0';
                    current_token[current_token_position] = '0';
                    current_token_position++;
                    current_token[current_token_position] = '9';
                    current_token_position++;

                    state = STRING_START;
                }
                else if(current_char == 'x')
                {
                    state = STRING_HEXA1;
                }
                else
                {
                    state = STRING_START;
                }
                break;
                
            case STRING_HEXA1:
                if ((current_char >= '0' && current_char <= '9') || (current_char >= 'a' && current_char <= 'f') || (current_char >= 'A' && current_char <= 'F') )
                {
                    state = STRING_HEXA2;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
                
            case STRING_HEXA2:
                if ((current_char >= '0' && current_char <= '9') || (current_char >= 'a' && current_char <= 'f') || (current_char >= 'A' && current_char <= 'F') )
                {
                    state = STRING_START;
                }
                else
                {
                    fprintf(stderr , "Lexical error.\n");
                    exit(1);
                }
                break;
                
            case IND_DED:
//                stackTop(&indent_s, &i);
                
                if(current_char == EOF){
                    end_token(t_EOF, &token);
                    return token;
                }
                if(current_char == ' ')
                {
                    spacecount++;
                }
                else if(current_char == '\n'){
                    end_token(t_EOL, &token);
                    state = IND_DED;
                    return token;
                }
                else
                {
                    unload_c(text);
                    stackTop(&indent_s, &i);
                    if(spacecount == i)
                    {
                        First_token = false;
                        state = START;
                        delete_string();
                        spacecount = 0;
                        
                    }
                    else if(spacecount > i)
                    {
                        stackPush(&indent_s, spacecount);
                        spacecount = 0;
                        end_token(t_INDENT, &token);
                        state = START;
                        First_token = false;
                        return token;
                    }
                    else
                    {
                        //end_token(t_DEDENT, &token);
                        stackPop(&indent_s);
                        stackTop(&indent_s, &i);
                        if(spacecount <= i){
                            end_token(t_DEDENT, &token);
                        }
                        else
                        {
                            fprintf(stderr , "Lexical error.\n");
                            exit(1);
                        }
                        if((!i) && spacecount)
                        {
                            fprintf(stderr , "Lexical error.\n");
                            exit(1);
                        }
                        return token;
                    }
                }
        }
    }
}
