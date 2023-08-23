//
// Created by Lenovo on 9/29/2018.
//
#include<iostream>
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include <map>
#include <typeinfo>
#include "SymbolTable.h"
int tempReg = 0;
int labelNo = 0;
int storeTemps = 0;
int toStore = 0;
int formula = 0;
int numParams = 0;
int spclStore = 0;
std::string spclFormula;
std::vector<std::string> tempVect;

std::string currCtrlStruc = "\0";
std::vector<std::string> whileEndLabelVect;
std::vector<std::string> elseLabelVect;
std::vector<std::string> endIfLabelVect;

std::vector<std::string> IRcodeVector;




void SymbolTable::addDecl(Symbol *entry) {
	if(table.find(entry->var_name) != table.end()){
		std::cout<<"DECLARATION ERROR "<<entry->var_name<<"\n";
		exit(1);
	}
	table.insert(std::make_pair(entry->var_name, entry));
	//std::cout<<"INSIDE ADD DECL FUNC-----------> "<<entry->var_name<<std::endl;
	ordered_table.push_back(entry);//only needed for step3
	//std::cout<<"INSIDE ORDERED TABLE!!!!!!!!!!!"<<std::endl;
	/*for (int i =0; i< ordered_table.size(); i++)
	{	
		std::cout<<"ORDERED TABLE ELEMENT    "<<i<<" ------ "<<ordered_table[i]->var_name<<std::endl;
	}*/
}

