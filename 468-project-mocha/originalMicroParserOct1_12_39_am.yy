%{
	void yyerror(const char* str){}
	extern int yylex();
	extern char* yytext;
	#include <stdio.h>
	#include <iostream>
	#include <string>
	#include <stack>
	#include <vector>
	#include "Symbol.h"
	#include "SymbolTable.h"
	using namespace std;
	extern SymbolTable* root; //declare in main.cpp & extern it in parser ----- Check declaration in main.cpp ---- ?????????????????
	std::stack<SymbolTable *> stack;
	int blockCounter = 0;
	//void increaseBlockCount(int count);
	//std::vector<SymbolTable *> childrenVector; //vector of all the popped SymbolTables
	extern std::vector<SymbolTable *> childrenVector;	// Is this OK??????????????? Check declaration in main.cpp   ------  ?????????????? (Global children vector storing popped symbol tables in order)
        void addChildSymTable(SymbolTable* child); //adding most recently popped SymbolTable to childrenVector ----------------- Check definition below --------- OK?????????????????
	
%}
%union{
	std::string* s;
	Symbol* Sym;
	vector<string> VectStr
}
/* Bison declarations*/
%start program
%token PROGRAM 
%token INTLITERAL
%token FLOATLITERAL
%token STRINGLITERAL
%token IDENTIFIER


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

%type <s> id IDENTIFIER str STRINGLITERAL var_type
%type <Sym> string_decl var_decl	//??????????
%type <VectStr> id_tail id_list

%%
/* Program */
program           : PROGRAM {cout<<"Program begins"<<endl;} id _BEGIN {SymbolTable* newSymTable = new SymbolTable(); 
								newSymTable->setScope("GLOBAL"); 
								newSymTable->setParent(root); 
								root = newSymTable; 
								stack.push(newSymTable);} 
		    pgm_body END {if (!stack.empty())
				  {
					SymbolTable* poppedTab = stack.pop();
					cout<<"Popped Table Name: "<<poppedTab->getScope()<<endl;
				  } 
				}; /*Proper rule defn*/ //Able to declare, global -------- OK?????????????????? ------------ CHANGE FOR POP

id                : IDENTIFIER {$$ = $1;}; //define types in %union & assign in %type

pgm_body          : decl func_declarations;
decl		  : string_decl decl | var_decl decl |;	//???????????????

/* Global String Declaration */
//string_decl       : STRING id COLONEQUAL str SEMICOLON {$$ = new Symbol($4); $$->var_name.assign(*($2)); };	//ADD to declVector?????????????????
string_decl       : STRING id COLONEQUAL str SEMICOLON { Symboltable* currTop = stack.pop();
							$$ = new Symbol($4); 
							$$->var_name.assign(*($2));
							currTop->addDecl($$);
							stack.push(currTop); };	//ADD to declVector?????????????????
str               : STRINGLITERAL {$$ = $1;}; 

/* Variable Declaration */
//var_decl          : var_type id_list SEMICOLON {if ((*($1)).compare("INT") == 0) { $$ = new Symbol(0); } else if ((*($1)).compare("FLOAT") == 0) { $$ = new Symbol(0.0); }};	//ADD to declVector; HOW TO PASS ID VALUE OR EVEN ASSIGN ID NAME????????????????? ----------- CHECK LOGIC
var_decl          : var_type id_list SEMICOLON {if ((*($1)).compare("INT") == 0) 
						{ 
							Symboltable* currTop = stack.pop();
							sz = ($2).size();
							for(int i=0; i<sz; i++)
							{
								Symbol* newSymEntry = new Symbol(0);
								newSymEntry->var_name.assign($2[i]);
								currTop->addDecl(newSymEntry);
							}
							stack.push(currTop);
						} 
						else if ((*($1)).compare("FLOAT") == 0)
						{ 
							Symboltable* currTop = stack.pop();
							sz = ($2).size();
							for(int i=0; i<sz; i++)
							{
								//Symbol* newSymEntry = new Symbol(0.0);
								Symbol* newSymEntry = new Symbol(1.5); //BAD but whatever.... change latr????
								newSymEntry->var_name.assign($2[i]);
								currTop->addDecl(newSymEntry);
							}
							stack.push(currTop);
 
						}	};	//ADD to declVector; --------- OK??????????
