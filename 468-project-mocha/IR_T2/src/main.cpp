#include <iostream>
#include <stdio.h>
#include <string>
#include <stack>
#include <vector>
#include "SymbolTable.h"
#include "../generated/parser.hpp" 
extern int yylex();
extern char * yytext;
extern FILE * yyin;

using namespace std;

int main(int argc, char *argv[]){
	if ( argc > 1 )
        yyin = fopen( argv[1], "r" );
    else
        yyin = stdin;

    int accept = yyparse();
	return 0;
}



