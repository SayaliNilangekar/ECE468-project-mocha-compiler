%code requires{
  #include <stdio.h>
  #include <iostream>
  #include <stack>
  #include <string>
  #include <sstream>
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
  #include <set>
  #include "../src/SymbolTable.h"

  int blockCounter = 0;
  int elseCounter = 0;
  int ifCounter = 0;
  int printVDnum = 0;
  bool isLivenessChanged = false;
  
  std::vector<CFGEntry*> CFGStmtVect;
  std::vector<std::string> finalIRvector;
  std::vector<std::string> tempIRvector;
  extern std::vector<std::string> IRcodeVector;
  //Offset Counter
  int offset = 0;
  //int it = 0;
  std::vector<CodeObject*> coVect;

  void yyerror(const char* str){}
  extern int yylex();
  extern char* yytext;
  SymbolTable* root; 
  VectorTable* vectRoot;
  
  std::stack<SymbolTable *> symtabStack;
  std::stack<VectorTable *> vectTabStack;
  std::stack<ASTNode*> ifStack;
  std::vector<ASTNode*> FuncVect;
  

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



std::vector<std::string> returnSplitVect(std::string strToSplit)
{	
	std::string delimiter = " ";
	std::string token;
	std::vector<std::string> indivStrVect;
	
    	size_t prev = 0, pos = 0;
	do{
        	pos = strToSplit.find(delimiter, prev);
        	if (pos == std::string::npos) pos = strToSplit.length();
        		token = strToSplit.substr(prev, pos-prev);
        	if (!token.empty()) indivStrVect.push_back(token);
       	 		prev = pos + delimiter.length();
    	}while (pos < strToSplit.length() && prev < strToSplit.length());

	return indivStrVect;
}

//For CFG
std::vector<CFGEntry*> assignCFGID(std::vector<std::string> finalIRVect){
	//std::vector<CFGEntry> CFGStmtVect;	
	for (int i = 0; i < finalIRVect.size(); i++){
		CFGEntry* currCFG = new CFGEntry(finalIRVect[i]);
		currCFG->StmtID = i;
		CFGStmtVect.push_back(currCFG);
		currCFG->next.push_back(i+1);
		
	}
	return CFGStmtVect;
	

}

std::vector<CFGEntry*> buildCFG(std::vector<CFGEntry*> CFGStmtVect){
	//Assigning JumpLabels
	for(int i=0; i<CFGStmtVect.size(); i++){
		std::string jumpLabel;
		std::string currStmt = CFGStmtVect[i]->InstructStmt;
		std::vector<std::string> SplitText = returnSplitVect(currStmt);
		if((SplitText[0] == ";GTI")||(SplitText[0] == ";LTI")||(SplitText[0] == ";GEI")||(SplitText[0] == ";LEI")||(SplitText[0] == ";EQI")||(SplitText[0] == ";NEI")||(SplitText[0] == ";GTF")||(SplitText[0] == ";LTF")||(SplitText[0] == ";GEF")||(SplitText[0] == ";LEF")||(SplitText[0] == ";EQF")||(SplitText[0] == ";NEF")){
			
				//std::cout<<"FOUND A COMPARISON!!!"<<std::endl; //test string
				jumpLabel = SplitText[3];
				CFGStmtVect[i]->JumpLabel = jumpLabel;
				//std::cout<<"Jump Label for stmt "<<i<<" is --------> "<<CFGStmtVect[i]->JumpLabel<<std::endl; //test string
		

		}

		if(SplitText[0] == ";JUMP"){
			//std::cout<<"FOUND A JUMP!!!"<<std::endl; //test string
			jumpLabel = SplitText[1];
			CFGStmtVect[i]->JumpLabel = jumpLabel;
			//std::cout<<"Jump Label for stmt "<<i<<" is --------> "<<CFGStmtVect[i]->JumpLabel<<std::endl; //test string

		}

	}

	//Linking Nexts
	for(int j=0; j<CFGStmtVect.size(); j++){
		std::string currStmt = CFGStmtVect[j]->InstructStmt;
		std::vector<std::string> SplitText = returnSplitVect(currStmt);
		if((CFGStmtVect[j]->JumpLabel) != "\0"){
			//std::cout<<"JUMP LABEL for "<<j<<" is not empty!!"<<std::endl; //test string
			std::string labelString = ";LABEL "+(CFGStmtVect[j]->JumpLabel);
			for(int k=0; k<CFGStmtVect.size(); k++){
				std::string currStmt2 = CFGStmtVect[k]->InstructStmt;
				if(currStmt2 == labelString){
					if((SplitText[0] == ";GTI")||(SplitText[0] == ";LTI")||(SplitText[0] == ";GEI")||(SplitText[0] == ";LEI")||(SplitText[0] == ";EQI")||(SplitText[0] == ";NEI")||(SplitText[0] == ";GTF")||(SplitText[0] == ";LTF")||(SplitText[0] == ";GEF")||(SplitText[0] == ";LEF")||(SplitText[0] == ";EQF")||(SplitText[0] == ";NEF")){
						CFGStmtVect[j]->next.push_back(k);

					}

				if(SplitText[0] == ";JUMP"){
						CFGStmtVect[j]->next[0] = k;			
				}


				}
			}
	
		}
			
		
	}
	//std::cout<<"SIZE OF CFGVECT ----------- "<<CFGStmtVect.size()<<std::endl;
	//Linking Prevs
	
	for(int j=0; j<CFGStmtVect.size(); j++){
		int nextLen = CFGStmtVect[j]->next.size();
		for(int k = 0; k < nextLen; k++){
			int nextNum = CFGStmtVect[j]->next[k];
			if(nextNum >= CFGStmtVect.size())
			{
				continue;
			}
			CFGStmtVect[nextNum]->prev.push_back(j);
			//std::cout<<"Prev push success!"<<std::endl;		
		}
	}
	

	return CFGStmtVect;	
}


std::vector<CFGEntry*> generateGenKill(std::vector<CFGEntry*> CFGStmtVect){
	for(int i=0; i < CFGStmtVect.size(); i++){
		std::string currStmt = CFGStmtVect[i]->InstructStmt;
		std::vector<std::string> SplitText = returnSplitVect(currStmt);

		//Checks for STORE
		if((SplitText[0] == ";STOREI") || (SplitText[0] == ";STOREF")){
			CFGStmtVect[i]->genSet.push_back(SplitText[1]);	//Adding to genSet
			CFGStmtVect[i]->killSet.push_back(SplitText[2]); //Adding to killSet
			
		}

		//Checks for READ
		else if((SplitText[0] == ";READI") || (SplitText[0] == ";READF")){			
			CFGStmtVect[i]->killSet.push_back(SplitText[1]); //Adding to killSet			
		}

		//Checks for WRITE
		else if((SplitText[0] == ";WRITEI") || (SplitText[0] == ";WRITEF") || (SplitText[0] == ";WRITES")){			
			CFGStmtVect[i]->genSet.push_back(SplitText[1]); //Adding to genSet			
		}

		//Checks for PUSH
		else if(SplitText[0] == ";PUSH"){
			if(SplitText.size() == 2)
			{						
				CFGStmtVect[i]->genSet.push_back(SplitText[1]); //Adding to genSet	
			}		
		}

		//Checks for POP
		else if(SplitText[0] == ";POP"){
			if(SplitText.size() == 2)
			{			
				CFGStmtVect[i]->killSet.push_back(SplitText[1]); //Adding to killSet			
			}
		}

		//Checks for Arithmetic Operations
		else if((SplitText[0] == ";ADDI") || (SplitText[0] == ";ADDF") || (SplitText[0] == ";SUBI") || (SplitText[0] == ";SUBF") || (SplitText[0] == ";MULI") || (SplitText[0] == ";MULF") || (SplitText[0] == ";DIVI") || (SplitText[0] == ";DIVF")){
			CFGStmtVect[i]->genSet.push_back(SplitText[1]);	//Adding to genSet
			CFGStmtVect[i]->genSet.push_back(SplitText[2]);	//Adding to genSet
			CFGStmtVect[i]->killSet.push_back(SplitText[3]); //Adding to killSet
			
		}

		//Checks for Comparison 
		else if((SplitText[0] == ";GTI")||(SplitText[0] == ";LTI")||(SplitText[0] == ";GEI")||(SplitText[0] == ";LEI")||(SplitText[0] == ";EQI")||(SplitText[0] == ";NEI")||(SplitText[0] == ";GTF")||(SplitText[0] == ";LTF")||(SplitText[0] == ";GEF")||(SplitText[0] == ";LEF")||(SplitText[0] == ";EQF")||(SplitText[0] == ";NEF")){
			CFGStmtVect[i]->genSet.push_back(SplitText[1]);	//Adding to genSet
			CFGStmtVect[i]->genSet.push_back(SplitText[2]);	//Adding to genSet

		}

		//Checks for Function call
		else if((SplitText[0] == ";JSR")){
			SymbolTable* currentTab;
		 	currentTab = symtabStack.top();
		              while(currentTab != NULL){		                
		                  if(currentTab->scope == "GLOBAL"){
					int ordTabSize = currentTab->ordered_table.size();
					for(int x = 0; x < ordTabSize; x++){
						CFGStmtVect[i]->genSet.push_back(currentTab->ordered_table[x]->var_name);	//Adding to genSet
					}				
				
				}

			currentTab = currentTab->parent;
			}

		}


	}


	return CFGStmtVect;
}

//Computing Liveness
std::vector<CFGEntry*> analyzeLiveness(std::vector<CFGEntry*> CFGStmtVect){
	isLivenessChanged = false;
	int numCFGentries = CFGStmtVect.size();
	for(int i = numCFGentries-2; i >= 0; i--){
	
		std::set<std::string> prevLiveIN = CFGStmtVect[i]->liveIN;
		std::set<std::string> prevLiveOUT = CFGStmtVect[i]->liveOUT;


	//Computing LIVE-OUT
		for(int j = 0; j < CFGStmtVect[i]->next.size(); j++){
			std::set<std::string> tempSet = CFGStmtVect[CFGStmtVect[i]->next[j]]->liveIN;
			for(std::set<std::string>::iterator it = tempSet.begin(); it != tempSet.end(); it++){
				CFGStmtVect[i]->liveOUT.insert(*it);
			}
		}
	//Computing LIVE-IN
		//Adding LIVE-OUT
		std::set<std::string> tempLiveOUT = CFGStmtVect[i]->liveOUT;	
		for(std::set<std::string>::iterator it = tempLiveOUT.begin(); it != tempLiveOUT.end(); it++){
			CFGStmtVect[i]->liveIN.insert(*it);
		}

		//Minusing KILL-set
		for(int j = 0; j < CFGStmtVect[i]->killSet.size(); j++){	
			CFGStmtVect[i]->liveIN.erase(CFGStmtVect[i]->killSet[j]);
		}

		//Adding GEN-set
		for(int j = 0; j < CFGStmtVect[i]->genSet.size(); j++){	
			CFGStmtVect[i]->liveIN.insert(CFGStmtVect[i]->genSet[j]);
		}

		
		if((prevLiveIN != CFGStmtVect[i]->liveIN) || (prevLiveOUT != CFGStmtVect[i]->liveOUT)){
			isLivenessChanged = true;
		}

	}

	return CFGStmtVect;
}


 
/*
  void yyerror(const char* str){}
  extern int yylex();
  extern char* yytext;
  SymbolTable* root; 
  VectorTable* vectRoot;
  
  std::stack<SymbolTable *> symtabStack;
  std::stack<VectorTable *> vectTabStack;
  std::stack<ASTNode*> ifStack;
  std::vector<ASTNode*> FuncVect;*/
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
%type <ASTPtr> primary call_expr expr postfix_expr factor_prefix factor expr_prefix cond assign_expr assign_stmt control_stmt return_stmt base_stmt if_stmt stmt read_stmt write_stmt while_stmt loop_stmt
%type <ASTPtrVectPtr> stmt_list else_part func_body expr_list expr_list_tail



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

		    VectorTable* currVectTabTOP = vectTabStack.top();
		    std::string funcJsr;
		    //funcJsr = funcJsr + ";JSR FUNC_"+currVectTabTOP->vectTabName;
		    finalIRvector.insert(finalIRvector.begin(),";HALT"); 
		    funcJsr = funcJsr + ";JSR FUNC_main"; 
   		    finalIRvector.insert(finalIRvector.begin(),funcJsr);

		    finalIRvector.insert(finalIRvector.begin(),";PUSHREGS");
		    finalIRvector.insert(finalIRvector.begin(),";PUSH");			
		    finalIRvector.insert(finalIRvector.begin(),";IR CODE");		

		    //VectorTable* currVectTabTOP = vectTabStack.top();
		    currVectTabTOP->PrintIRcodeVector(finalIRvector);

		    //Looping to create & number CFGEntries
		    CFGStmtVect = assignCFGID(finalIRvector);

		    //Doing Next & Prev Linking		    
		    CFGStmtVect = buildCFG(CFGStmtVect);
		    /*
			for(int k=0; k<CFGStmtVect.size(); k++){
				int lenNext = CFGStmtVect[k]->next.size();
				int lenPrev = CFGStmtVect[k]->prev.size();
				std::cout<<"Stmt #"<<k<<" prev size: "<<lenPrev<<", next size: "<<lenNext<<std::endl;
				//std::cout<<"Stmt #"<<k<<", next size: "<<lenNext<<std::endl;
				if((lenNext == 1) && (lenPrev == 1))
				//if((lenNext == 1))
				{
					std::cout<<"Printing CFG entries ----------------------->>> "<<CFGStmtVect[k]->StmtID<<"     "<<CFGStmtVect[k]->InstructStmt<<"  NEXT ID:   "<<CFGStmtVect[k]->next[0]<<"  PREV ID:   "<<CFGStmtVect[k]->prev[0]<<std::endl;
				}
				if(lenNext > 1)
				{
					std::cout<<"Printing CFG entries ----------------------->>> "<<CFGStmtVect[k]->StmtID<<"     "<<CFGStmtVect[k]->InstructStmt<<std::endl;
					for(int i = 0; i<lenNext; i++){	
						std::cout<<"------ NEXT ID #"<<i+1<<" :   "<<CFGStmtVect[k]->next[i]<<std::endl;
					}
				}
				
				if(lenPrev > 1)
				{
					std::cout<<"Printing CFG entries ----------------------->>> "<<CFGStmtVect[k]->StmtID<<"     "<<CFGStmtVect[k]->InstructStmt<<std::endl;
					for(int i = 0; i<lenPrev; i++){	
						std::cout<<"------ PREV ID #"<<i+1<<" :   "<<CFGStmtVect[k]->prev[i]<<std::endl;
					}
				}

			}*/
			
			//Generating GEN & KILL sets
			CFGStmtVect = generateGenKill(CFGStmtVect);
			/*
			for(int k=0; k<CFGStmtVect.size(); k++){
				std::cout<<"Printing CFG entries ----------------------->>> "<<CFGStmtVect[k]->StmtID<<"     "<<CFGStmtVect[k]->InstructStmt<<std::endl;
				if(CFGStmtVect[k]->genSet.size() > 0){
					for(int a = 0; a < CFGStmtVect[k]->genSet.size(); a++){
						std::cout<<"GEN Set element #"<<a+1<<" --->  "<<CFGStmtVect[k]->genSet[a]<<std::endl;					
					}				
				}
				if(CFGStmtVect[k]->killSet.size() > 0){
					for(int a = 0; a < CFGStmtVect[k]->killSet.size(); a++){
						std::cout<<"KILL Set element #"<<a+1<<" --->  "<<CFGStmtVect[k]->killSet[a]<<std::endl;					
					}				
				}
			}*/

			//Computing Liveness
			do{

				CFGStmtVect = analyzeLiveness(CFGStmtVect);
				
			}while(isLivenessChanged);

			for(int k=0; k<CFGStmtVect.size(); k++){
				int inCount = 0;
				int outCount = 0;
				std::cout<<"Printing CFG entries ----------------------->>> "<<CFGStmtVect[k]->StmtID<<"     "<<CFGStmtVect[k]->InstructStmt<<std::endl;
				if(CFGStmtVect[k]->liveIN.size() > 0){
					std::cout<<"LIVE-IN size:   "<<CFGStmtVect[k]->liveIN.size()<<std::endl;
					for(std::set<std::string>::iterator a = CFGStmtVect[k]->liveIN.begin(); a != CFGStmtVect[k]->liveIN.end(); a++){
						inCount++;
						std::cout<<"LIVE IN element #"<<inCount<<" --->  "<<(*a)<<std::endl;					
					}				
				}
				if(CFGStmtVect[k]->liveOUT.size() > 0){
					std::cout<<"LIVE-OUT size:   "<<CFGStmtVect[k]->liveOUT.size()<<std::endl;
					for(std::set<std::string>::iterator a = CFGStmtVect[k]->liveOUT.begin(); a != CFGStmtVect[k]->liveOUT.end(); a++){
						outCount++;
						std::cout<<"LIVE OUT element #"<<outCount<<" --->  "<<(*a)<<std::endl;					
					}				
				}
			}//End of Liveliness computation

  
		    currVectTabTOP->IRtoAssembly(finalIRvector);  

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
		    

		    AssignNode* asnTempo = new AssignNode(*$2, *$4); 
		    ASTNode* AsnAST = dynamic_cast<ASTNode*>(asnTempo); 

		    

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

		     //OFFSET VALUE SETTING
		     tmp->symOffset = offset;
		     offset--;
		
			//std::cout<<tmp->var_name<<" offset:  "<<tmp->symOffset<<std::endl;

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

		     //OFFSET VALUE SETTING
		    tmp->symOffset = offset;
		    offset++;

		    //std::cout<<tmp->var_name<<" offset:  "<<tmp->symOffset<<std::endl;		    
	
                    symtabStack.top()->addDecl(tmp);
		
	
                  };

