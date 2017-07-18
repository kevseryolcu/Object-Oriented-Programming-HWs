#ifndef CPUH_
#define CPUH_

#include <string>

const int LOWA = 97;    /* ASCII 'a' */
const int LOWZ = 122;    /* ASCII 'z' */
const int UPA = 65;    /* ASCII 'A' */
const int UPZ = 90;   /* ASCII 'Z' */
const int ZERO = 48;      /* ASCII '0' */
const int NINE = 57;      /* ASCII '9' */


union Operand{
	int reg;
	int constant;
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


class CPU
{
public:
	CPU();
	void setRegisters(int r1, int r2, int r3, int r4, int r5);
	void setPC(int number);
	void setR(int regNumber, int content);
	int getPC() const{return PC;};
	int getR(int regNumber) const;
	bool halted();
	void print() const;
	int execute(std::string line);
	
	
private:
	void prn(const Instruction& inst) const;
	void move(const Instruction& inst);
	void add(const Instruction& inst);
	void sub(const Instruction& inst);
	
	bool isHalted;
	int R[5];
	int PC;	
	
};


void print(Instruction& inst);

int analyzeLine(std::string line, Instruction& inst);

bool equalsTo(std::string str, std::string mnem);

bool myIsAlpha(char c);

bool myIsDigit(char c);

/*Coverts lower letter to upper letter*/
char myToUpper(char letter);

/*Converts string to integer*/
int overloadStoi(std::string str);


#endif

