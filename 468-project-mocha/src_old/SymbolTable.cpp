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

