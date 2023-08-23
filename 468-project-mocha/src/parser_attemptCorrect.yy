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
  std::vector<CodeObject*> coVect;
  

  std::string genScope(){
    return "BLOCK " + std::to_string((long long)++blockCounter);
  }


  void printInOrder(ASTNode* node){
		if(node == NULL)
			return;
		printInOrder(node->leftChild);
		//std::cout<<"Node token is: "<<node->token<<"        Token type is: "<<node->tokType<<std::endl;
		printInOrder(node->rightChild);
	}

 

  void yyerror(const char* str){}
  extern int yylex();
  extern char* yytext;
  SymbolTable* root; 
  VectorTable* vectRoot;
  ASTNode* ifRoot = NULL;
  std::stack<SymbolTable *> symtabStack;
  std::stack<VectorTable *> vectTabStack;
  std::stack<ASTNode*> ifStack;
  std::vector<ASTNode*> FuncVect;
%}

%union{
  int tok;
  std::string* sstr;
  std::list<std::string>* slist;
  ASTNode* ASTPtr;
  Arithmetic* ArithPtr;
  std::vector<ASTNode*>* ASTPtrVectPtr;
 
}

/* Bison declarations*/
%token INTLITERAL FLOATLITERAL STRINGLITERAL IDENTIFIER PROGRAM SEMICOLON _BEGIN END FUNCTION READ WRITE IF 
%token ELSE ENDIF WHILE ENDWHILE RETURN INT VOID STRING FLOAT TRUE FALSE COLONEQUAL PLUS MINUS ASTERISK 
%token FWDSLASH EQUAL NOTEQUAL LESSTHAN GREATERTHAN OPENPARAN CLOSEPARAN COMMA LESSTHANEQUAL GREATERTHANEQUAL 

%type <sstr> id str compop
%type <slist> id_list id_tail
%type <tok> any_type var_type
%type <ArithPtr> mulop addop
%type <ASTPtr> primary call_expr expr postfix_expr factor_prefix factor expr_prefix cond assign_expr assign_stmt control_stmt return_stmt base_stmt if_stmt stmt else_part 
%type <ASTPtr> read_stmt
%type <ASTPtrVectPtr> stmt_list

%%
/* Program */
program           : PROGRAM id _BEGIN 
                  {
                    //Symbol Table
		    root = new SymbolTable("GLOBAL", NULL); 
                    symtabStack.push(root);
		    
		    //Vector Table
		    vectRoot = new VectorTable("GLOBAL", NULL);
		    vectTabStack.push(vectRoot);
			 
                  } 
                  pgm_body END 
                  {
                    //root->PrintSymbolTables();
		    //vectRoot->printStack();
		    std::vector<CodeObject*> vect = vectRoot->StackIteratorforIR(coVect);
		    /*
		    std::cout<<"printing vector now"<<std::endl;
		    std::cout<<vect.size()<<std::endl;
		    int len = vect.size();
		    for (int i = 0; i < len; i++){
			std::cout<<vect[i]->result<<std::endl;
		    }
		    std::cout<<"vector printed "<<std::endl;*/
		    root->printVarDecl();
		    vectRoot->IRtoAssembly(vect);

                    delete($2);
                  }; /*Proper rule defn*/

id                : IDENTIFIER {$$ = new std::string(yytext);};

pgm_body          : decl func_declarations;

decl              : string_decl decl | var_decl decl |;

/* Global String Declaration */
string_decl       : STRING id COLONEQUAL str SEMICOLON 
                  { 
		    //std::cout<<"I am debugging"<<std::endl;
                    Symbol * tmp = new Symbol(STRING, *$2, *$4);
		    //std::cout<<"I am debugging2"<<std::endl;
                    symtabStack.top()->addDecl(tmp);
		    //std::cout<<"I am debugging"<<std::endl;

		    AssignNode* asnTempo = new AssignNode(*$2, *$4); 
		    ASTNode* AsnAST = dynamic_cast<ASTNode*>(asnTempo); 

		    //VectorTable* currVectTabTop = vectTabStack.top();
		    //(currVectTabTop->stmtVect).push_back(AsnAST);	

                    delete($2);
                    delete($4);

                  };

