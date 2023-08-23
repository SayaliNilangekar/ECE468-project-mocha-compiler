//
// Created by Lenovo on 9/29/2018.
//

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <list>
#include <set>

class Symbol{
public:
    int var_type;
    std::string var_name;
    std::string str_var_value;
    //Symbol offset
    int symOffset;

    Symbol(int t, std::string n, std::string v): var_type(t), var_name(n), str_var_value(v){}
    Symbol(int t, std::string n): var_type(t), var_name(n){}
};


class SymbolTable{
public:
    std::string scope;
    SymbolTable* parent;
    std::vector<SymbolTable *> children; //vector of all the children SymbolTables

    std::map<std::string, Symbol*> table;
    std::vector<Symbol*> ordered_table;//only needed for step3

    
    
    SymbolTable(std::string s, SymbolTable* p):scope(s), parent(p){}

    void PrintSymbolTables();
    void addDecl(Symbol* entry); //adds a declaration(of type Symbol) to vector
    void printVarDecl();
    int lhsOffset(std::string, std::string);
    int lhsType(std::string, std::string);
};




class ASTNode{
public:
	std::string token;
	Symbol* symb;
	ASTNode* rightChild;
	ASTNode* leftChild;
	int tokType;

	//for IO Nodes
	std::string IOType; 
	std::vector<ASTNode*> IOIdVect; //Vector of ASTNode* s containing all valid elements of "id_list" in a "READ" or "WRITE" ***********************************************************

	std::string assignLHS; //for assign nodes
	std::string assignRHS_str;
	ASTNode* assignRHS; //for assign nodes
	
	//For CondNode
	std::string compOp; 	
	std::string compBoolType;

	//For If_ElseNode
	std::vector<ASTNode*>* ThenStmtVect;
	std::vector<ASTNode*>* ElseStmtVect;
	ASTNode* condExpr;
	//std::vector<ASTNode*> IfElseChildren;
	//ASTNode* IfParent;
	ASTNode* ifPart;	
	ASTNode* elsePart;
	std::string If_ElseType;

	//For WhileNode
	std::vector<ASTNode*>* WhileStmtVect;
	std::string WhileType;

	//For CallExprNode
	std::vector<ASTNode*>* ExprVect;
	std::string* ExprID;

	//For ReturnNode
	ASTNode* returnExpr;

	std::string callType; //For CallExprNode & ReturnNode
	


	//Constructors
	ASTNode(){}
	ASTNode(std::string tok, int tT): token(tok), tokType(tT), symb(NULL), rightChild(NULL), leftChild(NULL), IOType("NoIO"), assignLHS("\0"), assignRHS(NULL), compOp("\0"), compBoolType("\0"), ifPart(NULL), elsePart(NULL), If_ElseType("\0"), WhileType("\0"),condExpr(NULL), callType("\0") {}
	
};


class VarRef : public ASTNode{
public:
	//Symbol* symb;

	//Constructor
	VarRef(Symbol* sy){
		ASTNode::symb = sy;
		ASTNode::token = sy->var_name;
		
		//Int id
		if(ASTNode::symb->var_type == 275)
		{			
			ASTNode::tokType = 2;
		}
		
		//Float id		
		else if(ASTNode::symb->var_type == 278)
		{
			ASTNode::tokType = 3;
		}

		//String id		
		else if(ASTNode::symb->var_type == 277)
		{
			ASTNode::tokType = 4;
		}				
	}
};

class Arithmetic : public ASTNode{
public:
	
	//Constructor
	Arithmetic(std::string tok){
		ASTNode::token = tok;
		ASTNode::tokType = 1;
	}
};

class LitNode : public ASTNode{
public:
	

	//Constructor
	LitNode(std::string lit, int tType){
		ASTNode::token = lit;
		ASTNode::tokType = tType;	
	}
};


class IONode : public ASTNode {
public:
    
    //Constructor
    IONode(Symbol* sy, std::string IOT){
        if(sy != NULL){        
            ASTNode::symb = sy;
            ASTNode::token = sy->var_name;
            ASTNode::IOType = IOT;
            //ASTNode::tokType = sy->var_type;

            //assigning symbole type to tokType of ASTNode
            //Int id
            if(sy->var_type == 275)
            {
                ASTNode::tokType = 2;
            }
        
            //Float id        
            else if(sy->var_type == 278)
            {
                ASTNode::tokType = 3;
            }

            //String id        
            else if(sy->var_type == 277)
            {
                ASTNode::tokType = 4;
            }            
            }
        else{
                ASTNode::token = "newline";
                ASTNode::IOType = IOT;
		ASTNode::tokType = 4;
                }
        
    }
};



