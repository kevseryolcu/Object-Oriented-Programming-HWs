#include "CPU.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

/*CPU constructor*/
CPU::CPU()
{
	isHalted = false;
	PC = 1;	
	R[0] = 0;
	R[1] = 0;
	R[2] = 0;
	R[3] = 0;
	R[4] = 0;	
}

/*Sets content of register with given numbers*/
void CPU::setRegisters(int r1, int r2, int r3, int r4, int r5)
{
	R[0] = r1;
	R[1] = r2;
	R[2] = r3;
	R[3] = r4;
	R[4] = r5;
}

/*Gets content of given register*/
int CPU::getR(int regNumber) const{	return R[regNumber-1];	}

/*Sets content of given register*/
void CPU::setR(int regNumber, int content) 
{
	if(0 < regNumber-1 && regNumber-1 < 5){
		R[regNumber-1] = content;	
		return;
	}
	cerr << "Register number could be between 5 to 1!" << endl;
	exit(1);
}

/*Sets PC*/
void CPU::setPC(int number)
{
	if(0 < number){
		PC = number;
		return;
	}
	cerr << "PC couldn't be changed" << endl;
	exit(1);
}

/*Prints all the registers and the PC*/
void CPU::print() const
{
	cout << "PC : " << PC;
	cout << ", ";
	
	for(int i = 0; i < 5; ++i)
		cout << "R" << i+1 << " : " << R[i] << "  ";	
	cout <<endl;
}

/*Takes a string that contains an instruction line, executes it and 
 * advances the PC accordingly*/
int CPU::execute(string line)
{
	Instruction inst;
	int result = analyzeLine(line, inst);
	if(result == 1)
		return 1;
	if(equalsTo(inst.mnemonic, "MOV"))
		move(inst);
	else if(equalsTo(inst.mnemonic, "ADD"))
		add(inst);
	else if(equalsTo(inst.mnemonic, "SUB"))
		sub(inst);
	else if(equalsTo(inst.mnemonic, "JMP")){
		if(!inst.hasROperand)
			PC = inst.operandL.constant-1;
		else if(R[inst.operandL.reg-1] == 0)
				PC = inst.operandR.constant-1;
	}			
	else if(equalsTo(inst.mnemonic, "PRN"))
		prn(inst);
	else if(equalsTo(inst.mnemonic, "HLT"))
		isHalted = true;
	
	PC += 1;
		
	return 0;
}

/*Returns true if CPU program was halted*/
bool CPU::halted(){return isHalted;}