str               : STRINGLITERAL 
                  {
                    $$ = new std::string(yytext);

                  };

/* Variable Declaration */
var_decl          : var_type id_list SEMICOLON
                  {
		    
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
		    //Symbol Table
                    SymbolTable *func = new SymbolTable(*$3, symtabStack.top());
                    symtabStack.top()->children.push_back(func);
                    symtabStack.push(func);

		    //Vector Table
		    VectorTable *vectFunc = new VectorTable(*$3, vectTabStack.top());
		    vectTabStack.top()->vectChildren.push_back(vectFunc);
		    vectTabStack.push(vectFunc);
                  } 
                  param_decl_list CLOSEPARAN _BEGIN func_body END
                  {
                    symtabStack.pop(); //Symbol Table		    
		    vectTabStack.pop(); //Vector Table
                  };

func_body         : decl stmt_list {
			for(int i = 0; i < $2->size(); i++)			
			{
				if((*$2)[i] != NULL)
				{	
					if((*$2)[i]->assignRHS != NULL)			
					{std::cout<<"Stmt List stmt is: "<<(*$2)[i]->assignRHS->token<<std::endl;}
					else
					{std::cout<<"Stmt List stmt If Else Type: "<<(*$2)[i]->If_ElseType<<std::endl;}
				}
				else
					std::cout<<"Stmt List stmt is: NULL"<<std::endl;
			}
		};

/* Statement List */
/*stmt_list         : stmt stmt_list  
		  | ; */

stmt_list         : stmt stmt_list {$$ = $2; $$->insert($$->begin(), $1); } 
		  | {$$ = new std::vector<ASTNode*>;}; 

stmt              : base_stmt {$$ = $1; std::cout<<"Base is called!"<<std::endl;}
	          | if_stmt {$$ = $1; 
			    std::cout<<"If_stmt is called!"<<std::endl;
			    if($$ != NULL)
			    {
			    	std::cout<<"If Else Type: "<<$$->If_ElseType<<std::endl;
				for(int i=0; i < $$->IfElseStmtVect.size(); i++)
				{
					if($$->IfElseStmtVect[i] != NULL)				
						std::cout<<"If List stmt is: "<<$$->IfElseStmtVect[i]->assignRHS->token<<std::endl;
				}
				if($$->elsePart != NULL)
				{
					std::cout<<"If Else Type: "<<$$->elsePart->If_ElseType<<std::endl;
					for(int i=0; i < $$->elsePart->IfElseStmtVect.size(); i++)
					{
						if($$->IfElseStmtVect[i] != NULL)				
							std::cout<<"Else List stmt is: "<<$$->elsePart->IfElseStmtVect[i]->assignRHS->token<<std::endl;
					}
				}
			    }
			}
                  | loop_stmt {$$ = NULL;};

 
base_stmt         : assign_stmt {$$ = $1;}
		  | read_stmt {$$ = $1;}
		  | write_stmt {$$ = NULL;}
		  | control_stmt {$$ = $1;}; 

/* Basic Statements */
assign_stmt       : assign_expr SEMICOLON {$$ = $1;};

assign_expr       : id COLONEQUAL expr {
					//printInOrder($3); 
					AssignNode* asnTempo = new AssignNode(*$1, $3); 
					ASTNode* AsnAST = dynamic_cast<ASTNode*>(asnTempo); 

					VectorTable* currVectTabTop = vectTabStack.top();
					(currVectTabTop->stmtVect).push_back(AsnAST);

					//Assigning type to assign_expr
					$$ = AsnAST; 
					//$$ = NULL;										
					};