void SymbolTable::PrintSymbolTables(){
	/*std::cout<<"Need to print here in SymbolTable.cpp, you should print the ordered_table"<<
	", then you should print the children in a recursive in preorder manner.\n";  */
	//std::cout<<"Symbol table "<<scope<<std::endl;
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


int SymbolTable::lhsOffset(std::string variable, std::string func){
	
	if (scope == func){
		for (int i = 0; i < ordered_table.size(); i++){
			if (ordered_table[i]->var_name == variable){
				return ordered_table[i]->symOffset;
			}
		}
	}


}


int SymbolTable::lhsType(std::string variable, std::string func){
	
	if (scope == func){
		for (int i = 0; i < ordered_table.size(); i++){
			if (ordered_table[i]->var_name == variable){
				return ordered_table[i]->var_type;
			}
		}
	}


}


void SymbolTable::printVarDecl(){
	/*std::cout<<"Need to print here in SymbolTable.cpp, you should print the ordered_table"<<
	", then you should print the children in a recursive in preorder manner.\n";  */
	//std::cout<<"Symbol table "<<scope<<std::endl;
	//std::cout<<"Printing var decl"<<scope<<std::endl;
	int sz;
	sz = ordered_table.size();
	//std::cout<<"size: "<<sz<<std::endl;
	for (int i=0; i<sz; i++){
		std::string name;
		int type;
		int offSet;
		std::string val;
		name.assign(ordered_table[i]->var_name);
		type = ordered_table[i]->var_type;
		offSet = ordered_table[i]->symOffset;
		//std::cout<<"HERE"<<std::endl;
		//std::cout<<"name: "<<name<<std::endl;
		//std::cout<<"type: "<<type<<std::endl;
		if (offSet == 0){
			if (type == 275 | type == 278) {
				//std::cout<<"HERE2"<<std::endl;
				std::cout<<"var "<<name<<std::endl;
				//std::cout<<"type: "<<type<<std::endl;		
			}	

			else if (type == 277) {
				//std::cout<<"HERE3"<<std::endl;
				//val = root->declVector[i]->str_var_value;
				val.assign(ordered_table[i]->str_var_value);
				std::cout<<"str "<<name<<" "<<val<<std::endl;	
			}
		}
	}

	if (!children.empty()){
		int childSize;
		childSize = children.size();
		for (int j=0; j<childSize; j++){
			//std::cout<<std::endl;
			(children[j])->printVarDecl();
		}			
	}	

}



std::string getNewLabel(std::string typeOfCtrlStruc){

	if (typeOfCtrlStruc == "while_start"){
		labelNo++;
		std::string newLabel = "WHILE_START_"+std::to_string((long long)labelNo);
		return newLabel;	
	}

	else if (typeOfCtrlStruc == "while_end"){
		labelNo++;
		std::string newLabel = "WHILE_END_"+std::to_string((long long)labelNo);
		return newLabel;	
	}

	else if (typeOfCtrlStruc == "else"){
		labelNo++;
		std::string newLabel = "ELSE_"+std::to_string((long long)labelNo);
		return newLabel;	
	}

	else if (typeOfCtrlStruc == "end_if_else"){
		labelNo++;
		std::string newLabel = "END_IF_ELSE_"+std::to_string((long long)labelNo);
		return newLabel;	
	}

}


void VectorTable::PrintIRcodeVector(std::vector<std::string> IRvect){
	
	for (int i = 0; i<IRvect.size(); i++){
		std::cout<<IRvect[i]<<std::endl;
	}

}



void VectorTable::printStack(){
	std::cout<<"In printStack()"<<std::endl;
	for(int i=0; i < stmtVect.size(); i++) 

					{
						if (stmtVect[i]->IOType == "WRITE")
							std::cout<<"Current Vector Table top element (is IO)"<<i<<" is ---  "<<(stmtVect)[i]->token<<std::endl;
						else if (stmtVect[i]->IOType == "READ")
							std::cout<<"Current Vector Table top element (is IO)"<<i<<" is ---  "<<(stmtVect)[i]->token<<std::endl;
						else
						{
							std::cout<<"Current Vector Table top element LHS id value (NO IO)"<<i<<" is ---  "<<(stmtVect)[i]->assignLHS<<std::endl;
							std::cout<<"Current Vector Table top element RHS root node value (NO IO)"<<i<<" is ---  "<<(stmtVect)[i]->assignRHS->token<<std::endl;	
						}				
					}


	if (!vectChildren.empty()){
		int childSize;
		childSize = vectChildren.size();
		for (int j=0; j<childSize; j++){
			std::cout<<std::endl;
			(vectChildren[j])->printStack();
		}
	
	}
}




CodeObject* VectorTable::createIRvector(ASTNode* node){
	
	if (node != NULL){
		//std::cout<<"Start of createIR"<<std::endl;
		//std::cout<<"token: "<<node->token<<std::endl;
		CodeObject* leftCodeObj = VectorTable::createIRvector(node->leftChild);
		CodeObject* rightCodeObj = VectorTable::createIRvector(node->rightChild);

		//std::cout<<"Recursion done"<<std::endl;
		//std::cout<<node->tokType<<std::endl;
		

		//**********Comparison operators check******************
		//For every comparison operator, create a string to print the opposite comparison with a label to jump to for that opp. comparison
		//Comparison op
		if (node->compOp != "\0"){
			if (node->compOp == ">"){
				std::string leftRes = leftCodeObj->result;
				std::string rightRes = rightCodeObj->result;

				//Create temporary
				std::string tempStr = "!T"+std::to_string((long long)tempReg);	
				//std::string tempStr = "!T"+s;
				tempReg++;
		
				std::string MyInstrucStr;
				std::string newLabel;
				if (currCtrlStruc == "while_start"){
					//std::cout<<"Okay I have a while_start"<<std::endl;
					newLabel = getNewLabel("while_end");
					whileEndLabelVect.insert(whileEndLabelVect.begin(),newLabel);
				}
				else if (currCtrlStruc == "else"){
					newLabel = getNewLabel("else");
					elseLabelVect.insert(elseLabelVect.begin(),newLabel);
				}		
				//std::cout<<newLabel<<std::endl;

				//Create Instruction
				if (leftCodeObj->type == "int"){
					MyInstrucStr = ";LEI "+leftRes+" "+rightRes+" "+newLabel;	
				}
		
				else if (leftCodeObj->type == "float"){
					MyInstrucStr = ";LEF "+leftRes+" "+rightRes+" "+newLabel;
				}
				//std::cout<<MyInstrucStr<<std::endl;


				std::vector<std::string> InstrucVector;

				std::vector<std::string> leftInst = leftCodeObj->instruction;
				std::vector<std::string> rightInst = rightCodeObj->instruction;

				if (!leftInst.empty()){
					InstrucVector.insert(InstrucVector.end(), leftInst.begin(), leftInst.end());
				
				}

				if (!rightInst.empty()){
					InstrucVector.insert(InstrucVector.end(), rightInst.begin(), rightInst.end());
				}
			
				InstrucVector.push_back(MyInstrucStr);	
				//VectorTable::completeIRvect.push_back(MyInstrucStr);
	
				std::string type = leftCodeObj->type;
			
				CodeObject* co = new CodeObject(tempStr,InstrucVector,type);

				return co;
				
			}
			if (node->compOp == ">="){
				std::string leftRes = leftCodeObj->result;
				std::string rightRes = rightCodeObj->result;

				//Create temporary
				std::string tempStr = "!T"+std::to_string((long long)tempReg);	
				//std::string tempStr = "!T"+s;
				tempReg++;
		
				std::string MyInstrucStr;
				std::string newLabel;
				if (currCtrlStruc == "while_start"){
					//std::cout<<"Okay I have a while_start"<<std::endl;
					newLabel = getNewLabel("while_end");
					whileEndLabelVect.insert(whileEndLabelVect.begin(),newLabel);
				}		
				else if (currCtrlStruc == "else"){
					newLabel = getNewLabel("else");
					elseLabelVect.insert(elseLabelVect.begin(),newLabel);				
				}
				//std::cout<<newLabel<<std::endl;

				//Create Instruction
				if (leftCodeObj->type == "int"){
					MyInstrucStr = ";LTI "+leftRes+" "+rightRes+" "+newLabel;	
				}
		
				else if (leftCodeObj->type == "float"){
					MyInstrucStr = ";LTF "+leftRes+" "+rightRes+" "+newLabel;
				}
				//std::cout<<MyInstrucStr<<std::endl;


				std::vector<std::string> InstrucVector;

				std::vector<std::string> leftInst = leftCodeObj->instruction;
				std::vector<std::string> rightInst = rightCodeObj->instruction;

				if (!leftInst.empty()){
					InstrucVector.insert(InstrucVector.end(), leftInst.begin(), leftInst.end());
				
				}

				if (!rightInst.empty()){
					InstrucVector.insert(InstrucVector.end(), rightInst.begin(), rightInst.end());
				}
			
				InstrucVector.push_back(MyInstrucStr);	
				//VectorTable::completeIRvect.push_back(MyInstrucStr);
	
				std::string type = leftCodeObj->type;
			
				CodeObject* co = new CodeObject(tempStr,InstrucVector,type);

				return co;
			}
			if (node->compOp == "<"){
				std::string leftRes = leftCodeObj->result;
				std::string rightRes = rightCodeObj->result;

				//Create temporary
				std::string tempStr = "!T"+std::to_string((long long)tempReg);	
				//std::string tempStr = "!T"+s;
				tempReg++;
		
				std::string MyInstrucStr;
				std::string newLabel;
				if (currCtrlStruc == "while_start"){
					//std::cout<<"Okay I have a while_start"<<std::endl;
					newLabel = getNewLabel("while_end");
					whileEndLabelVect.insert(whileEndLabelVect.begin(),newLabel);
				}		
				else if (currCtrlStruc == "else"){
					newLabel = getNewLabel("else");
					elseLabelVect.insert(elseLabelVect.begin(),newLabel);
				}
				//std::cout<<newLabel<<std::endl;

				//Create Instruction
				if (leftCodeObj->type == "int"){
					MyInstrucStr = ";GEI "+leftRes+" "+rightRes+" "+newLabel;	
				}
		
				else if (leftCodeObj->type == "float"){
					MyInstrucStr = ";GEF "+leftRes+" "+rightRes+" "+newLabel;
				}
				//std::cout<<MyInstrucStr<<std::endl;


				std::vector<std::string> InstrucVector;

				std::vector<std::string> leftInst = leftCodeObj->instruction;
				std::vector<std::string> rightInst = rightCodeObj->instruction;

				if (!leftInst.empty()){
					InstrucVector.insert(InstrucVector.end(), leftInst.begin(), leftInst.end());
				
				}

				if (!rightInst.empty()){
					InstrucVector.insert(InstrucVector.end(), rightInst.begin(), rightInst.end());
				}
			
				InstrucVector.push_back(MyInstrucStr);	
				//VectorTable::completeIRvect.push_back(MyInstrucStr);
	
				std::string type = leftCodeObj->type;
			
				CodeObject* co = new CodeObject(tempStr,InstrucVector,type);

				return co;
			}
			if (node->compOp == "<="){
				std::string leftRes = leftCodeObj->result;
				std::string rightRes = rightCodeObj->result;

				//Create temporary
				std::string tempStr = "!T"+std::to_string((long long)tempReg);	
				//std::string tempStr = "!T"+s;
				tempReg++;
		
				std::string MyInstrucStr;
				std::string newLabel;
				if (currCtrlStruc == "while_start"){
					//std::cout<<"Okay I have a while_start"<<std::endl;
					newLabel = getNewLabel("while_end");
					whileEndLabelVect.insert(whileEndLabelVect.begin(),newLabel);
				}		
				else if (currCtrlStruc == "else"){
					newLabel = getNewLabel("else");
					elseLabelVect.insert(elseLabelVect.begin(),newLabel);
				}
				//std::cout<<newLabel<<std::endl;

				//Create Instruction
				if (leftCodeObj->type == "int"){
					MyInstrucStr = ";GTI "+leftRes+" "+rightRes+" "+newLabel;	
				}
		
				else if (leftCodeObj->type == "float"){
					MyInstrucStr = ";GTF "+leftRes+" "+rightRes+" "+newLabel;
				}
				//std::cout<<MyInstrucStr<<std::endl;


				std::vector<std::string> InstrucVector;

				std::vector<std::string> leftInst = leftCodeObj->instruction;
				std::vector<std::string> rightInst = rightCodeObj->instruction;

				if (!leftInst.empty()){
					InstrucVector.insert(InstrucVector.end(), leftInst.begin(), leftInst.end());
				
				}

				if (!rightInst.empty()){
					InstrucVector.insert(InstrucVector.end(), rightInst.begin(), rightInst.end());
				}
			
				InstrucVector.push_back(MyInstrucStr);	
				//VectorTable::completeIRvect.push_back(MyInstrucStr);
	
				std::string type = leftCodeObj->type;
			
				CodeObject* co = new CodeObject(tempStr,InstrucVector,type);

				return co;
			}
			if (node->compOp == "!="){
				std::string leftRes = leftCodeObj->result;
				std::string rightRes = rightCodeObj->result;
				//std::cout<<"Found a not equal to "<<std::endl;
				//Create temporary
				std::string tempStr = "!T"+std::to_string((long long)tempReg);	
				//std::string tempStr = "!T"+s;
				tempReg++;
		
				std::string MyInstrucStr;
				std::string newLabel;
				if (currCtrlStruc == "while_start"){
					//std::cout<<"Okay I have a while_start"<<std::endl;
					newLabel = getNewLabel("while_end");
					whileEndLabelVect.insert(whileEndLabelVect.begin(),newLabel);
				}		
				else if (currCtrlStruc == "else"){
					newLabel = getNewLabel("else");
					elseLabelVect.insert(elseLabelVect.begin(),newLabel);
				}
				//std::cout<<newLabel<<std::endl;

				//Create Instruction
				if (leftCodeObj->type == "int"){
					MyInstrucStr = ";EQI "+leftRes+" "+rightRes+" "+newLabel;	
				}
		
				else if (leftCodeObj->type == "float"){
					MyInstrucStr = ";EQF "+leftRes+" "+rightRes+" "+newLabel;
				}
				//std::cout<<MyInstrucStr<<std::endl;


				std::vector<std::string> InstrucVector;

				std::vector<std::string> leftInst = leftCodeObj->instruction;
				std::vector<std::string> rightInst = rightCodeObj->instruction;

				if (!leftInst.empty()){
					InstrucVector.insert(InstrucVector.end(), leftInst.begin(), leftInst.end());
				
				}

				if (!rightInst.empty()){
					InstrucVector.insert(InstrucVector.end(), rightInst.begin(), rightInst.end());
				}
			
				InstrucVector.push_back(MyInstrucStr);	
				//VectorTable::completeIRvect.push_back(MyInstrucStr);
	
				std::string type = leftCodeObj->type;
			
				CodeObject* co = new CodeObject(tempStr,InstrucVector,type);

				return co;
			}
			if (node->compOp == "="){
				std::string leftRes = leftCodeObj->result;
				std::string rightRes = rightCodeObj->result;
				//std::cout<<"Found an equal to "<<std::endl;
				//Create temporary
				std::string tempStr = "!T"+std::to_string((long long)tempReg);	
				//std::string tempStr = "!T"+s;
				tempReg++;
		
				std::string MyInstrucStr;
				std::string newLabel;
				if (currCtrlStruc == "while_start"){
					//std::cout<<"Okay I have a while_start"<<std::endl;
					newLabel = getNewLabel("while_end");
					whileEndLabelVect.insert(whileEndLabelVect.begin(),newLabel);
				}		
				else if (currCtrlStruc == "else"){
					newLabel = getNewLabel("else");
					elseLabelVect.insert(elseLabelVect.begin(),newLabel);
				}
				//std::cout<<newLabel<<std::endl;

				//Create Instruction
				if (leftCodeObj->type == "int"){
					MyInstrucStr = ";NEI "+leftRes+" "+rightRes+" "+newLabel;	
				}
		
				else if (leftCodeObj->type == "float"){
					MyInstrucStr = ";NEF "+leftRes+" "+rightRes+" "+newLabel;
				}
				//std::cout<<MyInstrucStr<<std::endl;


				std::vector<std::string> InstrucVector;

				std::vector<std::string> leftInst = leftCodeObj->instruction;
				std::vector<std::string> rightInst = rightCodeObj->instruction;

				if (!leftInst.empty()){
					InstrucVector.insert(InstrucVector.end(), leftInst.begin(), leftInst.end());
				
				}

				if (!rightInst.empty()){
					InstrucVector.insert(InstrucVector.end(), rightInst.begin(), rightInst.end());
				}
			
				InstrucVector.push_back(MyInstrucStr);	
				//VectorTable::completeIRvect.push_back(MyInstrucStr);
	
				std::string type = leftCodeObj->type;
			
				CodeObject* co = new CodeObject(tempStr,InstrucVector,type);

				return co;
			}

		}

		//bool
		if (node->compBoolType != "\0"){ 
			
		}


		//**********Conditional operators check complete******************


		if (node->tokType == 2){
			//std::cout<<"tokType 2"<<std::endl;
			//CodeObject* co = new CodeObject(node->token,"int");  ///CHANGED FOR STEP 6
			int off = node->symb->symOffset;
			std::stringstream ss;
			ss << off;
			std::string strOff(ss.str());
			strOff = "$"+strOff;
				
			//std::cout<<"Left child for token "<<node->token<<" yes or no: "<<((node->leftChild) == NULL)<<std::endl;
			if (storeTemps == 1 && toStore == 1){
				tempVect.push_back(strOff);
			}

			CodeObject* co = new CodeObject(strOff,"int"); 
			//PrintIR::IRvector.push_back(co);
			return co;
		}
		if (node->tokType == 3){
			//std::cout<<"tokType 3"<<std::endl;
			//CodeObject* co = new CodeObject(node->token,"float");  ///CHANGED FOR STEP 6

			int off = node->symb->symOffset;
			std::stringstream ss;
			ss << off;
			std::string strOff(ss.str());
			strOff = "$"+strOff;
			//std::cout<<"Right child yes or no: "<<(node->rightChild->token)<<std::endl;
			if (storeTemps == 1 && toStore == 1){
				tempVect.push_back(strOff);
			}

			CodeObject* co = new CodeObject(strOff,"float");  ///CHANGED FOR STEP 6
			//PrintIR::IRvector.push_back(co);
			return co;	
		}


		if (node->tokType == 1) {//ArithNode
			//std::cout<<"Type Arithnode found"<<std::endl;
			std::string leftRes = leftCodeObj->result;
			std::string rightRes = rightCodeObj->result;


			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			if (storeTemps == 1){
				tempVect.push_back(tempStr);
			}	
			std::string MyInstrucStr;
		
			//Create Instruction
			if (leftCodeObj->type == "int"){

				if (node->token == "+"){		
					//std::string MyInstrucStr = ";ADDI "+leftRes+" "+rightRes+" "+tempStr; 
					MyInstrucStr = ";ADDI "+leftRes+" "+rightRes+" "+tempStr;
				}
				else if (node->token == "-"){
					//std::string MyInstrucStr = ";SUBI "+leftRes+" "+rightRes+" "+tempStr;
					MyInstrucStr = ";SUBI "+leftRes+" "+rightRes+" "+tempStr; 
				}
				else if (node->token == "*"){
					//std::string MyInstrucStr = ";MULI "+leftRes+" "+rightRes+" "+tempStr; 
					MyInstrucStr = ";MULI "+leftRes+" "+rightRes+" "+tempStr;
				}
				else if (node->token == "/"){
					//std::string MyInstrucStr = ";DIVI "+leftRes+" "+rightRes+" "+tempStr;
					MyInstrucStr = ";DIVI "+leftRes+" "+rightRes+" "+tempStr; 
				}
			}
		
			else if (leftCodeObj->type == "float"){

				if (node->token == "+"){		
					//std::string MyInstrucStr = ";ADDF "+leftRes+" "+rightRes+" "+tempStr;
					MyInstrucStr = ";ADDF "+leftRes+" "+rightRes+" "+tempStr; 
				}
				else if (node->token == "-"){
					//std::string MyInstrucStr = ";SUBF "+leftRes+" "+rightRes+" "+tempStr; 
					MyInstrucStr = ";SUBF "+leftRes+" "+rightRes+" "+tempStr; 
				}
				else if (node->token == "*"){
					//std::string MyInstrucStr = ";MULF "+leftRes+" "+rightRes+" "+tempStr; 
					MyInstrucStr = ";MULF "+leftRes+" "+rightRes+" "+tempStr; 
				}
				else if (node->token == "/"){
					//std::string MyInstrucStr = ";DIVF "+leftRes+" "+rightRes+" "+tempStr; 
					MyInstrucStr = ";DIVF "+leftRes+" "+rightRes+" "+tempStr; 
				}
			}
		


			std::vector<std::string> InstrucVector;

			std::vector<std::string> leftInst = leftCodeObj->instruction;
			std::vector<std::string> rightInst = rightCodeObj->instruction;

			if (!leftInst.empty()){
				InstrucVector.insert(InstrucVector.end(), leftInst.begin(), leftInst.end());
				
			}

			if (!rightInst.empty()){
				InstrucVector.insert(InstrucVector.end(), rightInst.begin(), rightInst.end());
			}
			
			InstrucVector.push_back(MyInstrucStr);	
			//VectorTable::completeIRvect.push_back(MyInstrucStr);
	
			std::string type = leftCodeObj->type;
			
			CodeObject* co = new CodeObject(tempStr,InstrucVector,type);

			return co;
		}
		
		if (node->tokType == 5){
			//std::cout<<"I am token:    "<<node->token;
			//std::cout<<"INT lit found"<<std::endl;
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			tempReg++;
			/*
			if (storeTemps == 1){
				tempVect.push_back(tempStr);
			}*/
			//PrintIR::IRvector.push_back(co);

			std::string storeStr = ";STOREI "+node->token+" "+tempStr;
			std::vector<std::string> InstrucVector;
			InstrucVector.push_back(storeStr);	
			//::completeIRvect.push_back(storeStr);
			CodeObject* co = new CodeObject(tempStr,InstrucVector,"int");
			return co;	
		}
		
		if (node->tokType == 6){
			//std::cout<<"FLOAT lit found"<<std::endl;
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			tempReg++;
			/*
			if (storeTemps == 1){
				tempVect.push_back(tempStr);
			}*/

			//PrintIR::IRvector.push_back(co);
			//std::cout<<"FLOAT lit found"<<std::endl;
			std::string storeStr = ";STOREF "+node->token+" "+tempStr;
			//std::cout<<storeStr<<std::endl;
			std::vector<std::string> InstrucVector;
			InstrucVector.push_back(storeStr);	
			//VectorTable::completeIRvect.push_back(storeStr);
			CodeObject* co = new CodeObject(tempStr,InstrucVector,"float");
			return co;		
		}
		

	
	}	
	

}

void VectorTable::printIRcode(std::vector<std::string> RootCodeObject){

	int len = RootCodeObject.size();
	for (int i = 0; i < len; i++){
		//VectorTable::completeIRvect.push_back(RootCodeObject[i]);
		//std::cout<<RootCodeObject[i]<<std::endl; //------------------->>>>>> PRINTING IR CODE ORIGINAL
		IRcodeVector.push_back(RootCodeObject[i]);  
	}

}

CodeObject* VectorTable::writeCodeObj(ASTNode* node){
	
	//std::cout<<"Found a write"<<std::endl;
	//std::cout<<node->tokType<<std::endl;

	if (node->tokType == 4){
	//else{	
		//std::cout<<"Found a string write"<<std::endl;
		std::vector<std::string> instVect;
		std::string IRstr = ";WRITES "+node->token;
		//std::cout<<IRstr<<std::endl;
		instVect.push_back(IRstr);
		//VectorTable::completeIRvect.push_back(IRstr);
		CodeObject* co = new CodeObject(node->token,instVect,"string");
		return co;
	}



	if ((node->symb->var_type) == 275){
		//std::cout<<"Toktype 2"<<std::endl;
		std::vector<std::string> instVect;
		//std::string IRstr = ";WRITEI "+node->token;  ////COMMENTED FOR STEP 6
		int off = node->symb->symOffset;
		std::stringstream ss;
		ss << off;
		std::string strOff(ss.str());
		std::string IRstr = ";WRITEI $"+strOff;	
		//std::cout<<IRstr<<std::endl;
		instVect.push_back(IRstr);
		//VectorTable::completeIRvect.push_back(IRstr);
		CodeObject* co = new CodeObject(node->token,instVect,"int");
		return co;
				
	}
	if ((node->symb->var_type) == 278){
		
		//std::cout<<"Toktype 3"<<std::endl;
		std::vector<std::string> instVect;
		//std::string IRstr = ";WRITEF "+node->token; ////COMMENTED FOR STEP 6
		int off = node->symb->symOffset;
		std::stringstream ss;
		ss << off;
		std::string strOff(ss.str());
		std::string IRstr = ";WRITEF $"+strOff;
		//std::cout<<IRstr<<std::endl;
		instVect.push_back(IRstr);
		//VectorTable::completeIRvect.push_back(IRstr);
		CodeObject* co = new CodeObject(node->token,instVect,"float");
		return co;
	}

	
}


CodeObject* VectorTable::readCodeObj(ASTNode* node){

	if ((node->symb->var_type) == 275){
		//std::cout<<"Toktype 2"<<std::endl;
		std::vector<std::string> instVect;
		//std::string IRstr = ";READI "+node->token; ////COMMENTED FOR STEP 6
		int off = node->symb->symOffset;
		std::stringstream ss;
		ss << off;
		std::string strOff(ss.str());
		std::string IRstr = ";READI $"+strOff;
		//std::cout<<IRstr<<std::endl;
		instVect.push_back(IRstr);
		//VectorTable::completeIRvect.push_back(IRstr);
		CodeObject* co = new CodeObject(node->token,instVect,"int");
		return co;
				
	}
	if ((node->symb->var_type) == 278){
		
		//std::cout<<"Toktype 2"<<std::endl;
		std::vector<std::string> instVect;
		//std::string IRstr = ";READF "+node->token;////COMMENTED FOR STEP 6
		int off = node->symb->symOffset;
		std::stringstream ss;
		ss << off;
		std::string strOff(ss.str());
		std::string IRstr = ";READF $"+strOff;
		//std::cout<<IRstr<<std::endl;
		instVect.push_back(IRstr);
		//VectorTable::completeIRvect.push_back(IRstr);
		CodeObject* co = new CodeObject(node->token,instVect,"float");
		return co;
	}

}






std::vector<CodeObject*> VectorTable::StackIteratorforIR(std::vector<CodeObject*> coVect, std::string function, SymbolTable* symTab){
	

	//VectorTable* vectTable;
	//std::cout<<"IN stack iterator"<<std::endl;
	//std::cout<<(stmt_listPtrVect)->size()<<std::endl;
	//std::cout<<"Should have printed size"<<std::endl;
	//std::vector<ASTNode*>vectToIterate = *stmt_listPtrVect;
	for(int i = 0; i < stmt_listPtrVect->size(); i++) {
		//std::cout<<"For loop"<<std::endl;
		//std::cout<<"Call type: "<<(*stmt_listPtrVect)[i]->callType<<std::endl;
		if ((*stmt_listPtrVect)[i]->callType == "Return"){

			//Found a return
			//std::cout<<"Found a return"<<std::endl;
			//Make new temporary, print 2 store statements and unlink and ret
			//std::cout<<"return expr: "<<(*stmt_listPtrVect)[i]->returnExpr->token<<std::endl;
			//std::string storeStr1;

			//std::cout<<"Local args: "<<(symTab->ordered_table).size()<<std::endl;
			for (int k = 0; k<(symTab->ordered_table).size(); k++){
				if ((symTab->ordered_table)[k]->symOffset > 0){
					numParams++;
				}
			}

			if (function == "main"){ //////////if return is in main, I don't have to do anything ??
				IRcodeVector.push_back(";UNLINK");
				IRcodeVector.push_back(";RET");
			}

			else{
				if ((*stmt_listPtrVect)[i]->returnExpr->tokType == 5){
					//std::cout<<"Found a return literal"<<std::endl;	
					std::string tempStr = "!T"+std::to_string((long long)tempReg);	
					tempReg++;
					std::string storeStr1 = ";STOREI "+(*stmt_listPtrVect)[i]->returnExpr->token+" "+tempStr;
					IRcodeVector.push_back(storeStr1);
					formula = 6 + numParams;
					//std::stringstream ss;
					//std::cout<<"Formula: "<<formula<<std::endl;
					std::stringstream ss;
					//ss.str("");
					ss << formula;
					std::string strFormula(ss.str());	
					strFormula = "$"+strFormula;

					std::string storeStr2 = ";STOREI "+tempStr+" "+strFormula/*(*stmt_listPtrVect)[i]->assignLHS "Formula answer that uses no. of registers"*/;
					formula = 0;
					numParams = 0;

					IRcodeVector.push_back(storeStr2);
					IRcodeVector.push_back(";UNLINK");
					IRcodeVector.push_back(";RET");
					//std::cout<<"Done with the return"<<std::endl;
					CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->returnExpr);
					//std::cout<<"Created rootCo for return"<<std::endl;
					if(!rootCo->instruction.empty()){
						coVect.push_back(rootCo);
					}

				}

				else if ((*stmt_listPtrVect)[i]->returnExpr->tokType == 6){ //////float literal
					//std::cout<<"Found a return literal"<<std::endl;	
					std::string tempStr = "!T"+std::to_string((long long)tempReg);	
					tempReg++;
					std::string storeStr1 = ";STOREF "+(*stmt_listPtrVect)[i]->returnExpr->token+" "+tempStr;
					IRcodeVector.push_back(storeStr1);
					formula = 6 + numParams;
					//std::stringstream ss;
					//std::cout<<"Formula: "<<formula<<std::endl;
					std::stringstream ss;
					//ss.str("");
					ss << formula;
					std::string strFormula(ss.str());	
					strFormula = "$"+strFormula;

					std::string storeStr2 = ";STOREF "+tempStr+" "+strFormula/*(*stmt_listPtrVect)[i]->assignLHS "Formula answer that uses no. of registers"*/;
					formula = 0;
					numParams = 0;

					IRcodeVector.push_back(storeStr2);
					IRcodeVector.push_back(";UNLINK");
					IRcodeVector.push_back(";RET");
					//std::cout<<"Done with the return"<<std::endl;
					CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->returnExpr);
					//std::cout<<"Created rootCo for return"<<std::endl;
					if(!rootCo->instruction.empty()){
						coVect.push_back(rootCo);
					}

				}

				else if ((*stmt_listPtrVect)[i]->returnExpr->token == "-" || (*stmt_listPtrVect)[i]->returnExpr->token == "+" || (*stmt_listPtrVect)[i]->returnExpr->token == "*" || (*stmt_listPtrVect)[i]->returnExpr->token == "/" ){
					//std::cout<<"Found an operator"<<std::endl;	
					CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->returnExpr);
					//std::cout<<"Done making rootco"<<std::endl;
					std::string storeStr;
					//std::cout<<stmtVect[i]->symb->var_type<<std::endl;
					formula = 6 + numParams;
					//std::stringstream ss;
					//std::cout<<"Formula: "<<formula<<std::endl;
					std::stringstream ss;
					//ss.str("");
					ss << formula;
					std::string strFormula(ss.str());	
					strFormula = "$"+strFormula;
					spclFormula = strFormula;		
					spclStore = 1;

					if (rootCo->type == "int"){
						//std::cout<<"Trying to print store int"<<std::endl;
						//std::cout<<"node lhs: "<<node->assignLHS<<std::endl;
						//storeStr = ";STOREI "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
						if ((rootCo->result).find("!") != std::string::npos) {
							//std::cout<<"In if part"<<std::endl;
							std::string tempStr = "!T"+std::to_string((long long)tempReg);	
							tempReg++;
							//storeStr = ";STOREI "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
							storeStr = ";STOREI "+rootCo->result+" "+strFormula;
							rootCo->instruction.push_back(storeStr);	
						} 
						/*
						else{

							//DOUBLE CHECK PLEASE
							std::cout<<"In else part"<<std::endl;
							std::string tempStr = "!T"+std::to_string((long long)tempReg);	
							tempReg++;
							if (storeTemps == 1){
								tempVect.push_back(tempStr);
							}
							std::string storeStr1 = ";STOREI "+rootCo->result+" "+tempStr;
							std::string storeStr2 = ";STOREI "+tempStr+" "+(*stmt_listPtrVect)[i]->assignLHS;
							rootCo->instruction.push_back(storeStr1);
							rootCo->instruction.push_back(storeStr2);		
						}*/
					}
					else if (rootCo->type == "float"){
						//std::cout<<"Trying to print store float"<<std::endl;

						if ((rootCo->result).find("!") != std::string::npos) {
							//std::cout<<"In if part"<<std::endl;
							std::string tempStr = "!T"+std::to_string((long long)tempReg);	
							tempReg++;
							storeStr = ";STOREF "+rootCo->result+" "+strFormula;
							rootCo->instruction.push_back(storeStr);	
						} 
						/*
						else{
							std::cout<<"In else part"<<std::endl;
							std::string tempStr = "!T"+std::to_string((long long)tempReg);	
							tempReg++;
							if (storeTemps == 1){
								tempVect.push_back(tempStr);
							}
							std::string storeStr1 = ";STOREF "+rootCo->result+" "+tempStr;
							std::string storeStr2 = ";STOREF "+tempStr+" "+(*stmt_listPtrVect)[i]->assignLHS;
							rootCo->instruction.push_back(storeStr1);
							rootCo->instruction.push_back(storeStr2);		
						}*/

						//storeStr = ";STOREF "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
						//std::cout<<"StoreStr is:"<<storeStr<<std::endl;
					}
			
					//std::cout<<"Done with the if/else part"<<std::endl;
			
					if(!rootCo->instruction.empty()){
						coVect.push_back(rootCo);
						//std::cout<<"Printing covect element in arith "<<coVect[coVect.size()-1]->result<<std::endl;		
						//std::cout<<"Root co instruction is NOT empty"<<std::endl;		
						VectorTable::printIRcode(rootCo->instruction);	
					
					}					
	

				}

				
				else{   //toktype is 2 ----variable instead of literal
					//std::cout<<"Found a return variable"<<std::endl;	
					std::string tempStr = "!T"+std::to_string((long long)tempReg);	
					tempReg++;
					//Need to get the return expr value
					//std::string storeStr1 = ";STOREI "+(*stmt_listPtrVect)[i]->returnExpr->token+" "+tempStr;

					int off = symTab->lhsOffset((*stmt_listPtrVect)[i]->returnExpr->token, function);
					//std::cout<<"returned offset: "<<off<<std::endl;
					//std::cout<<"STOREI LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
					std::stringstream ss;
					ss << off;
					std::string strOff(ss.str());	
					strOff = "$"+strOff;

					//std::cout<<"variable type: "<<(*stmt_listPtrVect)[i]->returnExpr->symb->var_type<<std::endl;
					
					if ((*stmt_listPtrVect)[i]->returnExpr->symb->var_type == 275){

						std::string storeStr1 = ";STOREI "+strOff+" "+tempStr;

						IRcodeVector.push_back(storeStr1);
				
						formula = 6 + numParams;
						//std::stringstream ss;
						//std::cout<<"Formula: "<<formula<<std::endl;
						ss.str("");
						ss << formula;
						std::string strFormula(ss.str());	
						strFormula = "$"+strFormula;

						std::string storeStr2 = ";STOREI "+tempStr+" "+strFormula/*(*stmt_listPtrVect)[i]->assignLHS "Formula answer that uses no. of registers"*/;
						formula = 0;
						numParams = 0;
						IRcodeVector.push_back(storeStr2);
						IRcodeVector.push_back(";UNLINK");
						IRcodeVector.push_back(";RET");
						//std::cout<<"Done with the return"<<std::endl;
						CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->returnExpr);
						//std::cout<<"Created rootCo for return"<<std::endl;
						if(!rootCo->instruction.empty()){
							coVect.push_back(rootCo);
						}
					}
					else if ((*stmt_listPtrVect)[i]->returnExpr->symb->var_type == 278){

						std::string storeStr1 = ";STOREF "+strOff+" "+tempStr;

						IRcodeVector.push_back(storeStr1);
				
						formula = 6 + numParams;
						//std::stringstream ss;
						//std::cout<<"Formula: "<<formula<<std::endl;
						ss.str("");
						ss << formula;
						std::string strFormula(ss.str());	
						strFormula = "$"+strFormula;

						std::string storeStr2 = ";STOREF "+tempStr+" "+strFormula/*(*stmt_listPtrVect)[i]->assignLHS "Formula answer that uses no. of registers"*/;
						formula = 0;
						numParams = 0;
						IRcodeVector.push_back(storeStr2);
						IRcodeVector.push_back(";UNLINK");
						IRcodeVector.push_back(";RET");
						//std::cout<<"Done with the return"<<std::endl;
						CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->returnExpr);
						//std::cout<<"Created rootCo for return"<<std::endl;
						if(!rootCo->instruction.empty()){
							coVect.push_back(rootCo);
						}


					}
					/*  >>>>>>>>>>>>Commented because I split it above into int or float instructions
					std::string storeStr1 = ";STOREI "+strOff+" "+tempStr;

					IRcodeVector.push_back(storeStr1);
				
					formula = 6 + numParams;
					//std::stringstream ss;
					//std::cout<<"Formula: "<<formula<<std::endl;
					ss.str("");
					ss << formula;
					std::string strFormula(ss.str());	
					strFormula = "$"+strFormula;

					std::string storeStr2 = ";STOREI "+tempStr+" "+strFormula;
					formula = 0;
					numParams = 0;
					IRcodeVector.push_back(storeStr2);
					IRcodeVector.push_back(";UNLINK");
					IRcodeVector.push_back(";RET");
					//std::cout<<"Done with the return"<<std::endl;
					CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->returnExpr);
					//std::cout<<"Created rootCo for return"<<std::endl;
					if(!rootCo->instruction.empty()){
						coVect.push_back(rootCo);
					}
					*/
				}	

			}

			/*
			std::cout<<"Local args: "<<(symTab->ordered_table).size()<<std::endl;
			for (int k = 0; k<(symTab->ordered_table).size(); k++){
				if ((symTab->ordered_table)[k]->symOffset < 0){
					std::cout<<(symTab->ordered_table)[k]->var_name<<std::endl;
				}
			}*/
			//std::string storeStr2 = ";STOREI "+tempStr+" "+/*(*stmt_listPtrVect)[i]->assignLHS "Formula answer that uses no. of registers"*/;


			//////////////////////////////////////////COMMENTED BECAUSE SEGFAULT? 
			/*
			IRcodeVector.push_back(storeStr1);
			//IRcodeVector.push_back(storeStr2);
			IRcodeVector.push_back(";UNLINK");
			IRcodeVector.push_back(";RET");
			//std::cout<<"Done with the return"<<std::endl;
			CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->returnExpr);
			//std::cout<<"Created rootCo for return"<<std::endl;
			if(!rootCo->instruction.empty()){
				coVect.push_back(rootCo);
			}*/
			//////////////////////////////////////////COMMENTED BECAUSE SEGFAULT?

			//std::cout<<"Pushed rootCo into coVect"<<std::endl;
		}	


		else if ((*stmt_listPtrVect)[i]->callType == "CallExpr"){
			//std::cout<<"Found a call expression"<<std::endl;

			VectorTable* callExpVect = new VectorTable("callETable",vectParent);
			storeTemps = 1;
			//std::cout<<"before calling stack iterator again, in callexpr"<<std::endl;
			if ((*stmt_listPtrVect)[i]->ExprVect != NULL){
				//std::cout<<"call expr vect is not null"<<std::endl;
				callExpVect->stmt_listPtrVect = (*stmt_listPtrVect)[i]->ExprVect;
				//std::cout<<"Calling Stack iterator again"<<std::endl;
				coVect = (callExpVect)->StackIteratorforIR(coVect,function,symTab);
				//std::cout<<"Done with Stack iterator again"<<std::endl;
			}

			IRcodeVector.push_back(";PUSH");
			IRcodeVector.push_back(";PUSHREGS");

			//std::cout<<"tempVect size: "<<tempVect.size()<<std::endl;

			for (int j = 0; j<tempVect.size(); j++){
				//std::cout<<"in push args loop"<<std::endl;
				std::string pushStr = ";PUSH " + tempVect[j];				
				IRcodeVector.push_back(pushStr);
			}
			storeTemps = 0;
			tempVect.clear();
	
			std::string jmpStr = ";JSR FUNC_" + *((*stmt_listPtrVect)[i]->ExprID);
			IRcodeVector.push_back(jmpStr);

			//std::cout<<"exprVect size: "<<(*(*stmt_listPtrVect)[i]->ExprVect).size()<<std::endl;
			for(int len = 0; len < (*(*stmt_listPtrVect)[i]->ExprVect).size(); len++ ){
				IRcodeVector.push_back(";POP");
			}	
			IRcodeVector.push_back(";POPREGS");
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			tempReg++;
			std::string popStr = ";POP "+tempStr;
			IRcodeVector.push_back(popStr);				
		}	



		else if ((*stmt_listPtrVect)[i]->IOType == "WRITE"){	
			//std::cout<<"Found a write"<<std::endl;
			for (int j = 0; j < ((*stmt_listPtrVect)[i]->IOIdVect).size(); j++){

				CodeObject* rootCo = VectorTable::writeCodeObj((*stmt_listPtrVect)[i]->IOIdVect[j]);

				if(!rootCo->instruction.empty()){
					//std::cout<<"Root co instruction is NOT empty"<<std::endl;		
					coVect.push_back(rootCo);
					//std::cout<<"Printing covect element in write "<<coVect[coVect.size()-1]->result<<std::endl;		
					VectorTable::printIRcode(rootCo->instruction);
						
				
				}
			}

		}
		else if ((*stmt_listPtrVect)[i]->IOType == "READ"){
			//std::cout<<"Found a read"<<std::endl;
			for (int j = 0; j < ((*stmt_listPtrVect)[i]->IOIdVect).size(); j++){
				CodeObject* rootCo = VectorTable::readCodeObj((*stmt_listPtrVect)[i]->IOIdVect[j]);

				if(!rootCo->instruction.empty()){
					//std::cout<<"Root co instruction is NOT empty"<<std::endl;	
					coVect.push_back(rootCo);	
					//std::cout<<"Printing covect element in read "<<coVect[coVect.size()-1]->result<<std::endl;		
					VectorTable::printIRcode(rootCo->instruction);
				}		
			}
		}
		

		




		//*******************CONTROL STRUCTURE PART ADDITION***************************
		//Plan for if-else (similar for while): Add checks for if-else and while, and statements that first check the condition expression, then execute sttments in thenStmtVect(call StackIterator func for every sttmnt in thnStmtVect), then execute sttments in elseStmtVect(call StackIterator func for every sttmnt in elseStmtVect), with appropriate jump and label statements. 

		
		else if ((*stmt_listPtrVect)[i]->If_ElseType != "\0"){
			//std::cout<<"Okay I found an if else structure"<<std::endl;
			currCtrlStruc = "else";
			

			std::string op = (*stmt_listPtrVect)[i]->condExpr->compOp;

	
			if (op != "\0"){ //has some comparison operator
				//std::cout<<"has some comparison operator"<<std::endl;		

				//Printing condition of if 
				//std::cout<<"Printing condition of if"<<std::endl;
				CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->condExpr);  //create a code object for the root operator in condExpr tree
		
				std::string storeStr;
				
				if(!rootCo->instruction.empty()){
					coVect.push_back(rootCo);
					//std::cout<<"Printing covect element in arith "<<coVect[coVect.size()-1]->result<<std::endl;		
					//std::cout<<"Root co instruction is NOT empty"<<std::endl;		
					VectorTable::printIRcode(rootCo->instruction);	
					
				}

						
				//Going through if statements
				//std::cout<<"Going through if statements"<<std::endl;
				//std::vector <ASTNode*>* PtrToVect = (*stmt_listPtrVect)[i]->WhileStmtVect;
				VectorTable* ifVect = new VectorTable("ifTable",vectParent);
				if ((*stmt_listPtrVect)[i]->ThenStmtVect != NULL){
					//std::cout<<"Then stmt vect is not null"<<std::endl;
					ifVect->stmt_listPtrVect = (*stmt_listPtrVect)[i]->ThenStmtVect;
					//std::cout<<"Calling Stack iterator again"<<std::endl;
					coVect = (ifVect)->StackIteratorforIR(coVect,function,symTab);
					//std::cout<<"Done with Stack iterator again"<<std::endl;
				}
				
				//Jump to END_IF
				//std::cout<<"Jump to END_IF"<<std::endl;
				std::string newLabel = getNewLabel("end_if_else");
				endIfLabelVect.insert(endIfLabelVect.begin(),newLabel);
				//currCtrlStruc = "while_start";
				std::string printStr;
				printStr = printStr + ";JUMP "+newLabel;
				//std::cout<<";JUMP "<<newLabel<<std::endl;
				//std::cout<<printStr<<std::endl;	//------------------->>>>>> PRINTING IR CODE ORIGINAL			
				IRcodeVector.push_back(printStr);


				//LABEL for else block
				//std::cout<<"LABEL for else block"<<std::endl;
				std::string elseLabelStr;
				elseLabelStr = elseLabelStr + ";LABEL " + elseLabelVect[0];
				//std::cout<<elseLabelStr<<std::endl; 	//------------------->>>>>> PRINTING IR CODE ORIGINAL
				IRcodeVector.push_back(elseLabelStr); 
				elseLabelVect.erase(elseLabelVect.begin());

				//Go through else statement vector
				//std::cout<<"Go through else statement vector"<<std::endl;
				//std::cout<<"Trying to print else statements"<<std::endl;
				VectorTable* elseVect = new VectorTable("elseTable",vectParent);
				if ((*stmt_listPtrVect)[i]->ElseStmtVect != NULL){
					//std::cout<<"Going through stack iterator for else part"<<std::endl;
					elseVect->stmt_listPtrVect = (*stmt_listPtrVect)[i]->ElseStmtVect;
					coVect = (elseVect)->StackIteratorforIR(coVect,function,symTab);
					//std::cout<<"Done with else stack iterator part"<<std::endl;
				}
				//std::cout<<"Printed else statements"<<std::endl;
				//Label end_if
				//std::cout<<"Trying to print end if label"<<std::endl;
				//std::cout<<"endIfLabelVect[0]"<<endIfLabelVect[0]<<std::endl; 
				std::string endIfLabelStr;
				endIfLabelStr = endIfLabelStr + ";LABEL " + endIfLabelVect[0];
				//std::cout<<endIfLabelStr<<std::endl;  //------------------->>>>>> PRINTING IR CODE ORIGINAL
				IRcodeVector.push_back(endIfLabelStr);
				endIfLabelVect.erase(endIfLabelVect.begin());
			
				
			}	
				

		}
		
		else if ((*stmt_listPtrVect)[i]->WhileType != "\0"){
			//std::cout<<"Okay I found a while structure"<<std::endl;
			std::string newLabel = getNewLabel("while_start");
			currCtrlStruc = "while_start";
			std::string printStr;
			printStr = printStr + ";LABEL " + newLabel;
			IRcodeVector.push_back(printStr);
			//std::cout<<";LABEL "<<newLabel<<std::endl;  //Label for while loop
			//std::cout<<printStr<<std::endl;  //Label for while loop   //------------------->>>>>> PRINTING IR CODE ORIGINAL
			/*
			std::string op = (*stmt_listPtrVect)[i]->compOp;
			std::cout<<"compOp is"<<(*stmt_listPtrVect)[i]->compOp<<std::endl;		
			std::cout<<"op is"<<op<<std::endl;	*/
			//std::cout<<"compOp is"<<(*stmt_listPtrVect)[i]->condExpr->compOp<<std::endl;		
			std::string op = (*stmt_listPtrVect)[i]->condExpr->compOp;

	
			if (op != "\0"){ //has some comparison operator
				//std::cout<<"has some comparison operator"<<std::endl;		

				//Printing condition of while loop
				CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->condExpr);  //create a code object for the root operator in condExpr tree
		
				std::string storeStr;
				
				if(!rootCo->instruction.empty()){
					coVect.push_back(rootCo);
					//std::cout<<"Printing covect element in arith "<<coVect[coVect.size()-1]->result<<std::endl;		
					//std::cout<<"Root co instruction is NOT empty"<<std::endl;		
					VectorTable::printIRcode(rootCo->instruction);	
					
				}

				//Going through while loop statements
				//std::vector <ASTNode*>* PtrToVect = (*stmt_listPtrVect)[i]->WhileStmtVect;
				VectorTable* whileVect = new VectorTable("whileTable",vectParent);
				whileVect->stmt_listPtrVect = (*stmt_listPtrVect)[i]->WhileStmtVect;
				coVect = (whileVect)->StackIteratorforIR(coVect,function,symTab);
				
		
				//Jump statement that goes to start of while
				std::string labelStr;
				labelStr = labelStr + ";JUMP " + newLabel;
				//std::cout<<labelStr<<std::endl;  //Label for while loop  //------------------->>>>>> PRINTING IR CODE ORIGINAL
				IRcodeVector.push_back(labelStr);

				//While end label, get first of while end vect and delete that
				std::string endLabelStr;
				endLabelStr = endLabelStr + ";LABEL " + whileEndLabelVect[0];
				//std::cout<<endLabelStr<<std::endl;	//------------------->>>>>> PRINTING IR CODE ORIGINAL
				IRcodeVector.push_back(endLabelStr); 
				whileEndLabelVect.erase(whileEndLabelVect.begin());
				

			}
			else{		//has a bool operator
				//std::cout<<"has some bool operator"<<std::endl;		
				std::string boolOp = (*stmt_listPtrVect)[i]->compBoolType;
			}
			

		}




	
		//Original ArithNode part, unchanged
		else{
			//std::cout<<"ArithNode"<<std::endl;
			//std::cout<<"LHS: "<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
			//std::cout<<"TOKEN: "<<(*stmt_listPtrVect)[i]->token<<std::endl;
			//ASTNode* rootNode = stmtVect[i]->assignRHS;


			if ((*stmt_listPtrVect)[i]->assignRHS == NULL){	
				//std::cout<<"Assign rhs is null"<<std::endl; ///////Arithmetic node from call expression, without an LHS value to assign the result to
				//std::cout<<"token: "<<(*stmt_listPtrVect)[i]->token<<std::endl;

				if ((*stmt_listPtrVect)[i]->token == "-" ||(*stmt_listPtrVect)[i]->token == "+" ||(*stmt_listPtrVect)[i]->token == "*"||(*stmt_listPtrVect)[i]->token == "/"){
					toStore = 0;
				}    
				else{
					toStore = 1;
				}

				CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]);
				//std::cout<<"Done making rootco"<<std::endl;
				std::string storeStr;
				//std::cout<<stmtVect[i]->symb->var_type<<std::endl;

			
				if (rootCo->type == "int"){
					//std::cout<<"Trying to print store int"<<std::endl;
					//std::cout<<"node lhs: "<<node->assignLHS<<std::endl;
					//storeStr = ";STOREI "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
					if ((rootCo->result).find("!") != std::string::npos) {
						//std::cout<<"In if part"<<std::endl;
						std::string tempStr = "!T"+std::to_string((long long)tempReg);	
						tempReg++;
						//storeStr = ";STOREI "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
						storeStr = ";STOREI "+rootCo->result+" "+tempStr;
						rootCo->instruction.push_back(storeStr);	
					} 
					/*
					else{

						//DOUBLE CHECK PLEASE
						std::cout<<"In else part"<<std::endl;
						std::string tempStr = "!T"+std::to_string((long long)tempReg);	
						tempReg++;
						if (storeTemps == 1){
							tempVect.push_back(tempStr);
						}
						std::string storeStr1 = ";STOREI "+rootCo->result+" "+tempStr;
						std::string storeStr2 = ";STOREI "+tempStr+" "+(*stmt_listPtrVect)[i]->assignLHS;
						rootCo->instruction.push_back(storeStr1);
						rootCo->instruction.push_back(storeStr2);		
					}*/
				}
				else if (rootCo->type == "float"){
					//std::cout<<"Trying to print store float"<<std::endl;

					if ((rootCo->result).find("!") != std::string::npos) {
						//std::cout<<"In if part"<<std::endl;
						std::string tempStr = "!T"+std::to_string((long long)tempReg);	
						tempReg++;
						storeStr = ";STOREF "+rootCo->result+" "+tempStr;
						rootCo->instruction.push_back(storeStr);	
					} 
					/*
					else{
						std::cout<<"In else part"<<std::endl;
						std::string tempStr = "!T"+std::to_string((long long)tempReg);	
						tempReg++;
						if (storeTemps == 1){
							tempVect.push_back(tempStr);
						}
						std::string storeStr1 = ";STOREF "+rootCo->result+" "+tempStr;
						std::string storeStr2 = ";STOREF "+tempStr+" "+(*stmt_listPtrVect)[i]->assignLHS;
						rootCo->instruction.push_back(storeStr1);
						rootCo->instruction.push_back(storeStr2);		
					}*/

					//storeStr = ";STOREF "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
					//std::cout<<"StoreStr is:"<<storeStr<<std::endl;
				}
			
				//std::cout<<"Done with the if/else part"<<std::endl;
			
				if(!rootCo->instruction.empty()){
					coVect.push_back(rootCo);
					//std::cout<<"Printing covect element in arith "<<coVect[coVect.size()-1]->result<<std::endl;		
					//std::cout<<"Root co instruction is NOT empty"<<std::endl;		
					VectorTable::printIRcode(rootCo->instruction);	
					
				}



			}


			else if ((*stmt_listPtrVect)[i]->assignRHS->callType == "CallExpr"){

				//std::cout<<"Found a call expression"<<std::endl;
				
				VectorTable* callExpVect = new VectorTable("callETable",vectParent);
				storeTemps = 1;
				//std::cout<<"before calling stack iterator again, in callexpr"<<std::endl;
				//std::cout<<"callexpr id: "<<*((*stmt_listPtrVect)[i]->assignRHS->ExprID)<<std::endl;
				if ((*stmt_listPtrVect)[i]->assignRHS->ExprVect != NULL){
					//numParams = (*(*stmt_listPtrVect)[i]->assignRHS->ExprVect).size();
					//formula = 6 + numParams;
					//std::cout<<"numParams: "<<numParams<<std::endl;
					//std::cout<<"call expr vect is not null"<<std::endl;
					callExpVect->stmt_listPtrVect = (*stmt_listPtrVect)[i]->assignRHS->ExprVect;
					//std::cout<<"Calling Stack iterator again"<<std::endl;
					coVect = (callExpVect)->StackIteratorforIR(coVect,function,symTab);
					//std::cout<<"Done with Stack iterator again"<<std::endl;
				}
				/*
				else{std::cout<<"call expr vect is null"<<std::endl;
				}*/

				IRcodeVector.push_back(";PUSH");
				IRcodeVector.push_back(";PUSHREGS");

				//std::cout<<"tempVect size: "<<tempVect.size()<<std::endl;

				for (int j = 0; j<tempVect.size(); j++){
					//std::cout<<"in push args loop"<<std::endl;
					std::string pushStr = ";PUSH " + tempVect[j];				
					IRcodeVector.push_back(pushStr);
				}
				storeTemps = 0;
				tempVect.clear();


				std::string jmpStr = ";JSR FUNC_" + *((*stmt_listPtrVect)[i]->assignRHS->ExprID);
				IRcodeVector.push_back(jmpStr);

				//std::cout<<(*(*stmt_listPtrVect)[i]->assignRHS->ExprVect).size()<<std::endl;
				for(int len = 0; len < (*(*stmt_listPtrVect)[i]->assignRHS->ExprVect).size(); len++ ){
					IRcodeVector.push_back(";POP");
				}

				//IRcodeVector.push_back(";POP");
				IRcodeVector.push_back(";POPREGS");
				std::string tempStr = "!T"+std::to_string((long long)tempReg);	
				tempReg++;
				std::string popStr = ";POP "+tempStr;
				IRcodeVector.push_back(popStr);
				//std::cout<<"pop offset: "<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
				int off = symTab->lhsOffset((*stmt_listPtrVect)[i]->assignLHS, function);
				//std::cout<<"returned offset: "<<off<<std::endl;
				//std::cout<<"STOREI LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
				std::stringstream ss;
				ss << off;
				std::string strOff(ss.str());	
				strOff = "$"+strOff;
				std::string storeStr;
				//std::cout<<"toktype: "<<(*stmt_listPtrVect)[i]->symb->var_type<<std::endl;
				
				int varType = symTab->lhsType((*stmt_listPtrVect)[i]->assignLHS, function);
				//std::cout<<"var type:  "<<varType<<std::endl;
				if (varType == 275){
					//std::cout<<"Fine!  "<<varType<<std::endl;
					storeStr = ";STOREI "+tempStr+" "+strOff;
				}
				if (varType == 278){
					storeStr = ";STOREF "+tempStr+" "+strOff;
				}
				IRcodeVector.push_back(storeStr);
			}
			else{
				//std::cout<<"Not call expr"<<std::endl;
				CodeObject* rootCo = VectorTable::createIRvector((*stmt_listPtrVect)[i]->assignRHS);
		
				std::string storeStr;
				//std::cout<<stmtVect[i]->symb->var_type<<std::endl;

			
				if (rootCo->type == "int"){
					//std::cout<<"Trying to print store int in not call expr"<<std::endl;
					//std::cout<<"node lhs: "<<node->assignLHS<<std::endl;
					//storeStr = ";STOREI "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
					if ((rootCo->result).find("!") != std::string::npos) {
						//std::cout<<"Temporary"<<std::endl;
						int off = symTab->lhsOffset((*stmt_listPtrVect)[i]->assignLHS, function);
						//std::cout<<"returned offset: "<<off<<std::endl;
						//std::cout<<"STOREI LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
						std::stringstream ss;
						ss << off;
						std::string strOff(ss.str());	
						strOff = "$"+strOff;
						//storeStr = ";STOREI "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
						storeStr = ";STOREI "+rootCo->result+" "+strOff;
						rootCo->instruction.push_back(storeStr);	
					} 
					else{
						//std::cout<<rootCo->result<<std::endl;
						std::string tempStr = "!T"+std::to_string((long long)tempReg);	
						tempReg++;
						if (storeTemps == 1){
							tempVect.push_back(tempStr);
						}
						int off = symTab->lhsOffset((*stmt_listPtrVect)[i]->assignLHS, function);
						//std::cout<<"returned offset: "<<off<<std::endl;
						//std::cout<<"STOREI LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
						std::stringstream ss;
						ss << off;
						std::string strOff(ss.str());	
						strOff = "$"+strOff;

						//std::cout<<"STOREI rootco->result"<<rootCo->result<<std::endl;
						//std::cout<<"STOREI LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
						std::string storeStr1 = ";STOREI "+rootCo->result+" "+tempStr;
						//std::string storeStr2 = ";STOREI "+tempStr+" "+(*stmt_listPtrVect)[i]->assignLHS;
						std::string storeStr2 = ";STOREI "+tempStr+" "+strOff;
						rootCo->instruction.push_back(storeStr1);
						rootCo->instruction.push_back(storeStr2);		
					}
				}
				else if (rootCo->type == "float"){
					//std::cout<<"Trying to print store float in not call expr"<<std::endl;

					if ((rootCo->result).find("!") != std::string::npos) {
						//std::cout<<"Temporary"<<std::endl;
						int off = symTab->lhsOffset((*stmt_listPtrVect)[i]->assignLHS, function);
						//std::cout<<"returned offset: "<<off<<std::endl;
						//std::cout<<"STOREF LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
						std::stringstream ss;
						ss << off;
						std::string strOff(ss.str());	
						strOff = "$"+strOff;
						//storeStr = ";STOREF "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
						storeStr = ";STOREF "+rootCo->result+" "+strOff;
						rootCo->instruction.push_back(storeStr);
					} 
					else{
						//std::cout<<rootCo->result<<std::endl;
						std::string tempStr = "!T"+std::to_string((long long)tempReg);	
						tempReg++;
						if (storeTemps == 1){
							tempVect.push_back(tempStr);
						}
						int off = symTab->lhsOffset((*stmt_listPtrVect)[i]->assignLHS, function);
						//std::cout<<"returned offset: "<<off<<std::endl;
						//std::cout<<"STOREF LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
						std::stringstream ss;
						ss << off;
						std::string strOff(ss.str());	
						strOff = "$"+strOff;

						//std::cout<<"STOREF rootco->result"<<rootCo->result<<std::endl;
						//std::cout<<"STOREF LHS"<<(*stmt_listPtrVect)[i]->assignLHS<<std::endl;
						std::string storeStr1 = ";STOREF "+rootCo->result+" "+tempStr;
						//std::string storeStr2 = ";STOREF "+tempStr+" "+(*stmt_listPtrVect)[i]->assignLHS;
						std::string storeStr2 = ";STOREF "+tempStr+" "+strOff;
						rootCo->instruction.push_back(storeStr1);
						rootCo->instruction.push_back(storeStr2);		
					}

					//storeStr = ";STOREF "+rootCo->result+" "+(*stmt_listPtrVect)[i]->assignLHS;
					//std::cout<<"StoreStr is:"<<storeStr<<std::endl;
				}
			

			
				if(!rootCo->instruction.empty()){
					coVect.push_back(rootCo);
					//std::cout<<"Printing covect element in arith "<<coVect[coVect.size()-1]->result<<std::endl;		
					//std::cout<<"Root co instruction is NOT empty"<<std::endl;		
					VectorTable::printIRcode(rootCo->instruction);	
					
				}
			}
			


		}
	}
	
	if (!vectChildren.empty()){
		//std::cout<<"in children vect recursive"<<std::endl;
		int childSize;
		childSize = vectChildren.size();
		for (int j=0; j<childSize; j++){
			//std::cout<<std::endl;
			coVect = (vectChildren[j])->StackIteratorforIR(coVect,function,symTab);
		}
	
	}
	//std::cout<<"final string is IRCode vect"<<std::endl;
	finalIRstringVector = IRcodeVector;
	//std::cout<<"returning coVect"<<std::endl;
	return coVect;

}




