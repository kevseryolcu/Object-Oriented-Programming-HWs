/*____________________________________________________________________*/
/*                                                                    */
/*					  131044072 KEVSER YOLCU						  */
/*	HW1 * Simple CPU Program										  *
 * 		- Takes file name from console which includes assembly code	  *
 * 		- Analyzes the file and execute instructions				  */
/*___________________________________________________________________ */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


const int LOWA = 97;    /* ASCII 'a' */
const int LOWZ = 122;    /* ASCII 'z' */
const int UPA = 65;    /* ASCII 'A' */
const int UPZ = 90;   /* ASCII 'Z' */
const int ZERO = 48;      /* ASCII '0' */
const int NINE = 57;      /* ASCII '9' */
const int NUM_OF_REG = 5;  /*Number of register*/
const int SIZE_OF_MEM = 50; /*Size of memory*/
const int MAX_INST = 200;	/*Maximum instruction*/

struct Register{
	int reg[NUM_OF_REG] = {0, 0, 0, 0, 0};
};
struct Memory{
	int mem[SIZE_OF_MEM];
};

union Operand{
	int reg;
	int address;
	int constant;
};

/*an assembly code includes - MNEMONIC LEFT_OPERAND, RIGHT_OPERAND*/
struct Instruction{
	string mnemonic;
	Operand operandR;	
	Operand operandL;
	bool hasROperand = false;	/*does it has right operand*/
	char kindOfR;				
	char kindOfL;				/* if operand constant, 
								   then kindOfR or kindOfL 'c';
								   if register, then 'r';
								   if address, then 'a'      */
};

/*Prints content of registers*/
void print(Register reg);

/*Prints content of memory*/
void print(Memory m);

/*Prints present instruction*/
void print(Register reg, Instruction inst, Memory m);

/*PRN reg, PRN address and PRN const*/
void prn(Register reg, Instruction inst, Memory m);

/*MOVE reg const or MOVE reg reg*/
void move(Register* regPtr, Instruction inst, Memory * m);

/*ADD reg const or ADD reg reg*/
void add(Register* regPtr, Instruction inst, Memory m);

/*SUB reg const or SUB reg reg*/
void sub(Register* regPtr, Instruction inst, Memory m);

/*Counts line number of given file*/
int lineCounter(char fileName[]);

/*Converts string to integer*/
int overloadStoi(string str);

/*Converts lower letter to upper letter*/
char myToUpper(char letter);

/*Copies instruction*/
void copyInstruction(Instruction* to, Instruction from);

/* Takes assembly code from file and analyzes, 
 * fills instructions to array of instructions	*/
int assemblyAnalyzer(ifstream& inpFile, Instruction *arrayOfInst, Register r);

/*Execute instructions*/
int compileInstr(Memory * m, Register* regPtr, const Instruction* inst, int size, int option);

int main(int argc, char* argv[])
{
	Memory myMemory;
	
	for(int i = 0; i < SIZE_OF_MEM; ++i)
	{
		myMemory.mem[i] = 0;		
	}
	
	Register reg;						
	string line;
	ifstream file;
	int countLine = 0,
		result;
	
	if(argc != 3)
	{	
		cerr << "The compilation format is ./prog fileName option" << endl;
		return 1;
	}
	
	countLine = lineCounter(argv[1]);
	if(countLine > MAX_INST)
	{
		cerr << "File has too many instruction!" << endl;
		return 1;
	}
	
	Instruction * arrayOfInst = new Instruction[countLine];
	
	file.open(argv[1]);
	if(!file.is_open())
	{
		cerr << "File could not be opened!" << endl;
		return 1;
	}
	/*Analyzes assmebly codes taken from file*/
	result = assemblyAnalyzer(file, arrayOfInst,reg);
	
	if(result != 0){
		cerr << "Assembly file could not be analyzed!" << endl;
		file.close();
		delete [] arrayOfInst;
		return 1;
	}
	/*Executes the instructions*/
	int x =  compileInstr(&myMemory, &reg, arrayOfInst, countLine, overloadStoi(argv[2]));
	file.close();
	
	
	delete [] arrayOfInst;
	
	return 0;
}

/* Takes assembly code from file and analyzes, 
 * fills instructions to array of instructions	*/
