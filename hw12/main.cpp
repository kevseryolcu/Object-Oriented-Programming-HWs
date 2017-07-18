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
/*dont forget to make a makefile*/


const int B_L_A_A = 65; /* The short of BEGIN_LOWER_ALPHA_ASCII*/
const int E_L_A_A = 90; /* The short of END_LOWER_ALPHA_ASCII*/
const int B_U_A_A = 97; /* The short of BEGIN_UPPER_ALPHA_ASCII*/
const int E_U_A_A = 122; /* The short of END_UPPER_ALPHA_ASCII*/
const int B_N_A = 48; /* The short of BEGIN_NUMBER_ASCII*/
const int E_N_A = 57; /* The short of END_NUMBER_ASCII*/
const int NUM_OF_REG = 5;/*Number of register*/


struct Register{
	int reg[NUM_OF_REG] = {0, 0, 0, 0, 0};
};

union rightOperand{
	int reg;
	int constant;
};

/*an assembly code includes - MNEMONIC LEFT_OPERAND, RIGHT_OPERAND*/
struct Instruction{
	string mnemonic;
	int operandL;
	rightOperand operandR;	
	bool hasROperand = false;	/*is it has right operand*/
	bool isRConst = false;		/*is right operand const*/
	bool isLConst = false;		/*is left operand const*/
};

/*Execute instructions*/
int compileInstr(Register* regPtr, const Instruction* inst, int size, int option);

/*MOVE reg const or MOVE reg reg*/
void move(Register* regPtr, Instruction inst);

/*ADD reg const or ADD reg reg*/
void add(Register* regPtr, Instruction inst);

/*SUB reg const or SUB reg reg*/
void sub(Register* regPtr, Instruction inst);

/*PRN reg and PRN const*/
void prn(Register reg, Instruction inst);

/*Prints content of registers*/
void print(Register reg);

/*Prints present instruction and content of registers*/
void print(Register reg, Instruction inst);

/*Converts string to integer*/
int overloadStoi(string str);

/*Counts line number of given file*/
int lineCounter(char fileName[]);

/* Takes assembly code from file and analyzes, 
 * fills instructions to array of instructions	*/
int assemblyAnalyzer(ifstream& inpFile, Instruction *arrayOfInst);

/*Converts lower letter to upper letter*/
char myToUpper(char letter);