param_decl_tail   : COMMA param_decl param_decl_tail |;

/* Function Declarations */
func_declarations : func_decl func_declarations |;

func_decl         : FUNCTION any_type id OPENPARAN 
                  {
			    IRcodeVector.clear();
			    //Symbol Table
		            SymbolTable *func = new SymbolTable(*$3, symtabStack.top());
		            symtabStack.top()->children.push_back(func);
			    //std::cout<<"symtabstack TOP scope  1    : "<<symtabStack.top()->scope<<std::endl;
			    //std::cout<<"printing var decl"<<std::endl;
			    if (printVDnum == 0){
				    symtabStack.top()->printVarDecl();  //Printing var decl
				    printVDnum = 1;
			    //std::cout<<"DONE printing var decl"<<std::endl;
			    }
		            symtabStack.push(func);
			    //std::cout<<"pushed function onto symtabStack"<<std::endl;
			    //Vector Table
			    VectorTable *vectFunc = new VectorTable(*$3, vectTabStack.top());
			    vectTabStack.top()->vectChildren.push_back(vectFunc);
			    vectTabStack.push(vectFunc);
			    //std::cout<<"pushed vector table of function onto vectTabStack"<<std::endl;
			    //Global offset:
			    offset = 2;
                  } 
                  param_decl_list CLOSEPARAN _BEGIN 
		  {//Global offset:
		    	offset = -1;
		  } 
		  func_body 
		  {
			VectorTable* currVectTabTOP = vectTabStack.top();
			currVectTabTOP->stmt_listPtrVect = $10;
			
			//std::cout<<"Function: "<<currVectTabTOP->vectTabName<<std::endl;

			//std::cout<<"Calling stack iterator for ir"<<std::endl;
			currVectTabTOP->entireTable = symtabStack.top();
			SymbolTable* symTab = symtabStack.top();
		        std::vector<CodeObject*> vect = currVectTabTOP->StackIteratorforIR(coVect,currVectTabTOP->vectTabName,symtabStack.top());
			//std::cout<<"PRINTING IR VECT NOW"<<std::endl;

			//BEGINNING IR code statements
			
			//currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),";LINK 1");	  ///Instead of hardcoding, just put in number of local args for func

			int numLocalArgs = 0;
			for (int k = 0; k<(symTab->ordered_table).size(); k++){
				if ((symTab->ordered_table)[k]->symOffset < 0){
					//std::cout<<(symTab->ordered_table)[k]->var_name<<std::endl;
					numLocalArgs++;
				}
			}
			//std::cout<<"Local args: "<<numLocalArgs<<std::endl;
			std::stringstream ss;
			ss << numLocalArgs;
			std::string strNum(ss.str());
			strNum = ";LINK "+strNum;
			currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),strNum);	  ///Instead of hardcoding, just put in number of local args for func



			//function name label
			std::string funcLabel;

			//std::cout<<"Now adding label for:  "<<currVectTabTOP->vectTabName<<std::endl;
			funcLabel = funcLabel + ";LABEL FUNC_"+currVectTabTOP->vectTabName;
			//std::cout<<"funclabel is :  "<<funcLabel<<std::endl;
			currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),funcLabel);
			
			//std::cout<<"Printing first element of vector: should be function label : "<<currVectTabTOP->finalIRstringVector[0]<<std::endl;			
	
			//currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),";HALT");
			/*
			std::string funcJsr;
			funcJsr = funcJsr + ";JSR FUNC_"+currVectTabTOP->vectTabName; 
			currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),funcJsr);

			currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),";PUSHREGS");
			currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),";PUSH");			
			currVectTabTOP->finalIRstringVector.insert(currVectTabTOP->finalIRstringVector.begin(),";IR CODE");			
			*/			
			currVectTabTOP->finalIRstringVector.push_back(";UNLINK");			
			currVectTabTOP->finalIRstringVector.push_back(";RET");			
			
			
			//currVectTabTOP->PrintIRcodeVector(currVectTabTOP->finalIRstringVector);  
			//finalIRvector = currVectTabTOP->finalIRstringVector;     //trying to split function wise and then have 1 main vector
			tempIRvector = currVectTabTOP->finalIRstringVector;
			/*
			std::cout<<"<<<<<<<<<<<<<<< PRINTING tempIRvector now >>>>>>>>>>>>>>>>"<<std::endl;
			for (int it = 0; it < tempIRvector.size(); it++){
				std::cout<<tempIRvector[it]<<std::endl;
			}
			std::cout<<"<<<<<<<<<<<<<<< DONE PRINTING tempIRvector >>>>>>>>>>>>>>>>"<<std::endl;
			*/			
			//currVectTabTOP->IRtoAssembly(currVectTabTOP->finalIRstringVector);  
			/*
			std::cout<<"<<<<<<<<<<<<<<< PRINTING IRcodeVector now >>>>>>>>>>>>>>>>"<<std::endl;
			for (int it = 0; it < IRcodeVector.size(); it++){
				std::cout<<IRcodeVector[it]<<std::endl;
			}
			std::cout<<"<<<<<<<<<<<<<<< DONE PRINTING IRcodeVector >>>>>>>>>>>>>>>>"<<std::endl;
			*/

			finalIRvector.insert(finalIRvector.end(), tempIRvector.begin(), tempIRvector.end());

			

		  }
		  END {
                    symtabStack.pop(); //Symbol Table		    
		    vectTabStack.pop(); //Vector Table
                  };

