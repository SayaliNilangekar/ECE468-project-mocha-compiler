//
// Created by Lenovo on 9/29/2018.
//
#include<iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <typeinfo>
#include "SymbolTable.h"
#include<cstdlib>


long long int tempNum = 0; //From IR.cpp



void SymbolTable::addDecl(Symbol *entry) {
	if(table.find(entry->var_name) != table.end()){
		std::cout<<"DECLARATION ERROR "<<entry->var_name<<"\n";
		exit(1);
	}
	table.insert(std::make_pair(entry->var_name, entry));
	ordered_table.push_back(entry);//only needed for step3
}

void SymbolTable::PrintSymbolTables(){
	/*std::cout<<"Need to print here in SymbolTable.cpp, you should print the ordered_table"<<
	", then you should print the children in a recursive in preorder manner.\n";  */
	std::cout<<"Symbol table "<<scope<<std::endl;
	int sz;
	sz = ordered_table.size();
	for (int i=0; i<sz; i++){
		std::string name;
		int type;
		std::string val;
		name.assign(ordered_table[i]->var_name);
		type = ordered_table[i]->var_type;
		//std::cout<<"HERE";
		//std::cout<<"name: "<<name<<std::endl;
		//std::cout<<"type: "<<type<<std::endl;

		if (type == 275) {
			std::cout<<"name "<<name<<" type "<<"INT"<<std::endl;		
		}	
		else if (type == 278) {
			std::cout<<"name "<<name<<" type "<<"FLOAT"<<std::endl;		
		}	

		else if (type == 277) {
			//val = root->declVector[i]->str_var_value;
			val.assign(ordered_table[i]->str_var_value);
			std::cout<<"name "<<name<<" type "<<"STRING"<<" value "<<val<<std::endl;	
		}
	}
	
	if (!children.empty()){
		int childSize;
		childSize = children.size();
		for (int j=0; j<childSize; j++){
			std::cout<<std::endl;
			(children[j])->PrintSymbolTables();
		}			
	}	

}

 void VectorTable::printStack(){
	IRCode ir_code;
	for(int i=0; i < stmtVect.size(); i++) {

		if (stmtVect[i]->IOType == "WRITE"){
			std::cout<<std::endl;
			//CodeObj* AC3_write = return_write_3AC(stmtVect[i]);
			//ir_code.complete_IR_code.push_back(AC3_write);
		}
		else if (stmtVect[i]->IOType == "READ")
			std::cout<<std::endl;
		else
		{
			std::cout<<std::endl;
			
			//CodeObj* AC3_code_rhs = return_RHS_3AC((stmtVect)[i]->assignRHS);
			//ir_code.complete_IR_code.push_back(AC3_code_rhs);
			//CodeObj* AC3_code_lhs = return_LHS_3AC((stmtVect)[i]->assignLHS, AC3_code_rhs);
			//ir_code.complete_IR_code.push_back(AC3_code_lhs);
		}				
	}
	//print_IR_code(ir_code);
	//convert_ir_to_assembly(ir_code);

	if (!vectChildren.empty()){
		int childSize;
		childSize = vectChildren.size();
		for (int j=0; j<childSize; j++){
			std::cout<<std::endl;
			(vectChildren[j])->printStack();
		}
	
	}
}

CodeObj* return_write_3AC(ASTNode* astnode){

	CodeObj* newObj = new CodeObj();
	IRNode newnode;

	switch(astnode->tokType){
		case 4: 
			newnode.instruction = ";WRITES";
			break;
		case 2:
		case 5:
			newnode.instruction = ";WRITEI";
			break;
		case 3:
		case 6:
			newnode.instruction = ";WRITEF";
			break;
	}
	newnode.oper1 = astnode->token;
	newnode.oper2 = "\0";
	newnode.result = "\0";

	newObj->InstrSeq.push_back(newnode);
	newObj->result = "\0";
	newObj->type = astnode->tokType;

	return newObj;
}

void convert_ir_to_assembly(IRCode ir_code){
	for (int i = 0 ; i < ir_code.complete_IR_code.size(); i++){
		convert_3AC_code(ir_code.complete_IR_code[i]);
	}
}

void convert_3AC_code(CodeObj* currentCodeExpr){
	for (int i = 0; i < currentCodeExpr->InstrSeq.size(); i++){
		// print instr
		if(currentCodeExpr->InstrSeq[i].instruction == ";MULI")
			std::cout<<"muli"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";ADDI")
			std::cout<<"addi"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";SUBI")
			std::cout<<"subi"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";DIVI")
			std::cout<<"divi"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";MULF")
			std::cout<<"mulr"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";ADDF")
			std::cout<<"addr"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";SUBF")
			std::cout<<"subr"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";DIVF")
			std::cout<<"divr"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";READI") //
			std::cout<<"readi"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";READF") //
			std::cout<<"muli"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";STOREI")
			std::cout<<"move"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";STOREF")
			std::cout<<"move"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";WRITEI")
			std::cout<<"sys writei"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";WRITEF")
			std::cout<<"sys writef"<<" ";
		if(currentCodeExpr->InstrSeq[i].instruction == ";WRITES")
			std::cout<<"sys writes"<<" ";
		// print oper1
		std::cout<<currentCodeExpr->InstrSeq[i].oper1<<" ";
		// print oper2
		std::cout<<currentCodeExpr->InstrSeq[i].oper2<<" ";
		// print result
		std::cout<<currentCodeExpr->InstrSeq[i].result<<" "<<std::endl;
	} 
}