//READ IO STMT
read_stmt         : READ OPENPARAN id_list {$$ = new ASTNode();} CLOSEPARAN SEMICOLON; 


//WRITE IO STMT
write_stmt        : WRITE OPENPARAN id_list { 
			//debugging
			//for(std::list<std::string>::iterator it=(*$3).begin();it!=(*$3).end();++it) 
			//ASTNode *ASTtempo = new ASTNode();
			//ASTtempo = NULL;
			//$$ = ASTtempo;
			for(std::list<std::string>::iterator it=(*$3).begin();it!=(*$3).end();++it) 
			{
			   //"newline" case
			   if(*it == "newline"){
				IONode *tempo = new IONode (NULL, "WRITE"); //IONode creation
		                ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
				//ASTtempo = dynamic_cast<ASTNode*>(tempo);

				//After ASTNode creation
				//std::cout<<"AFTER IONode CREATION AND CAST --- WRITE: tokType type of "<<ASTtempo->token<<" is "<<ASTtempo->tokType<<std::endl; //Remove

				VectorTable* currVectTabTop = vectTabStack.top();
				(currVectTabTop->stmtVect).push_back(ASTtempo);
				
				} //end of if - newline
			   
			  //Symbols
			  else{
			      //if stmt to check for newline
			      SymbolTable* currentTab;
		              currentTab = symtabStack.top();
		              while(currentTab != NULL){

		                if(currentTab->table.find(*it) == currentTab->table.end()){
		                  if(currentTab->scope == "GLOBAL"){
		                    std::cout<<"EXPRESSION ERROR"<<"\n"; //needs help
		              exit(1);
		                  }

		                } //end of if
		                else{
		                  //std::cout<<currentTab->scope<<std::endl;
		                  for (int i = 0; i< currentTab->ordered_table.size(); i++){
		                    if (currentTab->ordered_table[i]->var_name == *it){
				      //std::cout<<"Var type of "<<currentTab->ordered_table[i]->var_name<<" is "<<currentTab->ordered_table[i]->var_type<<std::endl; //Remove
		                      IONode *tempo = new IONode (currentTab->ordered_table[i], "WRITE"); //IONode creation
		                      ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
				      //ASTtempo = dynamic_cast<ASTNode*>(tempo);
				      //$$ = dynamic_cast<ASTNode*>(tempo);
				      //After ASTNode creation
				      //std::cout<<"AFTER IONode CREATION AND CAST: tokType type of "<<ASTtempo->token<<" is "<<ASTtempo->tokType<<std::endl; //Remove

				      VectorTable* currVectTabTop = vectTabStack.top();
				      (currVectTabTop->stmtVect).push_back(ASTtempo);
				      
					//Assigning type to write_stmt
					//$$ = ASTtempo; //NEED HELP --- STEP5
					//$$ = NULL;
				     
		                    }
		                  }
		                  break;                          
		                } //end of else
		                currentTab = currentTab->parent;
		              } //end of while
			} //end of else - newline
		     }//end of for
			//$$ = ASTtempo;
		   } CLOSEPARAN SEMICOLON; //end of write_stmt 

		  //Debiggung after all write statements the vector ( OR statement for READ and WRITE not working)
		/*{			
					VectorTable* currVectTabTop = vectTabStack.top();
					for(int i=0; i < (currVectTabTop->stmtVect).size(); i++) 

					{
						if ((currVectTabTop->stmtVect)[i]->IOType == "WRITE")
							std::cout<<"Current Vector Table top element (is IO)"<<i<<" is ---  "<<(currVectTabTop->stmtVect)[i]->token<<std::endl;
						else if ((currVectTabTop->stmtVect)[i]->IOType == "READ")
							std::cout<<"Current Vector Table top element (is IO)"<<i<<" is ---  "<<(currVectTabTop->stmtVect)[i]->token<<std::endl;
						else
							std::cout<<"Current Vector Table top element (NO IO)"<<i<<" is ---  "<<(currVectTabTop->stmtVect)[i]->assignRHS->token<<std::endl;					
					}
		};  */
		
		


