#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include "AssistantFunctions.h"

using namespace std;

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
				if( equalsTo(myStringToUpper(line), "MOV") )
				{
					inst.mnemonic = "MOV";
					inst.hasROperand = true;
					k = 1;
					i += 2;
				}
				else if( equalsTo(myStringToUpper(line), "ADD") )
				{
					inst.mnemonic = "ADD";
					inst.hasROperand = true;
					k = 1;
					i += 2;
				}
				else if( equalsTo(myStringToUpper(line), "SUB") )
				{
					inst.mnemonic = "SUB";
					inst.hasROperand = true;
					k = 1;
					i += 2;
				}
				else if( equalsTo(myStringToUpper(line), "JMP") )
				{
					inst.mnemonic = "JMP";
					k = 1;
					i += 2;
				}
				else if( equalsTo(myStringToUpper(line), "JPN") )
				{
					inst.mnemonic = "JPN";
					inst.hasROperand = true;
					k = 1;
					i += 2;
				}
				else if( equalsTo(myStringToUpper(line), "PRN") )
				{
					inst.mnemonic = "PRN";
					k = 1;
					i += 2;
				}
				else if( equalsTo(myStringToUpper(line), "HLT") )
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
					//cout << "test reg: " << inst.operandR.reg << endl;////////////////////////////////
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
				k = 3;
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
		
		/*If line[i] #*/
		else if(line[i] == '#' && i+1 < (int)(line.size()))
		{
			if(k < 1 || k > 2)
			{
				cerr << "Wrong instruction!" << endl;
				return 1;				
			}
			
			++i;
			
			string valueOfConstStr;
			int valueOfConst;
			int beginNumbAdd = i;/*begining of number*/
			int endNumbAdd;		 /*end of number*/
			
			/*counts end of number*/
			while(i < static_cast<int>(line.length()) && myIsDigit(line[i]))
				++i;

			endNumbAdd = i;
			/*Substruct number from line*/
			valueOfConstStr = line.substr(beginNumbAdd, endNumbAdd - beginNumbAdd);
			
			/*converts number from string to integer*/
			valueOfConst = overloadStoi(valueOfConstStr);
			
			if(k == 1)
			{
				inst.operandL.address = valueOfConst;
				inst.kindOfL = 'a';
				k = 2;
				if(equalsTo(inst.mnemonic, "PRN"))
					return 0;
			}
			else if(k == 2)
			{
				inst.operandR.address = valueOfConst;
				inst.kindOfR = 'a';
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

/*if letters of string is lower alphabet, converts them upper*/
std::string myStringToUpper(std::string& inp)
{
	for(int i = 0; i < (int)inp.size(); ++i)
	{
		if(inp[i] >= LOWA && inp[i] <= LOWZ)
			inp[i] =  inp[i] -(LOWA - UPA);
	}
	return inp;
}