/*PRN reg, and PRN const*/
void CPU::prn(const Instruction& inst) const
{
	if(inst.mnemonic == "PRN")
		switch(inst.kindOfL)
		{
			case 'r': cout << "R" << inst.operandL.reg << " = " 
						   << R[inst.operandL.reg-1] << endl;
				break;
			case 'c': cout << inst.operandL.constant << endl;
				break;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
}

/*MOVE reg const or MOVE reg reg*/
void CPU::move(const Instruction& inst)
{
	if(inst.kindOfL == 'r')
	{
		/*if instruction format is MOV reg reg*/
		if(inst.kindOfR == 'r'){
			R[inst.operandR.reg-1] = R[inst.operandL.reg-1];
		}	
		/*if instruction format is MOV reg const*/
		else if(inst.kindOfR == 'c')
			R[inst.operandL.reg-1] = inst.operandR.constant;
	}
	else
	{
		cerr << "Undefined MOV instruction format!" << endl;
		return; 
	}
	
}


/*ADD reg const or ADD reg reg*/
void CPU::add(const Instruction& inst)
{
	int temp;
	if(inst.mnemonic == "ADD" && inst.kindOfL == 'r')
		switch(inst.kindOfR)
		{
			/*if instruction format is ADD reg reg*/
			case 'r': temp = R[inst.operandL.reg-1] + R[inst.operandR.reg-1];
					  R[inst.operandL.reg-1] = temp;
				break;
				
			/*if instruction format is ADD reg const*/
			case 'c': temp = R[inst.operandL.reg-1] + inst.operandR.constant;
					  R[inst.operandL.reg-1] = temp;
				break;
			default:
				cerr << "Undefined ADD instruction format!" << endl;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
}

/*SUB reg const or SUB reg reg*/
void CPU::sub(const Instruction& inst)
{
	int temp;
	if(inst.mnemonic == "SUB" && inst.kindOfL == 'r')
		switch(inst.kindOfR)
		{
			/*if instruction format is SUB reg reg*/
			case 'r': temp = R[inst.operandL.reg-1] - R[inst.operandR.reg-1];
					  R[inst.operandL.reg-1] = temp;
				break;
				
			/*if instruction format is SUB reg const*/
			case 'c': temp = R[inst.operandL.reg-1] - inst.operandR.constant;
					  R[inst.operandL.reg-1] = temp;
				break;
			default:
				cerr << "Undefined SUB instruction format!" << endl;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
}



/*Analayzes given instruction line, stores in a Instruction object*/
int analyzeLine(string line, Instruction& inst)
{
	int k = 0;
	
	/*-if k = 0, nothing has taken yet
	 *-if k = 1, only mnemonic was taken
	 *-if k = 2, mnemonic and left operand were taken
	 *-if k = 3, mnemonic, left and right operands were taken 
	 * or taking instructions was completed
	 * (for like HLT instruction)*/
	 
	for(int i = 0; i < (int)(line.size()); ++i)
	{
		if(line[i] == ';' && k != 3)
		{
			cerr << "Unexpected instruction format because of char \';\'!" << endl;
			return 1;
		}
		if(line[i] == ',' && k != 2)
		{
			cerr << "Unexpected instruction format because of char \',\'!" << endl;
			return 1;
		}
		/*if line[i] is an alphabet*/
		if( myIsAlpha(line[i]))
		{
			if(k == 0 && i+2 < (int)(line.size()))
			{
				if( equalsTo(line, "MOV") )
				{
					inst.mnemonic = "MOV";
					inst.hasROperand = true;
					k = 1;
					i += 2;
				}
				else if( equalsTo(line, "ADD") )
				{
					inst.mnemonic = "ADD";
					inst.hasROperand = true;
					k = 1;
					i += 2;
				}
				else if( equalsTo(line, "SUB") )
				{
					inst.mnemonic = "SUB";
					inst.hasROperand = true;
					k = 1;
					i += 2;
				}
				else if( equalsTo(line, "JMP") )
				{
					inst.mnemonic = "JMP";
					k = 1;
					i += 2;
				}
				else if( equalsTo(line, "PRN") )
				{
					inst.mnemonic = "PRN";
					k = 1;
					i += 2;
				}
				else if( equalsTo(line, "HLT") )
				{
					inst.mnemonic = "HLT";
					return 0;
				}
				else
				{
					cerr << "Unexpected mnemonic!" << endl;
					return 1;
				}
			}
			/*if line[i] is reg*/
			else if(myToUpper(line[i]) == 'R' && i+1 < (int)(line.size()))
			{
				if(!myIsDigit(line[i+1]))
				{
					cerr << "Unexpected register number!" << endl;
					return 1;
				}
				if(k == 1)
				{
					inst.operandL.reg = static_cast<int>(line[i+1]-ZERO);
					inst.kindOfL = 'r';
					if(inst.mnemonic == "JMP")
						inst.hasROperand = true;
					else if(inst.mnemonic == "PRN")
						return 0;
					k = 2;
					i += 1;
				}
				else if(k == 2)
				{
					inst.kindOfR = 'r';
					inst.operandR.reg = static_cast<int>(line[i+1]-ZERO);
					return 0;			
				}
				else
				{
					cerr << "Error!!!" << endl;
					return 1;
				}
			}
		}
		/*if line[i] is an digit*/
		else if( myIsDigit(line[i]) )
		{
			if(k < 1 || k > 2)
			{
				cerr << "Wrong instruction!" << endl;
				return 1;				
			}
			
			string valueOfConstStr;
			int valueOfConst;
			int beginNumbAdd = i;/*begining of number*/
			int endNumbAdd;		 /*end of number*/
			bool isNumbNegative = false;
			
			/*is number negative*/
			if(i-1 < static_cast<int>(line.length()) && line[i-1] == '-')
				isNumbNegative = true;
			
			/*counts end of number*/
			while(i < static_cast<int>(line.length()) && myIsDigit(line[i]))
				++i;

			endNumbAdd = i;
			/*Substruct number from line*/
			valueOfConstStr = line.substr(beginNumbAdd, endNumbAdd - beginNumbAdd);
			
			/*converts number from string to integer*/
			valueOfConst = overloadStoi(valueOfConstStr);
			if(isNumbNegative)
				valueOfConst = -valueOfConst;
			
			
			else if(k == 1)
			{
				inst.operandL.constant = valueOfConst;
				inst.kindOfL = 'c';
				if(equalsTo(inst.mnemonic, "PRN"))
					return 0;
				else if(equalsTo(inst.mnemonic, "JMP") && !inst.hasROperand)
					return 0;
			}
			else if(k == 2)
			{
				inst.operandR.constant = valueOfConst;
				inst.kindOfR = 'c';
				return 0;
			}
		}
	
	}
	return 0;
}

/*if two string equals to each other returns true*/
bool equalsTo(string str, string mnem)
{
	for(int i = 0; i < (int)mnem.length(); ++i)	
		if(str[i] != mnem[i])
			return false;

	return true;
}

/*If a character is a alphabet, returns true*/
bool myIsAlpha(char c)
{
	c = myToUpper(c);
	
	if(UPA <= c && c <= UPZ)
	   return true;
	
	return false;
}

/*If a character is a digit, returns true*/
bool myIsDigit(char c)
{
	if(ZERO <= c && c <= NINE)
		return true;
 
	return false;
}

/*Converts string to integer*/
int overloadStoi(string str)
{
    int result = 0;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
		result *= 10;
		result += static_cast<int>(str[i] - '0');
	}
	return result;
}

/*Coverts lower letter to upper letter*/
char myToUpper(char letter)
{
	if(letter >= LOWA && letter <= LOWZ)
		return letter -(LOWA - UPA);
	
	return letter;
}

/*Prints present instruction*/
void print(Instruction& inst)
{
	if(inst.mnemonic == "HLT")
		cout << inst.mnemonic << endl;
		
	else if(inst.mnemonic == "PRN")
	{
		cout << inst.mnemonic << " ";
		if(inst.kindOfL == 'c')
			cout << inst.operandL.constant << endl;
		else
			cout << "R" << inst.operandL.reg << endl;
		
	}
	else if(inst.mnemonic == "JMP")
	{
		if(inst.hasROperand){
			cout << inst.mnemonic << " R" << inst.operandL.reg << ", "
				 << inst.operandR.constant << endl;
		}
		else
			cout << inst.mnemonic << " " << inst.operandL.constant << endl;
	}
	else if(inst.mnemonic == "MOV")
	{
		cout << inst.mnemonic << " ";
		if(inst.kindOfL == 'r')
		{
			cout << "R" << inst.operandL.reg << " , ";
			/*if instruction format is MOV reg reg*/
			if(inst.kindOfR == 'r')
				cout << "R"<< inst.operandR.reg;
			/*if instruction format is MOV reg address*/
			else if(inst.kindOfR == 'c')
				cout << inst.operandR.constant;
			cout << endl;
		}
	}
	else
	{
		cout << inst.mnemonic << " R" << inst.operandL.reg << ", ";
		if(inst.kindOfR == 'r')
			cout << " R" << inst.operandR.reg << endl;
		else if(inst.kindOfR == 'c')
			cout << inst.operandR.constant << endl;
	}
	cout << endl;
}