return_stmt       : RETURN expr SEMICOLON {$$ = $2;};

/* Expressions */
expr              : expr_prefix factor
		{
			$$ = $1;
			if($1 == NULL)
			{
				$$ = $2;
			
			}
			else
			{
				//$$->leftChild = $1;
				$$->rightChild = $2;
			}
		};
expr_prefix       : expr_prefix factor addop 
		    {
			$$ = $3;
			if($1 == NULL)
			{
				$3->leftChild = $2;
				$3->rightChild = NULL;
			
			}
			else
			{
				$3->leftChild = $1;
				$3->leftChild->rightChild = $2;
				$3->rightChild = NULL;
			}
			
		     } 
		    
		    | { $$ = NULL; };

factor            : factor_prefix postfix_expr     
		{
			$$ = $1;
			if($1 == NULL)
			{
				$$ = $2;
			
			}
			else
			{
				//$$->leftChild = $1;
				$$->rightChild = $2;
			}
		};
factor_prefix     : factor_prefix postfix_expr mulop
		     {
			$$ = dynamic_cast<ASTNode*>$3;
			if($1 == NULL)
			{
				$$->leftChild = $2;
				$$->rightChild = NULL;
			
			}
			else
			{
				$$->leftChild = $1;
				$$->leftChild->rightChild = $2;
				$$->rightChild = NULL;
			}
			
		     } 
		    | { $$ = NULL; };

postfix_expr      : primary {$$ = $1;} | call_expr {$$ = $1;} ;

call_expr         : id OPENPARAN expr_list CLOSEPARAN; 
expr_list         : expr expr_list_tail |; 
expr_list_tail    : COMMA expr expr_list_tail |; 

primary           : OPENPARAN expr CLOSEPARAN {$$ = $2;}
		  | id  {
			
                      SymbolTable* currentTab;
                      currentTab = symtabStack.top();
                      while(currentTab != NULL){
                        if(currentTab->table.find(*$1) == currentTab->table.end()){
                          if(currentTab->scope == "GLOBAL"){
                            std::cout<<"EXPRESSION ERROR"<<"\n"; //needs help
                      exit(1);
                          }

                        }
                        else{
                          //std::cout<<currentTab->scope<<std::endl;
                          for (int i = 0; i< currentTab->ordered_table.size(); i++){
                            if (currentTab->ordered_table[i]->var_name == *$1){

                              VarRef *tempo = new VarRef (currentTab->ordered_table[i]);
                              ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
                              $$ = ASTtempo;

                            }
                          }
                          break;                          
                        }
                        currentTab = currentTab->parent;
                      }
                    } //end of 'id' code
			
		  | INTLITERAL {
			LitNode *tempo = new LitNode(std::string(yytext), 5);
			ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);			
			$$ = ASTtempo;
			
			}
		  | FLOATLITERAL {
			LitNode *tempo = new LitNode(std::string(yytext), 6);
			ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);			
			$$ = ASTtempo;
			
			} ;

addop             : PLUS {Arithmetic* op = new Arithmetic("+"); $$ = op; }
		    | MINUS {Arithmetic* op = new Arithmetic("-"); $$ = op; };