var_type	  : FLOAT {(*($$)).assign("FLOAT")}| INT {(*($$)).assign("INT")};
any_type          : var_type | VOID ;
id_list           : id id_tail {$$ = $2; 
				$$->insert($$->begin(), *($1))} ; //**************
id_tail           : COMMA id id_tail {$$ = $3; 
				      $$->insert($$->begin(), *($2))} | {$$ = new vector<string>;} ; //********************

/* Function Paramater List */  //Able to declare, local function scope
param_decl_list   : param_decl param_decl_tail |; 
param_decl        : var_type id ;	
param_decl_tail   : COMMA param_decl param_decl_tail |; 

/* Function Declarations */  //Able to declare, local scope
func_declarations : func_decl func_declarations |;	
func_decl         : FUNCTION any_type id OPENPARAN param_decl_list CLOSEPARAN _BEGIN {SymbolTable* newSymTable = new SymbolTable(); 
										      newSymTable->setScope(*($3));
										      SymbolTable* currTop = stack.top();
										      newSymTable->setParent(currTop); 
	 									      currTop->addChildSymTable(newSymTable); 
										      currTop = newSymTable;
										      stack.push(newSymTable);}
		    func_body END {if (!stack.empty()) {
 					SymbolTable* poppedTab = stack.pop();
					cout<<"Popped Table Name: "<<poppedTab->getScope()<<endl;	}  } ;	//OK??????????? ---------------- CHANGE FOR POP
func_body         : decl stmt_list;	

/* Statement List */
stmt_list         : stmt stmt_list |;	
stmt              : base_stmt | if_stmt | loop_stmt; 
base_stmt         : assign_stmt | read_stmt | write_stmt | control_stmt;

/* Basic Statements */
assign_stmt       : assign_expr SEMICOLON;
assign_expr       : id COLONEQUAL expr
read_stmt         : READ OPENPARAN id_list CLOSEPARAN SEMICOLON; 
write_stmt        : WRITE OPENPARAN id_list CLOSEPARAN SEMICOLON; 
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
if_stmt           : IF OPENPARAN cond CLOSEPARAN {SymbolTable* newSymTable = new SymbolTable();
						 blockCounter++; 
						 string blockname = ("BLOCK "+to_string(blockCounter));
						 newSymTable->setScope(blockname); 
						 SymbolTable* currTop = stack.top();
						 newSymTable->setParent(currTop);
						 currTop->addChildSymTable(newSymTable);
						 currTop = newSymTable;
						 stack.push(newSymTable);} 
		    decl stmt_list else_part ENDIF {if (!stack.empty()) {
 							SymbolTable* poppedTab = stack.pop();
							cout<<"Popped Table Name: "<<poppedTab->getScope()<<endl;	}  } ; // ----------- CHANGE POP

else_part         : ELSE decl stmt_list {SymbolTable* newSymTable = new SymbolTable();
					 blockCounter++;
					 string blockname = ("BLOCK "+to_string(blockCounter));
					 newSymTable->setScope(blockname);
					 SymbolTable* currTop = stack.top();
					 newSymTable->setParent(currTop);
					 currTop->addChildSymTable(newSymTable);
					 currTop = newSymTable;
					 stack.push(newSymTable);} |; 

cond              : expr compop expr | TRUE | FALSE;

compop            : LESSTHAN | GREATERTHAN | EQUAL | NOTEQUAL | LESSTHANEQUAL | GREATERTHANEQUAL;

while_stmt        : WHILE OPENPARAN cond CLOSEPARAN {SymbolTable* newSymTable = new SymbolTable();
						     blockCounter++;
						     string blockname = ("BLOCK "+to_string(blockCounter));
						     newSymTable->setScope(blockname);
						     SymbolTable* currTop = stack.top();
						     newSymTable->setParent(currTop);
						     currTop->addChildSymTable(newSymTable);
						     currTop = newSymTable;
						     stack.push(newSymTable);}
		    decl stmt_list ENDWHILE {if (!stack.empty()) {
						 SymbolTable* poppedTab = stack.pop();
						 cout<<"Popped Table Name: "<<poppedTab->getScope()<<endl;	}} ; //--------- CHANGE POP


/*ECE468 ONLY*/
control_stmt      : return_stmt;
loop_stmt         : while_stmt;

%%