//Code from IR.cpp
// print individual STATEMENTS function for debugging
void print_3AC_code(CodeObj* currentCodeExpr){
	for (int i = 0; i < currentCodeExpr->InstrSeq.size(); i++){
		std::cout<<currentCodeExpr->InstrSeq[i].instruction<<" ";
		std::cout<<currentCodeExpr->InstrSeq[i].oper1<<" ";
		std::cout<<currentCodeExpr->InstrSeq[i].oper2<<" ";
		std::cout<<currentCodeExpr->InstrSeq[i].result<<" "<<std::endl;
	} 
}

void print_IR_code(IRCode ir_code){
	for (int i = 0 ; i < ir_code.complete_IR_code.size(); i++){
		print_3AC_code(ir_code.complete_IR_code[i]);
	}
}

CodeObj* return_LHS_3AC(std::string Left, CodeObj* Right){
	CodeObj* newObj = new CodeObj();
	IRNode newnode;
	
	// assign stuff to IRnode
	newnode.oper1 = Right->result;
	//newnode.oper2 = generateTemp();
	newnode.result = Left;
	switch(Right->type){
		case 2:
		case 5:
			newnode.instruction = ";STOREI";
			break;
		case 3:
		case 6:
			newnode.instruction = ";STOREF";
			break;

	}
	// write IRnode to the newObj InstrSeq field
	newObj->InstrSeq.push_back(newnode);
	// fill in type
	newObj->type = Right->type;
	// fill in result field 
	newObj->result = Left;
	
	return newObj;
}


CodeObj* return_RHS_3AC(ASTNode* astNode){

	//we have a stack of each scope/function which points to vectors list. The vector list contains all the nodes which are all AST but
	//you have to iterate through the stack to get the vector with all nodes
	// 1. IOnodes do not have left or right : you have to check if they have IOtype as READ or WRITE then you are sure that it is IONode. IONode just have IOtype, token
	// 2. Assign Node contains LHS and RHS :
	//		To access LHS => assign_node->assignLHS
	//		To access rhs tree do assign_node->assignRHS. assignRHS is the root node of the AST.
	// CHECK THE PRINT STACK FUNCTION IN SYMBOLTABLE.CPP of src.zip I have attached
	
	while (astNode != NULL){
		CodeObj* newObj = new CodeObj();
		CodeObj* left_codeObj = return_RHS_3AC(astNode->leftChild);
		CodeObj* right_codeObj = return_RHS_3AC(astNode->rightChild);
		

		// now generate code for yourself
		if (astNode->tokType == 1){		// arithmetic node
			IRNode newnode;
		
			// assign operator fields to newnode
			newnode.oper1 = left_codeObj->result;
			newnode.oper2 = right_codeObj->result;

			// assign result location to new temporary
			newnode.result = generateTemp();

			// figure out instruction code
			char oper;
			std::string oper_string = astNode->token;		// +, -, *. /
			if (oper_string == "+"){
				oper = '+';
			}
			else if (oper_string == "-"){
				oper = '-';
			}
			else if (oper_string == "*"){
				oper = '*';
			}
			else{
				oper = '/';
			}
			int type = left_codeObj->type;		// int or float

			switch(type){
				case 2:		// int
				case 5:
					switch(oper){

						case '+': newnode.instruction = ";ADDI";
							break;
						case '-': newnode.instruction = ";SUBI";
							break;
						case '*': newnode.instruction = ";MULI";
							break;
						case '/': newnode.instruction = ";DIVI";
							break;
					}
					break;
				case 3:		// float
				case 6:	
					switch(oper){
						case '+': newnode.instruction = ";ADDF";
							break;
						case '-': newnode.instruction = ";SUBF";
							break;
						case '*': newnode.instruction = ";MULF";
							break;
						case '/': newnode.instruction = ";DIVF";
							break;
					}
					break;
				}

				// fill in codeObj attributes
				newObj->type = type;
				newObj->result = newnode.result;
				for (int i = 0; i < left_codeObj->InstrSeq.size(); i++){
					newObj->InstrSeq.push_back(left_codeObj->InstrSeq[i]);
				}
				for (int i = 0; i < right_codeObj->InstrSeq.size(); i++){
					newObj->InstrSeq.push_back(right_codeObj->InstrSeq[i]);
				}
				newObj->InstrSeq.push_back(newnode);

		}
		else if (astNode->tokType == 6 || astNode->tokType == 5){	// if it is a literal
		/*
					 * NOT SURE IF THIS NECESSARY *
			newObj->InstrSeq.push_back(left_codeObj->InstrSeq);
			newObj->InstrSeq.push_back(right_codeObj->InstrSeq);
		*/
			// creating current 3AC
			IRNode newnode;
			newnode.oper1 = astNode->token;
			newnode.oper2 = "\0";
			newnode.result = generateTemp();

			switch(astNode->tokType){
				case 5:	newnode.instruction = ";STOREI";
						break;
				case 6: newnode.instruction = ";STOREF";
						break;
			}

			newObj->InstrSeq.push_back(newnode);
			newObj->type = astNode->tokType;
			newObj->result = newnode.result;

		}
		else{

			newObj->result = astNode->token;

			switch(astNode->tokType){
				case 2: newObj->type = 2;
					break;
				case 3: newObj->type = 3;
					break;
			}
		}
		return newObj;
	}
	return NULL;
}

std::string generateTemp(){
	std::string temp;
	temp = "r";
	temp = temp + std::to_string(tempNum++); // so example temp = "!T10"
	
	return temp;
}