/*
void VectorTable::IRtoAssembly(std::vector<CodeObject*> coVect){

	for (int i = 0; i<coVect.size(); i++){
		for (int j = 0; j<(coVect[i]->instruction.size()); j++){			
			printAssembly(coVect[i]->instruction[j]);
		}
	}
	std::cout<<"sys halt"<<std::endl;
}*/ //------------------->>>>>> PRINTING ASSEMBLY ORIGINAL

void VectorTable::IRtoAssembly(std::vector<std::string> IRvect){

	for (int i = 0; i<IRvect.size(); i++){		
		printAssembly(IRvect[i]);
	}

}

void VectorTable::printAssembly(std::string IR){
	//std::cout<<IR<<std::endl;
	std::string delimiter = " ";
	std::string token;
	std::vector<std::string> indivStrVect;
	
    	size_t prev = 0, pos = 0;
	do{
        	pos = IR.find(delimiter, prev);
        	if (pos == std::string::npos) pos = IR.length();
        		token = IR.substr(prev, pos-prev);
        	if (!token.empty()) indivStrVect.push_back(token);
       	 		prev = pos + delimiter.length();
    	}while (pos < IR.length() && prev < IR.length());
    
	
	if (indivStrVect[0] == ";PUSH"){

		if (indivStrVect.size() == 1){
			std::cout<<"push"<<std::endl;
		}
		else{
			if (indivStrVect[1].find("!") != std::string::npos) {
				if(indivStrVect[1].length() == 3){
					char lastChar2 = indivStrVect[1].at(indivStrVect[1].length()-1);
					std::string regStr1;
					regStr1.append("r");
					regStr1.append(std::string(1,lastChar2));
					regStr1.append(" ");
					std::cout<<"push "<<regStr1<<std::endl;
				}

				else if (indivStrVect[1].length() == 4){
					std::string lastChars = indivStrVect[1].substr(2,2);
					std::string regStr1 = "r"+lastChars+" ";
					std::cout<<"push "<<regStr1<<std::endl;
				}
			}
			else{
				std::cout<<"push "<<indivStrVect[1]<<std::endl;
			}
		}
				
	}

	if (indivStrVect[0] == ";PUSHREGS"){
		std::cout<<"push r0"<<std::endl;	
		std::cout<<"push r1"<<std::endl;	
		std::cout<<"push r2"<<std::endl;	
		std::cout<<"push r3"<<std::endl;	
	}

	if (indivStrVect[0] == ";POP"){
		if (indivStrVect.size() == 1){
			std::cout<<"pop"<<std::endl;
		}
		else{
			if (indivStrVect[1].find("!") != std::string::npos) {
				if(indivStrVect[1].length() == 3){
					char lastChar2 = indivStrVect[1].at(indivStrVect[1].length()-1);
					std::string regStr1;
					regStr1.append("r");
					regStr1.append(std::string(1,lastChar2));
					regStr1.append(" ");
					std::cout<<"pop "<<regStr1<<std::endl;
				}

				else if (indivStrVect[1].length() == 4){
					std::string lastChars = indivStrVect[1].substr(2,2);
					std::string regStr1 = "r"+lastChars+" ";
					std::cout<<"pop "<<regStr1<<std::endl;
				}
			}
		}
	}

	if (indivStrVect[0] == ";POPREGS"){
		std::cout<<"pop r3"<<std::endl;	
		std::cout<<"pop r2"<<std::endl;	
		std::cout<<"pop r1"<<std::endl;	
		std::cout<<"pop r0"<<std::endl;	
	}


	if (indivStrVect[0] == ";JSR"){
		std::cout<<"jsr "<<indivStrVect[1]<<std::endl;
	}

	if (indivStrVect[0] == ";HALT"){
		std::cout<<"sys halt"<<std::endl;
	}

	if (indivStrVect[0] == ";LABEL"){
		std::cout<<"label "<<indivStrVect[1]<<std::endl;
	}

	if (indivStrVect[0] == ";LINK"){
		std::cout<<"link "<<indivStrVect[1]<<std::endl;
	}

	if (indivStrVect[0] == ";JUMP"){
		std::cout<<"jmp "<<indivStrVect[1]<<std::endl;
	}

	if (indivStrVect[0] == ";RET"){
		std::cout<<"unlnk"<<std::endl;
		std::cout<<"ret"<<std::endl;
	}

	if (indivStrVect[0] == ";GTI"){
		/*		
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			std::cout<<"cmpi "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
		}
		std::cout<<"jgt "<<indivStrVect[3]<<std::endl;   */
	
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jgt "<<indivStrVect[3]<<std::endl;
	



	}

	if (indivStrVect[0] == ";LTI"){

		/*
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

		}
		else{
			std::cout<<"cmpi "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
		}
		std::cout<<"jlt "<<indivStrVect[3]<<std::endl;
		*/

		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jlt "<<indivStrVect[3]<<std::endl;
		

	}

	if (indivStrVect[0] == ";GEI"){

		/*
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			std::cout<<"cmpi "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
		}
		std::cout<<"jge "<<indivStrVect[3]<<std::endl;   */

		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jge "<<indivStrVect[3]<<std::endl;


	}


	if (indivStrVect[0] == ";LEI"){
		/*
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}		
		else{
			std::cout<<"cmpi "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
		}
		std::cout<<"jle "<<indivStrVect[3]<<std::endl;   */

		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jle "<<indivStrVect[3]<<std::endl;


	}


	if (indivStrVect[0] == ";EQI"){

		/*
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			std::cout<<"cmpi "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;	
		}
		std::cout<<"jeq "<<indivStrVect[3]<<std::endl;*/

		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jeq "<<indivStrVect[3]<<std::endl;


	}


	if (indivStrVect[0] == ";NEI"){

		/*
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			std::cout<<"cmpi "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;	
		}

		std::cout<<"jne "<<indivStrVect[3]<<std::endl;*/

		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpi "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jne "<<indivStrVect[3]<<std::endl;



	}


	if (indivStrVect[0] == ";GTF"){
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jgt "<<indivStrVect[3]<<std::endl;
	}


	if (indivStrVect[0] == ";LTF"){
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jlt "<<indivStrVect[3]<<std::endl;
	}

	if (indivStrVect[0] == ";GEF"){
		//std::cout<<"In GEF"<<std::endl;
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jge "<<indivStrVect[3]<<std::endl;
	}


	if (indivStrVect[0] == ";LEF"){
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jle "<<indivStrVect[3]<<std::endl;
	}


	if (indivStrVect[0] == ";EQF"){
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jeq "<<indivStrVect[3]<<std::endl;
	}

	if (indivStrVect[0] == ";NEF"){
		if (indivStrVect[2].find("!") != std::string::npos) {
			if(indivStrVect[2].length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = indivStrVect[2].at(indivStrVect[2].length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (indivStrVect[2].length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = indivStrVect[2].substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}
		}
		else{
			//Create temporary
			std::string tempStr = "!T"+std::to_string((long long)tempReg);	
			//std::string tempStr = "!T"+s;
			tempReg++;
			//std::cout<<"cmpr "<<indivStrVect[1]<<" "<<indivStrVect[2]<<std::endl;
			if(tempStr.length() == 3){
				//std::cout<<"length is 3"<<std::endl;
				char lastChar2 = tempStr.at(tempStr.length()-1);
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}

			else if (tempStr.length() == 4){
				//std::cout<<"length is 4"<<std::endl;
				std::string lastChars = tempStr.substr(2,2);
				std::string regStr1 = "r"+lastChars+" ";
				std::cout<<"move "<<indivStrVect[2]<<" "<<regStr1<<std::endl;
				std::cout<<"cmpr "<<indivStrVect[1]<<" "<<regStr1<<std::endl;
			}


		}
		std::cout<<"jne "<<indivStrVect[3]<<std::endl;
	}



	if (indivStrVect[0] == ";STOREI"){
		//std::cout<<"Storing after add!!!"<<std::endl;
		//std::cout<<indivStrVect[0]<<indivStrVect[1]<<std::endl;
		std::string assemStr = "";		
		assemStr = assemStr+"move ";
		char firstChar2 = ((indivStrVect[2]).at(0));
		//std::cout<<"indiv[1] "<<indivStrVect[1]<<std::endl;		
		//std::cout<<"firstChar2: "<<firstChar2<<std::endl;

		try {  
			int x = std::stoi(indivStrVect[1]);
			assemStr = assemStr + indivStrVect[1]+" ";
		}
		catch(...){
			if (indivStrVect[1].find("!") != std::string::npos) {
				if(indivStrVect[1].length() == 3){
					char lastChar1 = indivStrVect[1].at( indivStrVect[1].length() - 1 );
					//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
					std::string regStr1;
					regStr1.append("r");
					regStr1.append(std::string(1,lastChar1));
					regStr1.append(" ");
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}

				else if (indivStrVect[1].length() == 4){
					std::string lastChars = indivStrVect[1].substr(2,2);
					//std::cout<<"lastChars: "<<lastChars<<std::endl;
					std::string regStr1 = "r"+lastChars+" ";
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}
			}

			else{
				/*
				if(indivStrVect[2].length() == 3){
					char lastChar1 = indivStrVect[2].at( indivStrVect[2].length() - 1 );
					//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
					std::string regStr1;
					regStr1.append("r");
					regStr1.append(std::string(1,lastChar1));
					regStr1.append(" ");
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}

				else if (indivStrVect[2].length() == 4){
					std::string lastChars = indivStrVect[2].substr(2,2);
					//std::cout<<"lastChars: "<<lastChars<<std::endl;
					std::string regStr1 = "r"+lastChars+" ";
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}*/
				assemStr = assemStr + indivStrVect[1] + " ";


			}


		}
		
		if (firstChar2 == '!'){
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at( indivStrVect[2].length() - 1 );
				//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				//std::cout<<"lastChars: "<<lastChars<<std::endl;
				std::string regStr1 = "r"+lastChars+" ";
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}

		}
		else{
			assemStr = assemStr + indivStrVect[2];
		}
		//return AssemblyStrVec;
		std::cout<<assemStr<<std::endl;	
	}
	
	if (indivStrVect[0] == ";STOREF"){
		std::string assemStr = "";		
		assemStr = assemStr+"move ";
		char firstChar2 = ((indivStrVect[2]).at(0));
		//std::cout<<"indiv[1] "<<indivStrVect[1]<<std::endl;		
		//std::cout<<"firstChar2: "<<firstChar2<<std::endl;

		try {  
			int x = std::stof(indivStrVect[1]);
			assemStr = assemStr + indivStrVect[1]+" ";
		}
		catch(...){
			//Not float; string; storef num r1
			if (indivStrVect[1].find("!") != std::string::npos) {
				if(indivStrVect[1].length() == 3){
					char lastChar1 = indivStrVect[1].at( indivStrVect[1].length() - 1 );
					//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
					std::string regStr1;
					regStr1.append("r");
					regStr1.append(std::string(1,lastChar1));
					regStr1.append(" ");
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}

				else if (indivStrVect[1].length() == 4){
					std::string lastChars = indivStrVect[1].substr(2,2);
					//std::cout<<"lastChars: "<<lastChars<<std::endl;
					std::string regStr1 = "r"+lastChars+" ";
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}
			}
		
			else{
				/*
				if(indivStrVect[2].length() == 3){
					char lastChar1 = indivStrVect[2].at( indivStrVect[2].length() - 1 );
					//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
					std::string regStr1;
					regStr1.append("r");
					regStr1.append(std::string(1,lastChar1));
					regStr1.append(" ");
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}

				else if (indivStrVect[2].length() == 4){
					std::string lastChars = indivStrVect[2].substr(2,2);
					//std::cout<<"lastChars: "<<lastChars<<std::endl;
					std::string regStr1 = "r"+lastChars+" ";
					//std::cout<<"regstr "<<regStr1<<std::endl;		
					assemStr = assemStr + regStr1;
				}*/
				assemStr = assemStr + indivStrVect[1] + " ";
			}
		}
		
		if (firstChar2 == '!'){
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at( indivStrVect[2].length() - 1 );
				//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				//std::cout<<"lastChars: "<<lastChars<<std::endl;
				std::string regStr1 = "r"+lastChars+" ";
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}

		}
		else{
			assemStr = assemStr + indivStrVect[2];
		}

		std::cout<<assemStr<<std::endl;	
	}



	if (indivStrVect[0] == ";ADDI" | indivStrVect[0] == ";SUBI" | indivStrVect[0] == ";MULI" | indivStrVect[0] == ";DIVI" | indivStrVect[0] == ";ADDF" | indivStrVect[0] == ";SUBF" | indivStrVect[0] == ";MULF" | indivStrVect[0] == ";DIVF"){ //in any add/sub/mul/div, I include a '\n' as a vector element so as to split the vector into 2 vectors (move + <operation>i/f)

		//First add the move statement
		std::string assemStr = "";		
		assemStr = assemStr+"move ";
		char firstChar1 = ((indivStrVect[1]).at(0));
		if (firstChar1 == '!'){
			if(indivStrVect[1].length() == 3){
				char lastChar1 = indivStrVect[1].at( indivStrVect[1].length() - 1 );
				//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar1));
				regStr1.append(" ");
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}

			else if (indivStrVect[1].length() == 4){
				std::string lastChars = indivStrVect[1].substr(2,2);
				//std::cout<<"lastChars: "<<lastChars<<std::endl;
				std::string regStr1 = "r"+lastChars+" ";
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}
		}
		else{
			assemStr = assemStr + indivStrVect[1]+" ";
		}
		
		if(indivStrVect[3].length() == 3){
				char lastChar3 = indivStrVect[3].at( indivStrVect[3].length() - 1 );
				//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar3));
				regStr1.append(" ");
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}

		else if (indivStrVect[3].length() == 4){
				std::string lastChars = indivStrVect[3].substr(2,2);
				//std::cout<<"lastChars: "<<lastChars<<std::endl;
				std::string regStr1 = "r"+lastChars+" ";
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr = assemStr + regStr1;
			}
		
		std::cout<<assemStr<<std::endl;	//first print move statement
		
		std::string assemStr2 = "";		

		//Next add the <operation>i/f statement
		if (indivStrVect[0] == ";ADDI"){
			assemStr2 = assemStr2+"addi ";
		} 
		else if (indivStrVect[0] == ";SUBI"){
			assemStr2 = assemStr2+"subi ";
		}
		else if (indivStrVect[0] == ";MULI"){
			assemStr2 = assemStr2+"muli ";
		}
		else if (indivStrVect[0] == ";DIVI"){
			assemStr2 = assemStr2+"divi ";
		}

		else if (indivStrVect[0] == ";ADDF"){
			assemStr2 = assemStr2+"addr ";
		} 
		else if (indivStrVect[0] == ";SUBF"){
			assemStr2 = assemStr2+"subr ";
		}
		else if (indivStrVect[0] == ";MULF"){
			assemStr2 = assemStr2+"mulr ";
		}
		else if (indivStrVect[0] == ";DIVF"){
			assemStr2 = assemStr2+"divr ";
		}

		char firstChar2 = ((indivStrVect[2]).at(0));
		if (firstChar2 == '!'){
			if(indivStrVect[2].length() == 3){
				char lastChar2 = indivStrVect[2].at( indivStrVect[2].length() - 1 );
				//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar2));
				regStr1.append(" ");
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr2 = assemStr2 + regStr1;
			}

			else if (indivStrVect[2].length() == 4){
				std::string lastChars = indivStrVect[2].substr(2,2);
				//std::cout<<"lastChars: "<<lastChars<<std::endl;
				std::string regStr1 = "r"+lastChars+" ";
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr2 = assemStr2 + regStr1;
			}
		}
		else{
			assemStr2 = assemStr2 + indivStrVect[2]+" ";
		}
		
		if(indivStrVect[3].length() == 3){
				char lastChar3 = indivStrVect[3].at( indivStrVect[3].length() - 1 );
				//std::cout<<"lastChar1: "<<lastChar1<<std::endl;
				std::string regStr1;
				regStr1.append("r");
				regStr1.append(std::string(1,lastChar3));
				regStr1.append(" ");
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr2 = assemStr2 + regStr1;
			}

		else if (indivStrVect[3].length() == 4){
				std::string lastChars = indivStrVect[3].substr(2,2);
				//std::cout<<"lastChars: "<<lastChars<<std::endl;
				std::string regStr1 = "r"+lastChars+" ";
				//std::cout<<"regstr "<<regStr1<<std::endl;		
				assemStr2 = assemStr2 + regStr1;
			}


		std::cout<<assemStr2<<std::endl;	//print oper statement
	}
	

	
	if (indivStrVect[0] == ";READI" | indivStrVect[0] == ";READF"){
		std::string assemStr = "";		
		if (indivStrVect[0] == ";READI"){
			assemStr = assemStr +"sys readi ";
		}
		else if (indivStrVect[0] == ";READF"){		
			assemStr = assemStr +"sys readr ";
		}	
		assemStr = assemStr +indivStrVect[1];
		std::cout<<assemStr<<std::endl;	

	}
	
	if (indivStrVect[0] == ";WRITEI" | indivStrVect[0] == ";WRITEF" | indivStrVect[0] == ";WRITES"){
		std::string assemStr = "";
		if (indivStrVect[0] == ";WRITEI"){
			assemStr = assemStr +"sys writei ";
		}
		else if (indivStrVect[0] == ";WRITEF"){		
			assemStr = assemStr +"sys writer ";
		}	
		else if (indivStrVect[0] == ";WRITES"){		
			assemStr = assemStr +"sys writes ";
		}	
		assemStr = assemStr +indivStrVect[1];
		std::cout<<assemStr<<std::endl;	
	}
	

}




