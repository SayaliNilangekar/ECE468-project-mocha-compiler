#include"IR.h"
#include<string>
int tempNum = 0;

CodeObj return_RHS_3AC(AST* astNode){
	//we have a stack of each scope/function which points to vectors list. The vector list contains all the nodes which are all AST but
	//you have to iterate through the stack to get the vector with all nodes
	// 1. IOnodes do not have left or right : you have to check if they have IOtype as READ or WRITE then you are sure that it is IONode. IONode just have IOtype, token
	// 2. Assign Node contains LHS and RHS :
	//		To access LHS => assign_node->assignLHS
	//		To access rhs tree do assign_node->assignRHS. assignRHS is the root node of the AST.
	// CHECK THE PRINT STACK FUNCTION IN SYMBOLTABLE.CPP of src.zip I have attached

	left_codeObj = return_RHS_3AC(astNode->left);
	right_codeObj = return_RHS_3AC(astNode->right);

	// now generate code for yourself
	if astNode->type == 0{		// arithmetic node
		IRNode newnode;
		CodeObj newObj;

		// assign operator fields to newnode
		strcpy(newnode.oper1,left_codeObj.result);
		strcpy(newnode.oper2, right_codeObj.result);

		// assign result location to new temporary
		strcpy(newnode.result, generateTemp());

		// figure out instruction code
		char oper = astNode->token;		// +, -, *. /
		int type = astNode->type;		// int or float

		switch(type){
			case 1:		// int
				switch(oper){
					case '+': strcpy(newnode->instruction, "ADDI");
						break;
					case '-': strcpy(newnode->instruction, "SUBI");
						break;
					case '*': strcpy(newnode->instruction, "MULI");
						break;
					case '/': strcpy(newnode->instruction, "DIVI");
						break;
				}
				break;
			case 2:		// float
				switch(oper){
					case '+': strcpy(newnode->instruction, "ADDF");
						break
					case '-': strcpy(newnode->instruction, "SUBF");
						break;
					case '*': strcpy(newnode->instruction, "MULF");
						break;
					case '/': strcpy(newnode->instruction, "DIVF");
						break;
				}
				break;
			}

			// fill in codeObj attributes
			newObj.type = astNode->type;
			strcpy(newObj.result, newnode.result);
			newObj.InstrSeq.push_back(left_codeObj.InstrSeq);
			newObj.InstrSeq.push_back(right_codeObj.InstrSeq);
			newObj.InstrSeq.push_back(newnode);

	}
	else if (astNode->type == 4 || astNode->type == 5){	// if it is a literal
		CodeObj newObj;
	/*
				 * NOT SURE IF THIS NECESSARY *
		newObj->InstrSeq.push_back(left_codeObj->InstrSeq);
		newObj->InstrSeq.push_back(right_codeObj->InstrSeq);
	*/
		// creating current 3AC
		IRNode newnode;
		strcpy(newnode.oper1,astNode->token);
		strcpy(newnode.oper2,"\0");
		strcpy(newnode.result,generateTemp());

		switch(ASTNode->type){
			case 4:	strcpy(newnode.instruction ,"STOREI");
					break;
			case 5: strcpy(newnode->instruction, "STOREF");
					break;
		}

		newObj.InstrSeq.push_back(newnode);
		newObj.type = astNode->type;
		strcpy(newObj.result, newnode.result);

	}
	else{
		CodeObj newObj;

		strcpy(newObj.result, astNode->tok);
		switch(ASTNode->type){
			case 2: newObj.type = 2;
				break;
			case 3: newObj.type = 3;
				break;
		}
	}

	return newObj;
}

char* generateTemp(){
	char temp[10];
	strcat(temp, "!T");
	strcat(temp, (string)tempNum); // so example temp = "!T10"

	return temp;
}
