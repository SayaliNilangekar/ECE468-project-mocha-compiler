#include<vector>
using std::vector;

typedef class IRNode{
public:
	char intruction[10];	// this is the instruction
	char oper1[10];			// this is the first operator
	char oper2[10];			// this is the second operator (may be null for read or write or store)
	char result[10]; 		// this is the temp where result will be stored
}IRNode;

typedef class CodeObj{

public:
	vector<IRNode> InstrSeq;	// the list of 3AC instructions
	char result[10];	// this is the temp where result is stored
	int type;		/* this is the type of the result of the instruction
							1->int var
							2->float var
							3->int literal
							4->float literal
					*/	
}CodeObj;


/*
 *	Function accepts pointer to root node of an AST (so type AST*), and returns 3AC instruction for the expression.
 *	The 3AC instrutions should be stored in correct order in the InstrSeq of the CodeObj returned.
 */
CodeObj return_RHS_3AC(AST*);	

/*
 *	Helper function to keep generating new temporaries
 *	Generates new temporaries by having global counter keep incrementing
 */
char* generateTemp();