int assemblyAnalyzer(ifstream& inpFile, Instruction *arrayOfInst, Register r)
{
	string line;
	int i,
		j = 0,	/*number of instruction*/
		
		k = 0;	/*-if k = 0, nothing has taken yet
				 *-if k = 1, only mnemonic was taken
				 *-if k = 2, mnemonic and left operand were taken
				 *-if k = 3, mnemonic, left and right operands were taken 
				 * or taking instructions was completed
				 * (for like HLT instruction)*/
		
	while(!inpFile.eof())
	{
		getline(inpFile, line);
		if(!line.empty())
		{ 
			for(i = 0; i < static_cast<int>(line.length()); ++i)
			{
				if(line[i] == ';')
					break;
					
				/*if line[i] is a letter*/
				if((line[i] >= LOWA && line[i] <= LOWZ) ||
				   (line[i] >= UPA && line[i] <= UPZ))
				{
					/*if nothing was taken*/
					if(k == 0 && i+2 < static_cast<int>( line.length() ) )
					{
						if(myToUpper(line[i])  == 'M' &&
						   myToUpper(line[i+1]) == 'O' &&
						   myToUpper(line[i+2]) == 'V' )
						{
							arrayOfInst[j].mnemonic = "MOV";
							arrayOfInst[j].hasROperand = true;
							k = 1;
							i += 2;
						}
						else if(myToUpper(line[i]) == 'A' &&
								myToUpper(line[i+1]) == 'D' &&
								myToUpper(line[i+2]) == 'D' )
						{
							arrayOfInst[j].mnemonic = "ADD";
							arrayOfInst[j].hasROperand = true;
							k = 1;
							i += 2;
						}
						else if(myToUpper(line[i]) == 'S' &&
								myToUpper(line[i+1]) == 'U' &&
								myToUpper(line[i+2]) == 'B' )
						{
							arrayOfInst[j].mnemonic = "SUB";
							arrayOfInst[j].hasROperand = true;
							k = 1;
							i += 2;
						}
						else if(myToUpper(line[i]) == 'J' &&
								myToUpper(line[i+1]) == 'M' &&
								myToUpper(line[i+2]) == 'P' )
						{
							arrayOfInst[j].mnemonic = "JMP";
							k = 1;
							i += 2;
						}
						else if(myToUpper(line[i]) == 'J' &&
								myToUpper(line[i+1]) == 'P' &&
								myToUpper(line[i+2]) == 'N' )
						{
							arrayOfInst[j].mnemonic = "JPN";
							k = 1;
							i += 2;
						}
						else if(myToUpper(line[i]) == 'P' &&
								myToUpper(line[i+1]) == 'R' &&
								myToUpper(line[i+2]) == 'N' )
						{
							arrayOfInst[j].mnemonic = "PRN";
							k = 1;
							i += 2;
						}
						else if(myToUpper(line[i]) == 'H' &&
								myToUpper(line[i+1]) == 'L' &&
								myToUpper(line[i+2]) == 'T' )
						{
							arrayOfInst[j].mnemonic = "HLT";
							k = 3;
							i += 2;
						}
					}
					
					/*for register*/
					else if(myToUpper(line[i]) == 'R' &&
							i+1 < static_cast<int>(line.length()) )
					{
						
						if(k == 1)
						{
							arrayOfInst[j].kindOfL = 'r';
							arrayOfInst[j].operandL.reg = static_cast<int>(line[i+1]-ZERO);/*ZERO ASCII zero*/
							
							/*PRN takes just one operand*/
							if(arrayOfInst[j].mnemonic == "PRN")
								k = 3;
							else
								k = 2;
							++i;
						}
						else if(k == 2){
							arrayOfInst[j].kindOfR = 'r';
							arrayOfInst[j].operandR.reg = static_cast<int>(line[i+1]-ZERO);
							k = 3;
							++i;
						}
						else
						{
							cerr << "Unexpected line2 format!" << endl;
							return 1;
						}
					}
				}
				
				else if(line[i] == '#' && i+1 < static_cast<int>(line.length()))
				{
					if(line[i+1] >= ZERO && line[i+1] <= NINE)
					{
						++i;
						string valueOfConstStr;
						int valueOfConst;
						int beginNumbAdd = i;
						int endNumbAdd;
						
						while(i < static_cast<int>(line.length()) && line[i] >= ZERO && 
							  line[i] <= NINE)
							++i;
		
						endNumbAdd = i;
						valueOfConstStr = line.substr(beginNumbAdd, endNumbAdd - beginNumbAdd);
						
						valueOfConst = overloadStoi(valueOfConstStr);
						if(k < 1)
						{
							cout << "Unexpected line format!" << endl;
							return 1;
						}
						else if(k == 2)
						{
							arrayOfInst[j].kindOfR = 'a';
							arrayOfInst[j].hasROperand = true;
							arrayOfInst[j].operandR.address = valueOfConst;
							k = 3;
						}
						else if(k == 1)
						{
							arrayOfInst[j].kindOfL = 'a';
							arrayOfInst[j].operandL.address = valueOfConst;
							k = 2;
							if(arrayOfInst[j].mnemonic == "PRN")
								k = 3;
						}
					}
					else{
						cerr << "Unknown memory address!" << endl;
						return 1;
					}	
				}
				
				/*If line[i] is a number*/
				else if(line[i] >= ZERO && line[i] <= NINE)
				{
					string valueOfConstStr;
					int valueOfConst;
					int beginNumbAdd = i;
					int endNumbAdd;
					bool isNumbNegative = false;
					
					if(i-1 < static_cast<int>(line.length()) && line[i-1] == '-')
						isNumbNegative = true;
					
					while(i < static_cast<int>(line.length()) && line[i] >= ZERO && 
						  line[i] <= NINE)
						++i;
	
					endNumbAdd = i;
					valueOfConstStr = line.substr(beginNumbAdd, endNumbAdd - beginNumbAdd);
					
					valueOfConst = overloadStoi(valueOfConstStr);
					if(isNumbNegative)
						valueOfConst = -valueOfConst;
					
					if(k > 3 || k < 1)
					{
						cout << "Unexpected line format!" << endl;
						return 1;
					}
					else if(k == 2)
					{
						arrayOfInst[j].kindOfR = 'c';
						arrayOfInst[j].hasROperand = true;
						arrayOfInst[j].operandR.constant = valueOfConst;
						k = 3;
					}
					else if(k == 1)
					{
						arrayOfInst[j].kindOfL = 'c';
						arrayOfInst[j].operandL.constant = valueOfConst;
						k = 2;
						if(arrayOfInst[j].mnemonic == "JMP")
							k = 3;
					}
				}			
			}
			
			if(k == 3)
				j++;
			k = 0;
			line.clear();
		}
	}
	return 0;
}


