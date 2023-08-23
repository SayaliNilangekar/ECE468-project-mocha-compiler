void PrintAssembly(std::vector IRcodeList, SymbolTable* table){
	
	PrintVarDecl();

	for(std::vector<std::string>::iterator it=IRcodeList.begin();it!=IRcodeList.end();++it){ 
		
		std::istringstream iss(it);
		std::vector<std::string> splitStringVector ((std::istream_iterator<std::string>(iss)),std::istream_iterator<std:string>());

		std::vector<std::string> AssemblyStrVector;
		AssemblyStrVector = IRtoAssembly(splitStringVector);
		len = AssemblyStrVector.size;		
		string AssemStr;

		if(std::find(AssemblyStrVector.begin(), AssemblyStrVector.end(),"\n") != AssemblyStrVector.end()) {
			/* v contains x */  //HAVE TO SPLIT VECTOR INTO THE TWO SUB STATEMENTS
		} else {
    			for (int k=0; k<len; k++){
				AssemStr = AssemStr + AssemblyStrVector[k];
			} 
		}
		
		
	}

}

void PrintVarDecl(){
	sz = table.size();
	for (int i=0; i<sz; i++){
		std::string name;
		name.assign(table[i]->var_name);
		std::cout<<"var "<<name<<std::endl;	

	if (!children.empty()){
		int childSize;
		childSize = children.size();
		for (int j=0; j<childSize; j++){
			std::cout<<std::endl;
			(children[j])->PrintVarDecl();
		}		
	
}

std::vector IRtoAssembly(vector IR){

	std::vector<std::string> AssemblyStrVec;

	//STORE OF 2 DIFFERENT TYPES, handle that

	if (IR[0] == ";STOREI"){
		AssemblyStrVec.push_back("move");
		if (atoi(IR[1]) != 0){
			AssemblyStrVec.push_back(IR[1]);
		}
		else{
			std::string regStr1 = "r"+IR[1].back();
			AssemblyStrVec.push_back(regStr1);
		}
		if (IR[2].front == "!"){
			std::string regStr2 = "r"+IR[2].back();
			AssemblyStrVec.push_back(regStr2);
		}
		else{
			AssemblyStrVec.push_back(IR[2]);
		}
		return AssemblyStrVec;	
	}

	if (IR[0] == ";STOREF"){
		AssemblyStrVec.push_back("move");
		if (atof(IR[1]) != 0){
			AssemblyStrVec.push_back(IR[1]);
		}
		else{
			std::string regStr1 = "r"+IR[1].back();
			AssemblyStrVec.push_back(regStr1);
		}
		if (IR[2].front == "!"){
			std::string regStr2 = "r"+IR[2].back();
			AssemblyStrVec.push_back(regStr2);
		}
		else{
			AssemblyStrVec.push_back(IR[2]);
		}
		return AssemblyStrVec;	
	}


	if (IR[0] == ";ADDI" | IR[0] == ";SUBI" | IR[0] == ";MULI" | IR[0] == ";DIVI" | IR[0] == ";ADDF" | IR[0] == ";SUBF" | IR[0] == ";MULF" | IR[0] == ";DIVF"){ //in any add/sub/mul/div, I include a '\n' as a vector element so as to split the vector into 2 vectors (move + <operation>i/f)

		//First add the move statement
		AssemblyStrVec.push_back("move");
		if (IR[1].front == "!") != 0){
			std::string regStr1 = "r"+IR[1].back();
			AssemblyStrVec.push_back(regStr1);
		}
		else{
			AssemblyStrVec.push_back(IR[1]);			
		}
		
		std::string regStr2 = "r"+IR[3].back();
		AssemblyStrVec.push_back(regStr2);
		
		AssemblyStrVec.push_back("\n");  //To separate the move and addi statements
		

		//Next add the <operation>i/f statement
		if (IR[0] == ";ADDI"){
			AssemblyStrVec.push_back("addi");
		} 
		else if (IR[0] == ";SUBI"){
			AssemblyStrVec.push_back("subi");
		}
		else if (IR[0] == ";MULI"){
			AssemblyStrVec.push_back("muli");		
		}
		else if (IR[0] == ";DIVI"){
			AssemblyStrVec.push_back("divi");
		}

		else if (IR[0] == ";ADDF"){
			AssemblyStrVec.push_back("addf");
		} 
		else if (IR[0] == ";SUBF"){
			AssemblyStrVec.push_back("subf");
		}
		else if (IR[0] == ";MULF"){
			AssemblyStrVec.push_back("mulf");		
		}
		else if (IR[0] == ";DIVF"){
			AssemblyStrVec.push_back("divf");
		}


		if (IR[2].front == "!") != 0){
			std::string regStr3 = "r"+IR[2].back();
			AssemblyStrVec.push_back(regStr3);
		}
		else{
			AssemblyStrVec.push_back(IR[2]);			
		}
		
		std::string regStr4 = "r"+IR[3].back();
		AssemblyStrVec.push_back(regStr4);
		


		return AssemblyStrVec;	
	}
	


	if (IR[0] == ";READI" | IR[0] == ";READF"){
		
		if (IR[0] == ";READI"){
			AssemblyStrVec.push_back("sys readi");
		}
		else if (IR[0] == ";READF"){		
			AssemblyStrVec.push_back("sys readf");
		}	
		AssemblyStrVec.push_back(IR[1]);
	}

	if (IR[0] == ";WRITEI" | IR[0] == ";WRITEF" | IR[0] == ";WRITES"){
		
		if (IR[0] == ";WRITEI"){
			AssemblyStrVec.push_back("sys writei");
		}
		else if (IR[0] == ";WRITEF"){		
			AssemblyStrVec.push_back("sys writef");
		}	
		else if (IR[0] == ";WRITES"){		
			AssemblyStrVec.push_back("sys writes");
		}	
		AssemblyStrVec.push_back(IR[1]);
	}


}
