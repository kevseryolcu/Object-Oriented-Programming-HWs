#ifndef ASSISTANTFUNCTIONSH_
#define ASSISTANTFUNCTIONSH_

#include <string>

const int MEM_SIZE = 50;
const int LOWA = 97;	/* ASCII 'a' */
const int LOWZ = 122;   /* ASCII 'z' */
const int UPA = 65;     /* ASCII 'A' */
const int UPZ = 90;     /* ASCII 'Z' */
const int ZERO = 48;    /* ASCII '0' */
const int NINE = 57;    /* ASCII '9' */
const int MAX_INST = 200;//maximum instruction number*/


union Operand{
	int reg;
	int constant;
	int address;
};

/*an assembly code includes - MNEMONIC LEFT_OPERAND, RIGHT_OPERAND*/
struct Instruction{
	std::string mnemonic;
	Operand operandR;	
	Operand operandL;
	bool hasROperand = false;	/*does it has right operand*/
	char kindOfR;				
	char kindOfL;				/* if operand constant, 
								   then kindOfR or kindOfL 'c';
								   if register, then 'r';   */
};

int analyzeLine(std::string line, Instruction& inst);

bool equalsTo(std::string str, std::string mnem);

bool myIsAlpha(char c);

bool myIsDigit(char c);

/*Coverts lower letter to upper letter*/
char myToUpper(char letter);

/*Converts string to integer*/
int overloadStoi(std::string str);

std::string myStringToUpper(std::string& inp);

#endif