/*Execute instructions*/
int compileInstr(Memory * m, Register* regPtr, const Instruction* inst, int size, int option)//////////////////////////jumpi degistir
{		
	Instruction oldInst;
	oldInst.mnemonic = "EMPTY";		
		
	for(int progCount = 0; progCount < size; progCount++)
	{			
		if(inst[progCount].mnemonic == "MOV")
			move(regPtr, inst[progCount], m);
			
		else if(inst[progCount].mnemonic == "ADD")
			add(regPtr, inst[progCount], *m);
			
		else if(inst[progCount].mnemonic == "SUB")
			sub(regPtr, inst[progCount], *m);
			
		else if(inst[progCount].mnemonic == "JMP")
		{
			/*Copies jmp instruction's information for print function*/
			copyInstruction(&oldInst, inst[progCount]);
	
			/*if instructionformat is JMP reg lineAddress*/
			if(inst[progCount].hasROperand)
			{
				if(regPtr->reg[inst[progCount].operandL.reg-1] == 0)
				{
					if(inst[progCount].operandR.constant-1 <= 0)
					{
						cerr << "For JMP mnemonic; lineAdress cannot be negative or zero!" << endl;
						return 1;
					}
					/*prog counter jumps gotten constant value*/
					if(inst[progCount].operandR.constant-1 < size)
						progCount = inst[progCount].operandR.constant -1;
				}
			}
			
			/*if instruction format is JMP lineAddress*/
			else
			{
				/*prog counter jumps gotten constant value*/
				if(inst[progCount].operandL.constant -1 <= 0)
				{
					cerr << "For JMP mnemonic; lineAdress cannot be negative or zero!" << endl;
					return 1;
				}
				if(inst[progCount].operandL.constant -1< size)
					progCount = inst[progCount].operandL.constant - 1;
			}
		}	
		else if(inst[progCount].mnemonic == "JPN")
		{
			/*Copies jpn information of instruction for print function*/
			copyInstruction(&oldInst, inst[progCount]);
	
			/*if instruction format is JPN reg lineAddress*/
			if(regPtr->reg[inst[progCount].operandL.reg-1] <= 0)
			{
				if(inst[progCount].operandR.constant-1 <= 0)
				{
					cerr << "For JPN mnemonic; lineAdress cannot be negative or zero!" << endl;
					return 1;
				}
				/*prog counter jumps gotten constant value*/
				if(inst[progCount].operandR.constant-1 < size)
					progCount = inst[progCount].operandR.constant -1;
			}
			
		}
		else if(inst[progCount].mnemonic == "PRN")
			/*Prints given left operand*/
			prn(*regPtr, inst[progCount], *m);
		
		/*Halts the program and prints contents of registers*/	
		else if(inst[progCount].mnemonic == "HLT")
		{
			if(option == 1)
			{
				print(*regPtr, inst[progCount], *m);
				print(*regPtr);
			}
			else if(option == 2)
			{
				print(*regPtr, inst[progCount], *m);
				print(*regPtr);
				print(*m);
			}
			/*Prints content of values after program execute*/
			else if(option == 0)
				print(*regPtr);
			else
			{
				cerr << "Option must be 0 or 1 or 2!" << endl;
				return 1;
			}
			return 0;
		}
		
		else
		{
			cerr << "Undefined instruction in file!" << endl;
			return 1;
		}
		
		/*Prints each instruction and contents of registers 
		 * while program executing*/
		if(option == 1 || option == 2)
		{
			if(oldInst.mnemonic == "JMP" && oldInst.mnemonic == "JPN")
			{
				print(*regPtr, oldInst, *m);
				oldInst.mnemonic = "EMPTY";
			}
			else
				print(*regPtr, inst[progCount], *m);
			print(*regPtr);
			
			if(option == 2)
				print(*m);
		}
	}
	
	
	return 0;
}