func_body         : decl stmt_list {
			 $$ = $2;
		};

/* Statement List */
/*stmt_list         : stmt stmt_list  
		  | ; */

stmt_list         : stmt stmt_list {$$ = $2; $$->insert($$->begin(), $1); } 
		  | {$$ = new std::vector<ASTNode*>;}; 

stmt              : base_stmt {$$ = $1;}
	          | if_stmt {$$ = $1; };
			    
			
                  | loop_stmt {$$ = $1; };

 
base_stmt         : assign_stmt {$$ = $1;}
		  | read_stmt {$$ = $1;
					
			      }
		  | write_stmt {$$ = $1;
				
             		}
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
read_stmt         : READ OPENPARAN id_list CLOSEPARAN SEMICOLON
		    {
			$$ = new ASTNode(); //Master ASTNode for IO creation  **************************************************************************************
			$$->IOType = "READ";

			for(std::list<std::string>::iterator it=(*$3).begin();it!=(*$3).end();++it) 
			{
			   //if stmt to check for newline
			   if(*it == "newline"){
				

				IONode *tempo = new IONode (NULL, "READ"); //IONode creation
		                ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
				

				VectorTable* currVectTabTop = vectTabStack.top();
				(currVectTabTop->stmtVect).push_back(ASTtempo);
				$$->IOIdVect.push_back(ASTtempo);
				
				} //end of if - newline
			   else{
			      
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

		                  for (int i = 0; i< currentTab->ordered_table.size(); i++){
		                    if (currentTab->ordered_table[i]->var_name == *it){
				      			     
		                      IONode *tempo = new IONode (currentTab->ordered_table[i], "READ"); //IONode creation
		                      ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
				      
				      VectorTable* currVectTabTop = vectTabStack.top();
				      (currVectTabTop->stmtVect).push_back(ASTtempo);
				      
				      $$->IOIdVect.push_back(ASTtempo); 	//Adding to Master IO ASTNode IOIdVect *******************************************************				
				     
		                    }
		                  }
		                  break;    
                      
		                } //end of else

		                currentTab = currentTab->parent;

		              } //end of while
			} //end of else - newline
		     }//end of for
		   	
		    }; 


