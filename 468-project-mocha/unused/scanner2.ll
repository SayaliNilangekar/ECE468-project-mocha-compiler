%{
#include "microParser.tab.h"
%}
INTLITERAL 			[0-9]+
FLOATLITERAL 		[0-9]+\.[0-9]*|\.[0-9]+
STRINGLITERAL 		\"(\\.|[^"\\])*\"
COMMENT 			\-{2}[^\n]+\n
PROGRAM 			PROGRAM
_BEGIN 				BEGIN
END 				END
FUNCTION 			FUNCTION
READ 				READ
WRITE 				WRITE
IF 					IF
ELSE 				ELSE
ENDIF 				ENDIF
WHILE 				WHILE
ENDWHILE 			ENDWHILE
RETURN 				RETURN
INT 				INT
VOID 				VOID
STRING 				STRING
FLOAT 				FLOAT
TRUE 				TRUE
FALSE 				FALSE
IDENTIFIER 			[a-zA-Z]{1}[a-zA-Z0-9]*
COLONEQUAL 			":="
SEMICOLON 			";"
PLUS 				"+"
MINUS 				"-"
ASTERISK 			"*"
FWDSLASH 			"/"
EQUAL 				"="
NOTEQUAL 			"!="
LESSTHAN 			"<"
GREATERTHAN 		">"
OPENPARAN 			"("
CLOSEPARAN 			")"
COMMA 				","
LESSTHANEQUAL 		"<="
GREATERTHANEQUAL 	">="
%%
{INTLITERAL}		{ return INTLITERAL;}
{FLOATLITERAL}		{ return FLOATLITERAL;}
{STRINGLITERAL} 	{ return STRINGLITERAL;}
{COMMENT} 			;
{PROGRAM} 			{ return PROGRAM; }
{_BEGIN} 			{ return _BEGIN; }
{END} 				{ return END; }
{FUNCTION} 			{ return FUNCTION; }
{READ} 				{ return READ; }
{WRITE} 			{ return WRITE; }
{IF} 				{ return IF; }
{ELSE} 				{ return ELSE; }
{ENDIF} 			{ return ENDIF; }
{WHILE} 			{ return WHILE; }
{ENDWHILE} 			{ return ENDWHILE; }
{RETURN} 			{ return RETURN; }
{INT} 				{ return INT; }
{VOID} 				{ return VOID; }
{STRING} 			{ return STRING; }
{FLOAT} 			{ return FLOAT; }
{TRUE} 				{ return TRUE; }
{FALSE} 			{ return FALSE; }
{IDENTIFIER} 		{ return IDENTIFIER;}
{COLONEQUAL} 		{ return COLONEQUAL; }
{SEMICOLON} 		{ return SEMICOLON; }
{PLUS} 				{ return PLUS; }
{MINUS} 			{ return MINUS; }
{ASTERISK} 			{ return ASTERISK; }
{FWDSLASH} 			{ return FWDSLASH; }
{EQUAL} 			{ return EQUAL; }
{NOTEQUAL} 			{ return NOTEQUAL; }
{LESSTHAN} 			{ return LESSTHAN; }
{GREATERTHAN} 		{ return GREATERTHAN; }
{OPENPARAN} 		{ return OPENPARAN; }
{CLOSEPARAN} 		{ return CLOSEPARAN; }
{COMMA} 			{ return COMMA; }
{LESSTHANEQUAL} 	{ return LESSTHANEQUAL; }
{GREATERTHANEQUAL} 	{ return GREATERTHANEQUAL; }
[ \t\n\r]			;
. 					;
%%
int yywrap(void) { return 1;}