int main(int argc, char* argv[])
{		
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
	
	Instruction * arrayOfInst = new Instruction[countLine];
	
	file.open(argv[1]);
	if(!file.is_open())
	{
		cerr << "File could not be opened!" << endl;
		return 1;
	}
	/*Analyzes assmebly codes taken from file*/
	result = assemblyAnalyzer(file, arrayOfInst);
	
	if(result != 0){
		cerr << "Assembly file could not be analyzed!" << endl;
		file.close();
		delete [] arrayOfInst;
		return 1;
	}
	/*Executes the instructions*/
	int x =  compileInstr(&reg, arrayOfInst, countLine, overloadStoi(argv[2]));
	file.close();
	
	delete [] arrayOfInst;

	return 0;
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

/*Execute instructions*/
int compileInstr(Register* regPtr, const Instruction* inst, int size, int option)
{		
	Instruction oldInst;
	oldInst.mnemonic = "EMPTY";		
		
	for(int progCount = 0; progCount < size; progCount++)
	{			
		//cout << "program counter:" <<progCount << endl;
		if(inst[progCount].mnemonic == "MOV")
			move(regPtr, inst[progCount]);
			
		else if(inst[progCount].mnemonic == "ADD")
			add(regPtr, inst[progCount]);
			
		else if(inst[progCount].mnemonic == "SUB"){
			//cout << "subdayım " << endl;
			sub(regPtr, inst[progCount]);
		}	
		else if(inst[progCount].mnemonic == "JMP")
		{
			/*Copies jmp instruction's information for print function*/
			oldInst.mnemonic = "JMP";
			oldInst.operandL = inst[progCount].operandL;
			oldInst.hasROperand = inst[progCount].hasROperand;
			oldInst.isRConst = inst[progCount].isRConst;
			oldInst.isLConst = inst[progCount].isLConst;
			oldInst.operandR.constant = inst[progCount].operandR.constant;
	
			/*if instructionformat is JMP reg const*/
			if(inst[progCount].hasROperand)
			{
				if(regPtr->reg[inst[progCount].operandL-1] != 0)
				{
					if(inst[progCount].operandR.constant-1 <= 0){
						cerr << "For JMP mnemonic; const cannot be negative!" << endl;
						return 1;
					}
					
					/*prog counter jumps gotten constant value*/
					if(inst[progCount].operandR.constant-1 < size)
						progCount = inst[progCount].operandR.constant -1;
				}
			}
			/*if instruction format is JMP const*/
			else{
				/*prog counter jumps gotten constant value*/
				if(inst[progCount].operandL -1 <= 0){
					cerr << "For JMP mnemonic; const cannot be negative!" << endl;
					return 1;
				}
				if(inst[progCount].operandL -1< size)
					progCount = inst[progCount].operandL - 1;
			}
		}	
		else if(inst[progCount].mnemonic == "PRN")
			/*Prints given left operand*/
			prn(*regPtr, inst[progCount]);
		
		/*Halts the program and prints contents of registers*/	
		else if(inst[progCount].mnemonic == "HLT"){
			if(option == 1)
				print(*regPtr, inst[progCount]);
			else
				print(*regPtr);
			return 0;
		}
		
		else{
			cerr << "Undefined instruction in file!" << endl;
			return 1;
		}
		/*Prints each instruction and contents of registers 
		 * while program executing*/
		if(option == 1)
			if(oldInst.mnemonic == "JMP"){
				print(*regPtr, oldInst);
				
				oldInst.mnemonic = "EMPTY";
			}
			else
				print(*regPtr, inst[progCount]);
	}
	/*Prints content of values after program execute*/
	if(option == 0){
		print(*regPtr);
	}
	
	return 0;
}

/*PRN reg and PRN const*/
void prn(Register reg, Instruction inst)
{
	if(inst.isLConst)
		cout << "" << inst.operandL <<endl;
	else
		cout << "R" << inst.operandL << " = " << reg.reg[inst.operandL-1] << endl;
}

/*MOVE reg const or MOVE reg reg*/
void move(Register* regPtr, Instruction inst)
{
	/*if instruction format is MOV reg const*/
	if(inst.isRConst)
		regPtr->reg[inst.operandL-1] = inst.operandR.constant;
	/*if instruction format is MOV reg reg*/
	else
		regPtr->reg[inst.operandL-1] = regPtr->reg[inst.operandR.reg-1];
}

/*ADD reg const or ADD reg reg*/
void add(Register* regPtr, Instruction inst)
{
	/*if instruction format is ADD reg const*/
	if(inst.isRConst)
		regPtr->reg[inst.operandL-1] += inst.operandR.constant;
	/*if instruction format is ADD reg reg*/
	else
		regPtr->reg[inst.operandL-1] += regPtr->reg[inst.operandR.reg-1];
}

/*SUB reg const or SUB reg reg*/
void sub(Register* regPtr, Instruction inst)
{
	/*if instruction format is SUB reg const*/
	if(inst.isRConst)
		regPtr->reg[inst.operandL-1] -= inst.operandR.constant;
	/*if instruction format is SUB reg reg*/
	else
		regPtr->reg[inst.operandL-1] -= regPtr->reg[inst.operandR.reg-1];
}

/*Prints content of registers*/
void print(Register reg)
{
	for(int i = 0; i < NUM_OF_REG; ++i)
		cout << "_ R" << i+1 << " = " << reg.reg[i];
	cout << endl;
}

/*Prints present instruction and content of registers*/
void print(Register reg, Instruction inst)
{
	if(inst.mnemonic == "HLT")
		cout << inst.mnemonic << endl;
		
	else if(inst.mnemonic == "PRN")
	{
		cout << inst.mnemonic << " R" << inst.operandL;
		
	}
	else if(inst.mnemonic == "JMP")
	{
		if(inst.hasROperand){
			cout << inst.mnemonic << " R" << inst.operandL << ", ";
			if(inst.isRConst)
				cout << inst.operandR.constant;
			else 
				cout << " R" << inst.operandR.reg;
		}
		else
			cout << inst.mnemonic << " " << inst.operandL;
	}
	else
	{
		cout << inst.mnemonic << " R" << inst.operandL << ", ";
		if(inst.isRConst)
			cout << inst.operandR.constant;
		else 
			cout << " R" << inst.operandR.reg;
	}
	print(reg);
	cout << endl;
}

/*Coverts lower letter to upper letter*/
char myToUpper(char letter)
{
	if(letter >= B_U_A_A && letter <= E_U_A_A)
		return letter + B_L_A_A - B_U_A_A;
	else
		return letter;
}

/* Takes assembly code from file and analyzes, 
 * fills instructions to array of instructions	*/
int assemblyAnalyzer(ifstream& inpFile, Instruction *arrayOfInst)
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
			for(i = 0; i < (int)(line.length()); ++i)
			{
				if(line[i] == ';')
					break;
					
				/*if line[i] is a letter*/
				if((line[i] >= B_L_A_A && line[i] <= E_L_A_A) ||
				   (line[i] >= B_U_A_A && line[i] <= E_U_A_A))
				{
					/*if nothing was taken*/
					if(k == 0 && i+2 < (int)( line.length() ) )
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
							i+1 < (int)(line.length()) )
					{
						
						if(k == 1){
							arrayOfInst[j].operandL = (int)(line[i+1]-B_N_A);
							
							/*PRN takes just one operand*/
							if(arrayOfInst[j].mnemonic == "PRN")
								k = 3;
							else
								k = 2;
							++i;
						}
						else if(k == 2){
							arrayOfInst[j].operandR.reg = (int)(line[i+1]-B_N_A);
							k = 3;
							++i;
						}
						else{
							cerr << "Unexpected line format!" << endl;
							return 1;
						}
					}
				}
				/*If line[i] is a number*/
				else if(line[i] >= B_N_A && line[i] <= E_N_A)
				{
					string valueOfConstStr;
					int valueOfConst;
					int beginNumbAdd = i;
					int endNumbAdd;
					bool isNumbNegative = false;
					
					if(line[i-1] == '-')
						isNumbNegative = true;
					
					while(i < (int)(line.length()) && line[i] >= B_N_A && 
						  line[i] <= E_N_A)
						++i;
	
					endNumbAdd = i;
					valueOfConstStr = line.substr(beginNumbAdd, endNumbAdd - beginNumbAdd);
					
					valueOfConst = overloadStoi(valueOfConstStr);
					if(isNumbNegative)
						valueOfConst = -valueOfConst;
					
					if(k > 3 && k < 1)
					{
						cout << "Unexpected line format!" << endl;
						return 1;
					}
					else if(k == 2)
					{
						arrayOfInst[j].isRConst = true;
						arrayOfInst[j].hasROperand = true;
						arrayOfInst[j].operandR.constant = valueOfConst;
						k = 3;
					}
					else if(k == 1)
					{
						arrayOfInst[j].isLConst = true;
						arrayOfInst[j].operandL = valueOfConst;
						k = 3;
					}
				}			
			}
			
			if(k == 3){
				k = 0;
				j++;
			}
			
			line.clear();
		}
	}
	return 0;
}

/*___________________________________________________________________ */
/*                                                                    */
/*							 End of HW1								  */
/*___________________________________________________________________ */
