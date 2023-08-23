%code requires{
  #include <stdio.h>
  #include <iostream>
  #include <stack>
  #include <string>
  #include <vector>
  #include <map>
  #include <list>
  #include <typeinfo>
  #include "../src/SymbolTable.h"
}
%{
  #include <stdio.h>
  #include <iostream>
  #include <stack>
  #include <string>
  #include <vector>
  #include <map>
  #include <list>
  #include "../src/SymbolTable.h"
  int blockCounter = 0;
  //int it = 0;
  std::string genScope(){
    return "BLOCK " + std::to_string((long long)++blockCounter);
  }
  void yyerror(const char* str){}
  extern int yylex();
  extern char* yytext;
  SymbolTable* root; 
  std::stack<SymbolTable *> symtabStack;
%}

%union{
  int tok;
  std::string* sstr;
  std::list<std::string>* slist;
}

/* Bison declarations*/
%token INTLITERAL FLOATLITERAL STRINGLITERAL IDENTIFIER PROGRAM SEMICOLON _BEGIN END FUNCTION READ WRITE IF 
%token ELSE ENDIF WHILE ENDWHILE RETURN INT VOID STRING FLOAT TRUE FALSE COLONEQUAL PLUS MINUS ASTERISK 
%token FWDSLASH EQUAL NOTEQUAL LESSTHAN GREATERTHAN OPENPARAN CLOSEPARAN COMMA LESSTHANEQUAL GREATERTHANEQUAL 

%type <sstr> id str 
%type <slist> id_list id_tail
%type <tok> any_type var_type
%%
/* Program */
program           : PROGRAM id _BEGIN 
                  {
                    root = new SymbolTable("GLOBAL", NULL); 
                    symtabStack.push(root); 
                  } 
                  pgm_body END 
                  {
                    root->PrintSymbolTables();
                    delete($2);
                  }; /*Proper rule defn*/

id                : IDENTIFIER {$$ = new std::string(yytext);};

pgm_body          : decl func_declarations;

decl              : string_decl decl | var_decl decl |;

/* Global String Declaration */
string_decl       : STRING id COLONEQUAL str SEMICOLON 
                  { 
                    Symbol * tmp = new Symbol(STRING, *$2, *$4);
                    symtabStack.top()->addDecl(tmp);
                    delete($2);
                    delete($4);
                    // SymbolTable* currTop = symtabStack.top(); 
                    // cout<<"Top name: "<<currTop->getScope()<<endl; 
                    // symtabStack.pop(); cout<<"Pop success!"<<endl; 
                    // Symbol* strSym = new Symbol(); 
                    // cout<<"Symbol create success!"<<endl; 
                    // (strSym->var_type).assign("STRING"); 
                    // cout<<"Assign success!"<<endl; 
                    // cout<<($4)<<endl; 
                    // (strSym->str_var_value) = ($4); 
                    // cout<<"Value Assign success!"<<endl; 
                    // (strSym->var_name) = ($2); 
                    // cout<<"Name Assign success!"<<endl; 
                    // currTop->addDecl(strSym); 
                    // cout<<"Added Decl!"<<endl; 
                    // symtabStack.push(currTop); 
                    // cout<<"Pushed updated SymbolTable."<<endl;
                  };

str               : STRINGLITERAL 
                  {
                    $$ = new std::string(yytext);
                    // cout<<"Strlit  to be assigned."<<endl; 
                    // $$ = $1; 
                    // cout<<"Strlit Assignment success!"<<endl;
                  };

/* Variable Declaration */
var_decl          : var_type id_list SEMICOLON
                  {
		    //std::cout<<typeid(*$2).name()<<std::endl;
                    //for(auto& id : *$2){  //CHRIS
		    //std::list<std::string>*::const_iterator i;
                    //for (i = ((*$2).begin()); i != ((*$2).end()); ++i){
		    for(std::list<std::string>::iterator it=(*$2).begin();it!=(*$2).end();++it){  
		      //Symbol* tmp = new Symbol($1, id);  //CHRIS
		      Symbol* tmp = new Symbol($1, *it);
                      symtabStack.top()->addDecl(tmp);
                    }
                    delete($2);//delete list now we don't need it
                  };

var_type          : FLOAT {$$ = FLOAT;} | INT{$$ = INT;};

any_type          : var_type {$$ = $1;}
                  | VOID {$$= VOID;}; 

id_list           : id id_tail {$$ = $2; $$->push_front(*$1); delete($1);} ;

id_tail           : COMMA id id_tail {$$ = $3; $$->push_front(*$2); delete($2);}
                  | {$$ = new std::list<std::string>;};

/* Function Paramater List */
param_decl_list   : param_decl param_decl_tail |;

param_decl        : var_type id 
                  {
                    Symbol *tmp = new Symbol($1, *$2);
                    symtabStack.top()->addDecl(tmp);
                  };

param_decl_tail   : COMMA param_decl param_decl_tail |;

/* Function Declarations */
func_declarations : func_decl func_declarations |;

func_decl         : FUNCTION any_type id OPENPARAN 
                  {
                    SymbolTable *func = new SymbolTable(*$3, symtabStack.top());
                    symtabStack.top()->children.push_back(func);
                    symtabStack.push(func);
                  } 
                  param_decl_list CLOSEPARAN _BEGIN func_body END
                  {
                    symtabStack.pop();
                  };

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
if_stmt           : IF OPENPARAN cond CLOSEPARAN 
                  {
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Create */
                  } decl stmt_list 
                  {
                    symtabStack.pop();//pop off the if block
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Pop, Create */
                  } else_part ENDIF
                  {
                    symtabStack.pop();
                  };
else_part         : ELSE decl stmt_list |;
cond              : expr compop expr | TRUE | FALSE;
compop            : LESSTHAN | GREATERTHAN | EQUAL | NOTEQUAL | LESSTHANEQUAL | GREATERTHANEQUAL;
while_stmt        : WHILE OPENPARAN cond CLOSEPARAN 
                  {
                    symtabStack.pop();//pop off the if block
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Pop, Create */
                  }
                  decl stmt_list ENDWHILE
                  {
                    symtabStack.pop();
                  };


/*ECE468 ONLY*/
control_stmt      : return_stmt;
loop_stmt         : while_stmt;



%%