/*MOVE reg const or MOVE reg reg*/
void move(Register* regPtr, Instruction inst, Memory * m)
{
	if(inst.kindOfL == 'r')
	{
		/*if instruction format is MOV reg reg*/
		if(inst.kindOfR == 'r')
			regPtr->reg[inst.operandR.reg-1] = regPtr->reg[inst.operandL.reg-1];
			
		/*if instruction format is MOV reg address*/
		else if(inst.kindOfR == 'a')
			m->mem[inst.operandR.address] = regPtr->reg[inst.operandL.reg-1];
			
		/*if instruction format is MOV reg const*/
		else if(inst.kindOfR == 'c')
			regPtr->reg[inst.operandL.reg-1] = inst.operandR.constant;
	}
	
	else if(inst.kindOfL == 'a')
	{
		/*if instruction format is MOV address reg*/
		if(inst.kindOfR == 'r')
			regPtr->reg[inst.operandR.reg-1] = m->mem[inst.operandL.address];
			
		/*if instruction format is MOV address const*/
		else if(inst.kindOfR == 'c')
			m->mem[inst.operandL.address] = inst.operandR.constant;
	}
	
	else
	{
		cerr << "Undefined MOV instruction format!" << endl;
		return; 
	}
}

/*Prints content of memory*/
void print(Memory m)
{
	for(int i = 0, j = 0; i < SIZE_OF_MEM; ++i, ++j){
		cout << "Content of #" << i << " = " << m.mem[i] << "   ";
		if(j == 4){
			cout << endl;
			j = -1;
		}
	}
}

/*Prints content of registers*/
void print(Register reg)
{
	cout << "Registers:";
	for(int i = 0; i < NUM_OF_REG; ++i)
		cout << " R" << i+1 << " = " << reg.reg[i] << ",";
	cout << endl;
}

