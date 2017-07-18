#ifndef ASSISTANTFUNCTIONSH_
#define ASSISTANTFUNCTIONSH_

#include <string>

const int LOWA = 97;	/* ASCII 'a' */
const int LOWZ = 122;   /* ASCII 'z' */
const int UPA = 65;     /* ASCII 'A' */
const int UPZ = 90;     /* ASCII 'Z' */
const int ZERO = 48;    /* ASCII '0' */
const int NINE = 57;    /* ASCII '9' */
const int MEM_SIZE = 50;/*memory size*/


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

/*Analayzes given instruction line, stores in a Instruction object*/
int analyzeLine(std::string line, Instruction& inst);

/*if two string equals to each other returns true*/
bool equalsTo(std::string str, std::string mnem);

/*If a character is a alphabet, returns true*/
bool myIsAlpha(char c);

/*If a character is a digit, returns true*/
bool myIsDigit(char c);

/*Coverts lower letter to upper letter*/
char myToUpper(char letter);

/*Converts string to integer*/
int overloadStoi(std::string str);

/*if letters of string is lower alphabet, converts them upper*/
std::string myStringToUpper(std::string& inp);

#endif