class AssignNode : public ASTNode{
public:
	//Constructor
	AssignNode(std::string LHS, ASTNode* RHS){
		ASTNode::assignLHS = LHS;
		ASTNode::assignRHS = RHS;		
	
	}

	AssignNode(std::string LHS, std::string RHS){
		ASTNode::assignLHS = LHS;
		ASTNode::assignRHS_str = RHS;		
	
	}

};


class CondNode : public ASTNode{
public:
	
	//Constructor
	//CondNode(ASTNode* lChild, std::string comperOper, std::string resType, ASTNode* rChild): ASTNode::compOp(comperOper), ASTNode::compBoolType(resType){
	CondNode(ASTNode* lChild, std::string comperOper, std::string resType, ASTNode* rChild){
		ASTNode::compOp = comperOper;
		ASTNode::compBoolType = resType;
		ASTNode::leftChild = lChild;
		ASTNode::rightChild = rChild;
	}

};


class If_ElseNode : public ASTNode{
public:
	

	//Constructor
	If_ElseNode(ASTNode* c, std::vector<ASTNode*>* ThenStmt, std::vector<ASTNode*>* ElseStmt ){
		ASTNode::condExpr = c;
		ASTNode::ThenStmtVect = ThenStmt;
		ASTNode::ElseStmtVect = ElseStmt;
	}
};

class WhileNode : public ASTNode{
public:
	

	//Constructor
	WhileNode(ASTNode* c, std::vector<ASTNode*>* WhileStmt){
		ASTNode::condExpr = c;
		ASTNode::WhileStmtVect = WhileStmt;
		ASTNode::WhileType = "WHILE";
		
	}

};





class CodeObject{
public:
	std::string result;
	std::vector<std::string> instruction;
	std::string type;
	//void createIRvector;
	//void printIRcode;

	//Constructor
	CodeObject(){}
	CodeObject(std::string r,std::string t): result(r), type(t) {}
	CodeObject(std::string r,std::vector<std::string> i,std::string t): result(r), instruction(i), type(t) {}
	

};




class VectorTable{
public:
	std::string vectTabName; //can access "function" name with this	
	VectorTable* vectParent;
	std::vector <ASTNode*> stmtVect;

	SymbolTable* entireTable;

	//Step 5 Special :P
	std::vector <ASTNode*>* stmt_listPtrVect;

	std::vector <std::string> finalIRstringVector;

	std::vector<VectorTable *> vectChildren;
	std::vector<CodeObject*> completeIRvect;

	void printStack();
	CodeObject* createIRvector(ASTNode*);
	CodeObject* readCodeObj(ASTNode*);
	CodeObject* writeCodeObj(ASTNode*);	
	void printIRcode(std::vector<std::string>);
	void PrintIRcodeVector(std::vector<std::string>);
	std::vector<CodeObject*> StackIteratorforIR(std::vector<CodeObject*> coVect,std::string,SymbolTable*);
	//void PrintAssembly(std::vector<std::string> IRcodeList);
	void printAssembly(std::string IR);
	//void IRtoAssembly(std::vector<CodeObject*>);
	void IRtoAssembly(std::vector<std::string>);
	//Constructor
	VectorTable(std::string tabName, VectorTable* p): vectTabName(tabName), vectParent(p) {}


};

class CallExprNode : public ASTNode{
public:
	
	//Constructor
	CallExprNode(std::vector<ASTNode*>* ExpV, std::string* ExpID){
		//std::cout<<"Constructing call expr node"<<std::endl;
		ASTNode::ExprVect = ExpV;
		ASTNode::ExprID = ExpID;
		ASTNode::callType = "CallExpr";	
	}
};

class ReturnNode : public ASTNode{
public:
	
	//Constructor
	ReturnNode(ASTNode* retExp){
		ASTNode::returnExpr = retExp;
		ASTNode::callType = "Return";	
	}
};

class CFGEntry{
public:
	std::string InstructStmt;
	std::string JumpLabel;
	int StmtID;
	std::vector<int> prev;
	std::vector<int> next;
	std::vector<std::string> genSet;
	std::vector<std::string> killSet;
	std::set<std::string> liveIN;
	std::set<std::string> liveOUT;

	//Constructor
	CFGEntry(std::string instruction){
		InstructStmt = instruction;
		JumpLabel = "\0";
	}

};


#endif //ECE468STEP3_SYMBOLTABLE_H
