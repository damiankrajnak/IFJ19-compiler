#include "main.h"
#include "parser.h"
#include "symtable.h"

int main() {

    //printf("main");
    parser();
    second_pass();
    print_output();
    return 0;
}
