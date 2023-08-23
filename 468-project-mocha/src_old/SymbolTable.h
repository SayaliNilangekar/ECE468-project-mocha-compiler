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

class Symbol{
public:
    int var_type;
    std::string var_name;
    std::string str_var_value;

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
    
    
};




class ASTNode{
public:
	std::string token;
	Symbol* symb;
	ASTNode* rightChild;
	ASTNode* leftChild;
	int tokType;
	std::string IOType; //for IO Nodes
	std::string assignLHS; //for assign nodes
	std::string assignRHS_str;
	ASTNode* assignRHS; //for assign nodes


	//Constructors
	ASTNode(){}
	ASTNode(std::string tok, int tT): token(tok), tokType(tT), symb(NULL), rightChild(NULL), leftChild(NULL), IOType("NoIO"), assignLHS(NULL), assignRHS(NULL){}
	
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
			ASTNode::tokType = sy->var_type; //assigning symbole type to tokType of ASTNode
		}
		else{
			ASTNode::token = "newline";
			ASTNode::IOType = IOT;
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

class VectorTable{
public:
	std::string vectTabName; //can access "function" name with this	
	VectorTable* vectParent;
	std::vector <ASTNode*> stmtVect;
	std::vector<VectorTable *> vectChildren;
	void printStack();
	
	//Constructor
	VectorTable(std::string tabName, VectorTable* p): vectTabName(tabName), vectParent(p) {}

};


#endif //ECE468STEP3_SYMBOLTABLE_H
