%{
#include <stdio.h>
%}

NUM [0-9][^\"]
ALPHA [a-zA-Z][^\"]
SPL [^a-zA-Z0-9][^\"]

STRING \"(\\.|[^"\\])*\"


DIGIT [0-9]+
FLOATLITERAL [0-9]+\.[0-9]*|\.[0-9]+
COMMENT \-{2}[^\n]+\n
KEYWORD ("PROGRAM"|"BEGIN"|"END"|"FUNCTION"|"READ"|"WRITE"|"IF"|"ELSE"|"ENDIF"|"WHILE"|"ENDWHILE"|"RETURN"|"INT"|"VOID"|"STRING"|"FLOAT"|"TRUE"|"FALSE")
OPERATOR (":="|"+"|"-"|"*"|"/"|"="|"!="|"<"|">"|"("|")"|";"|","|"<="|">=")
IDENTIFIER [a-zA-Z]{1}[a-zA-Z0-9]*


/*** Rules ***/

%%


{DIGIT}	{ printf("Token Type: INTLITERAL \nValue: %s\n",yytext);}

{STRING} { printf("Token Type: STRINGLITERAL \nValue: %s\n",yytext);}

{FLOATLITERAL}	{ printf("Token Type: FLOATLITERAL \nValue: %s\n",yytext);}

[ \t\n\r]	;

[\"{1}] ;

{COMMENT} ;

{KEYWORD} { printf("Token Type: KEYWORD \nValue: %s\n",yytext);}

{OPERATOR} { printf("Token Type: OPERATOR \nValue: %s\n",yytext);}

{IDENTIFIER} { printf("Token Type: IDENTIFIER \nValue: %s\n",yytext);}

%%
/*
main(argc,argv)
int argc;
char** argv;
{
	//++argv, --argc;
	if(argc > 0)
		yyin = fopen(argv[1], "r");
	else
		yyin = stdin;
	yylex();


}*/

int main(int argc, char *argv[]){
	if(argc > 0)
		yyin = fopen(argv[1], "r");
	yylex();
	return 0;
}