//WRITE IO STMT
write_stmt        : WRITE OPENPARAN id_list CLOSEPARAN SEMICOLON { 
			$$ = new ASTNode(); //Master ASTNode for IO creation  **************************************************************************************
			$$->IOType = "WRITE";

			for(std::list<std::string>::iterator it=(*$3).begin();it!=(*$3).end();++it) 
			{
			   //"newline" case
			   if(*it == "newline"){
				

				IONode *tempo = new IONode (NULL, "WRITE"); //IONode creation
		                ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
				

				VectorTable* currVectTabTop = vectTabStack.top();
				(currVectTabTop->stmtVect).push_back(ASTtempo);

				$$->IOIdVect.push_back(ASTtempo);

				} //end of if - newline
			   
			  //Symbols
			  else{
			      //if stmt to check for newline
			      SymbolTable* currentTab;
		              currentTab = symtabStack.top();
		              while(currentTab != NULL){

		                if(currentTab->table.find(*it) == currentTab->table.end()){
		                  if(currentTab->scope == "GLOBAL"){
				    std::cout<<"I am in WRITE"<<"\n"<<std::endl;
		                    std::cout<<"EXPRESSION ERROR"<<"\n"; //needs help
		              exit(1);
		                  }

		                } //end of if
		                else{
		                  //std::cout<<currentTab->scope<<std::endl;
		                  for (int i = 0; i< currentTab->ordered_table.size(); i++){
		                    if (currentTab->ordered_table[i]->var_name == *it){			      
				      
				      
		                      IONode *tempo = new IONode (currentTab->ordered_table[i], "WRITE"); //IONode creation
		                      ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
				      

				      VectorTable* currVectTabTop = vectTabStack.top();
				      (currVectTabTop->stmtVect).push_back(ASTtempo);				      

					$$->IOIdVect.push_back(ASTtempo); //Adding to Master IO ASTNode IOIdVect *******************************************************
				     
		                    }
		                  }
		                  break;                          
		                } //end of else
		                currentTab = currentTab->parent;
		              } //end of while
			} //end of else - newline
		     }//end of for
			
		   } ; //end of write_stmt 

		 
		
		


