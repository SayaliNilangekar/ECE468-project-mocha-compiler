%{
	#include <stdio.h>
	void yyerror(const char* str){}
	extern int yylex();
%}

/* Bison declarations*/
%token INTLITERAL
%token FLOATLITERAL
%token STRINGLITERAL
%token IDENTIFIER

%token PROGRAM 
%token SEMICOLON
%token _BEGIN
%token END
%token FUNCTION
%token READ
%token WRITE 
%token IF 
%token ELSE 
%token ENDIF 
%token WHILE 
%token ENDWHILE 
%token RETURN 
%token INT 
%token VOID 
%token STRING 
%token FLOAT 
%token TRUE 
%token FALSE 


%token COLONEQUAL 

%token PLUS 
%token MINUS 
%token ASTERISK 
%token FWDSLASH 
%token EQUAL 
%token NOTEQUAL 
%token LESSTHAN 
%token GREATERTHAN 
%token OPENPARAN 
%token CLOSEPARAN 
%token COMMA 
%token LESSTHANEQUAL 
%token GREATERTHANEQUAL 

%%
/* Program */
program           : PROGRAM id _BEGIN pgm_body END; /*Proper rule defn*/
id                : IDENTIFIER;
pgm_body          : decl func_declarations;
decl		  : string_decl decl | var_decl decl |;

/* Global String Declaration */
string_decl       : STRING id COLONEQUAL str SEMICOLON;
str               : STRINGLITERAL;

/* Variable Declaration */
var_decl          : var_type id_list SEMICOLON;
var_type	  : FLOAT | INT;
any_type          : var_type | VOID; 
id_list           : id id_tail;
id_tail           : COMMA id id_tail |;

/* Function Paramater List */
param_decl_list   : param_decl param_decl_tail |;
param_decl        : var_type id;
param_decl_tail   : COMMA param_decl param_decl_tail |;

/* Function Declarations */
func_declarations : func_decl func_declarations |;
func_decl         : FUNCTION any_type id OPENPARAN param_decl_list CLOSEPARAN _BEGIN func_body END;
func_body         : decl stmt_list;

/* Statement List */
stmt_list         : stmt stmt_list |;
stmt              : base_stmt | if_stmt | loop_stmt; 
base_stmt         : assign_stmt | read_stmt | write_stmt | control_stmt;

/* Basic Statements */
assign_stmt       : assign_expr SEMICOLON;
assign_expr       : id COLONEQUAL expr
read_stmt         : READ OPENPARAN id_list CLOSEPARAN SEMICOLON; /*space before "SEMICOLON" ok?*/
write_stmt        : WRITE OPENPARAN id_list CLOSEPARAN SEMICOLON; /*space before "SEMICOLON" ok?*/
return_stmt       : RETURN expr SEMICOLON;

/* Expressions */
expr              : expr_prefix factor;
expr_prefix       : expr_prefix factor addop |;
factor            : factor_prefix postfix_expr;
factor_prefix     : factor_prefix postfix_expr mulop |;
postfix_expr      : primary | call_expr;
call_expr         : id OPENPARAN expr_list CLOSEPARAN;
expr_list         : expr expr_list_tail |;
expr_list_tail    : COMMA expr expr_list_tail |;
primary           : OPENPARAN expr CLOSEPARAN | id | INTLITERAL | FLOATLITERAL;
addop             : PLUS | MINUS;
mulop             : ASTERISK | FWDSLASH;

/* Complex Statements and Condition */ 
if_stmt           : IF OPENPARAN cond CLOSEPARAN decl stmt_list else_part ENDIF;
else_part         : ELSE decl stmt_list |;
cond              : expr compop expr | TRUE | FALSE;
compop            : LESSTHAN | GREATERTHAN | EQUAL | NOTEQUAL | LESSTHANEQUAL | GREATERTHANEQUAL;
while_stmt        : WHILE OPENPARAN cond CLOSEPARAN decl stmt_list ENDWHILE;


/*ECE468 ONLY*/
control_stmt      : return_stmt;
loop_stmt         : while_stmt;



%%