mulop             : ASTERISK {Arithmetic* op = new Arithmetic("*"); $$ = op; }
		   | FWDSLASH {Arithmetic* op = new Arithmetic("/"); $$ = op; };

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
			if($9 == NULL)
			{
				//If_ElseNode
		    		If_ElseNode* ifNode = new If_ElseNode();
		    		ifNode->condExpr = $3;
		    		ifNode->If_ElseType = "IF";
				ifNode->elsePart = NULL;
				//ifNode->IfElseStmtVect = (*$7);
				for(int i=0; i < $7->size(); i++)
				{
					ifNode->IfElseStmtVect.push_back((*$7)[i]);
				}
				
				if(ifRoot == NULL)
				{
					ifNode->IfParent = NULL;
					ifRoot = ifNode;
					ifStack.push(ifNode);
				}
				else
				{
					ifNode->IfParent = ifStack.top();
					//ifStack.top()->IfElseChildren.push_back(ifNode);
					//ifStack.push(ifNode);
					if(ifNode->IfParent->elsePart != NULL)
					{
						ifNode->IfParent->elsePart->IfElseChildren.push_back(ifNode);
						std::cout<<"In ElsePart Children: "<<ifNode->If_ElseType<<std::endl;
						ifStack.push(ifNode);
					}
					else
					{
						ifStack.top()->IfElseChildren.push_back(ifNode);
						std::cout<<"In IfPart Children: "<<ifNode->If_ElseType<<std::endl;
						ifStack.push(ifNode);
					}
				}
				$$ = dynamic_cast<ASTNode*>(ifNode);
			}
			else{
				//If_ElseNode
		   		If_ElseNode* ifNode = new If_ElseNode();
		    		ifNode->condExpr = $3;
		    		ifNode->If_ElseType = "IF";
				ifNode->elsePart = $9;
				//ifNode->IfElseStmtVect = (*$7);
				for(int i=0; i < $7->size(); i++)
				{
					ifNode->IfElseStmtVect.push_back((*$7)[i]);
				}
				
				if(ifRoot == NULL)
				{
					ifNode->IfParent = ifRoot;
					ifStack.push(ifNode);
				}
				else
				{
					ifNode->IfParent = ifStack.top();
					if(ifNode->IfParent->elsePart != NULL)
					{
						ifNode->IfParent->elsePart->IfElseChildren.push_back(ifNode);
						std::cout<<"In ElsePart Children: "<<ifNode->If_ElseType<<std::endl;
						ifStack.push(ifNode);
					}
					else
					{
						ifStack.top()->IfElseChildren.push_back(ifNode);
						std::cout<<"In IfPart Children: "<<ifNode->If_ElseType<<std::endl;
						ifStack.push(ifNode);
					}
				}
				$$ = dynamic_cast<ASTNode*>(ifNode);
			}                    
			
			symtabStack.pop();
                  };
else_part         : ELSE decl stmt_list
		    {
			If_ElseNode* elseNode = new If_ElseNode();
			elseNode->If_ElseType = "ELSE";
			//elseNode->IfElseStmtVect = (*$3);
			for(int i=0; i < $3->size(); i++)
			{
				elseNode->IfElseStmtVect.push_back((*$3)[i]);
				//if((*$3)[i]->If_ElseType == "IF")
				//{}
			}
			$$ = dynamic_cast<ASTNode*>(elseNode);
			
		    }	 
		    | {$$ = NULL;};

cond              : expr compop expr 
			{
				CondNode* condObj = new CondNode($1, *$2, "\0", $3);
				$$ = dynamic_cast<ASTNode*>(condObj); 
			}
		  | TRUE
			{
				CondNode* condObj = new CondNode(NULL, "\0", "TRUE", NULL);
				$$ = dynamic_cast<ASTNode*>(condObj); 
			}
 
		  | FALSE
		  	{
				CondNode* condObj = new CondNode(NULL, "\0", "FALSE", NULL);
				$$ = dynamic_cast<ASTNode*>(condObj); 
			};

compop            : LESSTHAN {$$ = new std::string(yytext);}
		  | GREATERTHAN {$$ = new std::string(yytext);}
		  | EQUAL {$$ = new std::string(yytext);}
		  | NOTEQUAL {$$ = new std::string(yytext);}
		  | LESSTHANEQUAL {$$ = new std::string(yytext);}
		  | GREATERTHANEQUAL  {$$ = new std::string(yytext);} ;


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
control_stmt      : return_stmt {$$ = $1;} ;
loop_stmt         : while_stmt  ;



%%