return_stmt       : RETURN expr SEMICOLON {ReturnNode* retnTempo = new ReturnNode($2); $$ = dynamic_cast<ASTNode*>(retnTempo);};

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

call_expr         : id OPENPARAN expr_list CLOSEPARAN 
		    {
			//std::cout<<"-------------------  CALL EXPR IS CALLED -------------------------"<<std::endl;
			CallExprNode* callnTempo = new CallExprNode($3, $1);
			$$ = dynamic_cast<ASTNode*>(callnTempo); 
		    }; 

expr_list         : expr expr_list_tail {$$ = $2; $$->insert($$->begin(), $1);} | {$$ = NULL;}; 
expr_list_tail    : COMMA expr expr_list_tail {$$ = $3; $$->insert($$->begin(), $2);} 
		    | {$$ = new std::vector<ASTNode*>;} ; 

primary           : OPENPARAN expr CLOSEPARAN {$$ = $2;}
		  | id  {
			
                      SymbolTable* currentTab;
                      currentTab = symtabStack.top();
                      while(currentTab != NULL){
                        if(currentTab->table.find(*$1) == currentTab->table.end()){
                         if(currentTab->scope == "GLOBAL"){
			    std::cout<<"I am primary"<<std::endl;
                            std::cout<<"PRIMARY ERROR"<<"\n"; //needs help
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
		    //std::cout<<"If being detected!"<<std::endl;
		    ++ifCounter; 
		
                  } decl stmt_list 
                  {
                    symtabStack.pop();//pop off the if block
		    
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Pop, Create */
                  } 
		  else_part ENDIF 
		  {	
			$$ = new If_ElseNode($3, $7, $9);
			//std::cout<<"LINE: "<<__LINE__<<"\n";
			$$->If_ElseType = "IF";	  		    		
			//$$ = globalIfNodeTEMP;
			symtabStack.pop();
                      };
                  

else_part         : ELSE {/*std::cout<<"Else being detected!"<<std::endl;*/ ++elseCounter;} decl stmt_list
		    { $$ = $4;}	 
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
                    //symtabStack.pop();//pop off the if block
		    
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Pop, Create */
                  }
                  decl stmt_list ENDWHILE
                  {
		    $$ = new WhileNode($3, $7);
		    //std::cout<<"LINE: "<<__LINE__<<"\n";		    
                    symtabStack.pop();
                  };


/*ECE468 ONLY*/
control_stmt      : return_stmt {$$ = $1;} ;
loop_stmt         : while_stmt {$$ = $1;} ;



%%