/*Prints present instruction*/
void print(Register reg, Instruction inst, Memory m)
{
	if(inst.mnemonic == "HLT ")
		cout << inst.mnemonic << endl;
		
	else if(inst.mnemonic == "PRN ")
	{
		cout << inst.mnemonic;
		prn(reg, inst, m);
		
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
	else if(inst.mnemonic == "JPN")
	{
		cout << inst.mnemonic << " R" << inst.operandL.reg << ", "
			 << inst.operandR.constant << endl;
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
			/*if instruction format is MOV reg const*/
			else if(inst.kindOfR == 'a')
				cout << "#" << inst.operandR.address;
		}
		else if(inst.kindOfL == 'a')
		{
			cout << "#" << inst.operandL.address << " , ";
			/*if instruction format is MOV address reg*/
			if(inst.kindOfR == 'r')
				cout << "R"<< inst.operandR.reg;
			/*if instruction format is MOV address const*/
			else if(inst.kindOfR == 'c'){
				cout << inst.operandR.constant;
			}
		}
	}
	else
	{
		cout << inst.mnemonic << " R" << inst.operandL.reg << ", ";
		if(inst.kindOfR == 'r')
			cout << " R" << inst.operandR.reg << endl;
		else if(inst.kindOfR == 'a')
			cout << "#" << inst.operandR.address << endl;
		else if(inst.kindOfR == 'c')
			cout << inst.operandR.constant << endl;
	}
	cout << endl;
}

/*ADD reg const or ADD reg reg*/
void add(Register* regPtr, Instruction inst, Memory m)
{
	if(inst.mnemonic == "ADD" && inst.kindOfL == 'r')
		switch(inst.kindOfR)
		{
			/*if instruction format is ADD reg reg*/
			case 'r': regPtr->reg[inst.operandL.reg-1] += regPtr->reg[inst.operandR.reg-1];				break;
			/*if instruction format is ADD reg address*/
			case 'a': regPtr->reg[inst.operandL.reg-1] += m.mem[inst.operandR.address];
			//cout<<"hey"<<regPtr->reg[inst.operandL.reg-1]<<endl<<"ho"<<m.mem[inst.operandR.address]<<endl;/////////////
				break;
			/*if instruction format is ADD reg const*/
			case 'c': regPtr->reg[inst.operandL.reg-1] += inst.operandR.constant;
				break;
			default:
				cerr << "Undefined ADD instruction format!" << endl;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
}

/*SUB reg const or SUB reg reg*/
void sub(Register* regPtr, Instruction inst, Memory m)
{
	if(inst.mnemonic == "SUB" && inst.kindOfL == 'r')
		switch(inst.kindOfR)
		{
			/*if instruction format is SUB reg reg*/
			case 'r': regPtr->reg[inst.operandL.reg-1] -= regPtr->reg[inst.operandR.reg-1];
				break;
			/*if instruction format is SUB reg address*/
			case 'a': regPtr->reg[inst.operandL.reg-1] -= m.mem[inst.operandR.address];
				break;
			/*if instruction format is SUB reg const*/
			case 'c': regPtr->reg[inst.operandL.reg-1] -= inst.operandR.constant;
				break;
			default: 
				cerr << "Undefined SUB instruction format!" << endl;
				return;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;

}

/*PRN reg, PRN address and PRN const*/
void prn(Register reg, Instruction inst, Memory m)
{
	if(inst.mnemonic == "PRN")
		switch(inst.kindOfL)
		{
			case 'r': cout << "R" << inst.operandL.reg << " = " 
						   << reg.reg[inst.operandL.reg-1] << endl;
				break;
			case 'a': cout << "Content of #" << inst.operandL.address << " = "
						   << m.mem[inst.operandL.address] << endl;
				break;
			case 'c': cout << inst.operandL.constant << endl;
				break;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
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

void copyInstruction(Instruction* to, Instruction from)
{
	to->mnemonic = from.mnemonic;
	to->hasROperand = from.hasROperand;
	to->kindOfR = from.kindOfR;
	to->kindOfL = from.kindOfL;
	if(from.hasROperand)
		switch(from.kindOfR)
		{
			case 'r': to->operandR.reg = from.operandR.reg;
				break;
			case 'a': to->operandR.address = from.operandR.constant;
				break;
			case 'c': to->operandR.constant = from.operandR.constant;
				break;
		}
	switch(from.kindOfL)
	{
		case 'r': to->operandL.reg = from.operandL.reg;
			break;
		case 'a': to->operandL.address = from.operandL.constant;
			break;
		case 'c': to->operandL.constant = from.operandL.constant;
			break;
	}
}

/*Counts line number of given file*/
int lineCounter(char fileName[])
{
	string line;
	ifstream file;
	int countLine = 0;
	
	file.open(fileName);
	
	if(!file.is_open())
	{
		cerr << "File could not be opened!" << endl;
		return 1;
	}
	while(!file.eof())
	{
		getline(file, line); 
		if(!line.empty())
			countLine += 1;	
		line.clear();
	}
	file.close();
	return countLine;
}


