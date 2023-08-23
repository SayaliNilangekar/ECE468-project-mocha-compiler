#include"SymbolTable.h"
int tempNum = 0;
CodeObj return_RHS_3AC(ASTNode* astNode){

	//we have a stack of each scope/function which points to vectors list. The vector list contains all the nodes which are all AST but
	//you have to iterate through the stack to get the vector with all nodes
	// 1. IOnodes do not have left or right : you have to check if they have IOtype as READ or WRITE then you are sure that it is IONode. IONode just have IOtype, token
	// 2. Assign Node contains LHS and RHS :
	//		To access LHS => assign_node->assignLHS
	//		To access rhs tree do assign_node->assignRHS. assignRHS is the root node of the AST.
	// CHECK THE PRINT STACK FUNCTION IN SYMBOLTABLE.CPP of src.zip I have attached

	CodeObj left_codeObj = return_RHS_3AC(astNode->leftChild);
	CodeObj right_codeObj = return_RHS_3AC(astNode->rightChild);
	CodeObj newObj;

	// now generate code for yourself
	if (astNode->tokType == 0){		// arithmetic node
		IRNode newnode;

		// assign operator fields to newnode
		newnode.oper1 = left_codeObj.result;
		newnode.oper2 = right_codeObj.result;

		// assign result location to new temporary
		newnode.result = generateTemp();

		// figure out instruction code
		char oper;
		std::string oper_string = astNode->token;		// +, -, *. /
		if (oper_string == "_PLUS"){
			oper = '+';
		}
		else if (oper_string == "_MINUS"){
			oper = '-';
		}
		else if (oper_string == "_MUL"){
			oper = '*';
		}
		else{
			oper = '/';
		}
		int type = left_codeObj.type;		// int or float

		switch(type){
			case 2:		// int
			case 5:
				switch(oper){

					case '+': newnode.instruction = "ADDI";
						break;
					case '-': newnode.instruction = "SUBI";
						break;
					case '*': newnode.instruction = "MULI";
						break;
					case '/': newnode.instruction = "DIVI";
						break;
				}
				break;
			case 3:		// float
			case 6:	
				switch(oper){
					case '+': newnode.instruction = "ADDF";
						break;
					case '-': newnode.instruction = "SUBF";
						break;
					case '*': newnode.instruction = "MULF";
						break;
					case '/': newnode.instruction = "DIVF";
						break;
				}
				break;
			}

			// fill in codeObj attributes
			newObj.type = type;
			newObj.result = newnode.result;
			for (int i = 0; i < left_codeObj.InstrSeq.size(); i++){
				newObj.InstrSeq.push_back(left_codeObj.InstrSeq[i]);
			}
			for (int i = 0; i < right_codeObj.InstrSeq.size(); i++){
				newObj.InstrSeq.push_back(right_codeObj.InstrSeq[i]);
			}
			newObj.InstrSeq.push_back(newnode);

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
			case 5:	newnode.instruction = "STOREI";
					break;
			case 6: newnode.instruction = "STOREF";
					break;
		}

		newObj.InstrSeq.push_back(newnode);
		newObj.type = astNode->tokType;
		newObj.result = newnode.result;

	}
	else{

		newObj.result = astNode->token;

		switch(astNode->tokType){
			case 2: newObj.type = 2;
				break;
			case 3: newObj.type = 3;
				break;
		}
	}

	return newObj;
}

std::string generateTemp(){
	std::string temp;
	temp = "!T";
	temp = temp + std::to_string(tempNum++); // so example temp = "!T10"
	
	return temp;
}
