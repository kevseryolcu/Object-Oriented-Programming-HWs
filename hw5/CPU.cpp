#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "CPU.h"
#include "AssistantFunctions.h"

using namespace std;

/*CPU constructor*/
CPU::CPU()
{
	option = 0;
	isHalted = false;
	PC = 1;	
	R[0] = 0;
	R[1] = 0;
	R[2] = 0;
	R[3] = 0;
	R[4] = 0;	
}

/*CPU constructor with option*/
CPU::CPU(int opt):CPU()
{
	setOption(opt);
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
int CPU::getR(int regNumber) const
{	
	if(0 > regNumber || regNumber > 5){
		cerr << "Register number must be between 1 to 5!" << endl;
		exit(1);
	}
	return R[regNumber-1];	
}

/*Sets content of given register*/
void CPU::setR(int regNumber, int content) 
{
	if(0 <= regNumber-1 && regNumber-1 < 5){
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

/*Sets isHalted*/
void CPU::setIsHalted(bool b)
{
	isHalted = b; 
}

/*Sets option*/
void CPU::setOption(int opt)
{
	if(0 > opt || opt > 2)
	{
		cerr << "Option must be 0, 1, or 2!" << endl;
		exit(1);
	}
	option = opt;
}

/*Gets option*/
int CPU::getOption() const
{
	return option;
}

/*Prints all the registers and the PC*/
void CPU::print() const
{
	cout << "PC : " << PC << endl;
	
	for(int i = 0; i < 5; ++i)
		cout << "[" << i+1 << "] -> " << R[i] << endl;	
	cout <<endl;
}

/*Takes a string that contains an instruction line, executes it and 
 * advances the PC accordingly*/
int CPU::execute(string line, Memory& m)
{
	//cout << "testoption:" << option << endl;
	if(option == 1 || option == 2)
		cout << line << endl;
	
		
	Instruction inst;
	int result = analyzeLine(line, inst);
	if(result == 1)
		return 1;
	if(equalsTo(inst.mnemonic, "MOV"))
		move(inst, m);
	else if(equalsTo(inst.mnemonic, "ADD"))
		add(inst, m);
	else if(equalsTo(inst.mnemonic, "SUB"))
		sub(inst, m);
	else if(equalsTo(inst.mnemonic, "JMP")){
		if(!inst.hasROperand)
			setPC(inst.operandL.constant-1);
		else if(getR(inst.operandL.reg) == 0)
				setPC(inst.operandR.constant-1);
	}	
	else if(equalsTo(inst.mnemonic, "JPN"))
		if(getR(inst.operandL.reg) <= 0)
			setPC(inst.operandR.constant-1);
	else if(equalsTo(inst.mnemonic, "PRN"))
		prn(inst, m);
	else if(equalsTo(inst.mnemonic, "HLT"))
		setIsHalted(true);
	
	if(option == 1 || option == 2)
		print();
	
	if(option == 2)
		m.printAll();
	
	setPC(getPC() + 1);
	
	if(equalsTo(inst.mnemonic, "HLT"))
	{
		setIsHalted(true);
		cout << "Program ends..." << endl << endl;
		print();
		m.printAll();
	}
	
	return 0;
}

/*Returns true if CPU program was halted*/
bool CPU::halted() const {return isHalted;}


/*PRN reg, PRN const, PRN address*/
void CPU::prn(const Instruction& inst,  Memory& m) const
{
	if(inst.mnemonic == "PRN")
		switch(inst.kindOfL)
		{
			case 'r': cout << "[" << inst.operandL.reg << "] -> ["
						   << getR(inst.operandL.reg) << "]" << endl;
				break;
			case 'c': cout << inst.operandL.constant << endl;
				break;
			case 'a': cout << "[" << inst.operandL.address << "] -> ["
						   << m.getMem(inst.operandL.address) << "]" << endl;
				break;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
}

/*MOVE reg const, MOVE reg reg, MOVE reg address, 
 * MOVE address reg, MOVE address constant		*/
void CPU::move(const Instruction& inst, Memory& m)
{
	if(inst.kindOfL == 'r')
	{
		/*if instruction format is MOV reg reg*/
		if(inst.kindOfR == 'r'){
			setR(inst.operandR.reg ,getR(inst.operandL.reg));
		}	
		/*if instruction format is MOV reg const*/
		else if(inst.kindOfR == 'c')
			setR(inst.operandL.reg, inst.operandR.constant);
			
		/*if instruction format is MOV reg address*/
		else if(inst.kindOfR == 'a')
			m.setMem(inst.operandR.address, getR(inst.operandL.reg));
	}
	
	else if(inst.kindOfL == 'a')
	{
		/*if instruction format is MOV address reg*/
		if(inst.kindOfR == 'r')
			setR(inst.operandR.reg, m.getMem(inst.operandL.address));
			
		/*if instruction format is MOV address const*/
	else if(inst.kindOfR == 'c')
			m.setMem(inst.operandL.address, inst.operandR.constant);
	}
	
	else
	{
		cerr << "Undefined MOV instruction format!" << endl;
		return; 
	}
	
}

/*ADD reg const, ADD reg reg, ADD reg address*/
void CPU::add(const Instruction& inst, Memory& m)
{
	int temp;
	if(inst.mnemonic == "ADD" && inst.kindOfL == 'r')
		switch(inst.kindOfR)
		{
			/*if instruction format is ADD reg reg*/
			case 'r': temp = getR(inst.operandL.reg) + getR(inst.operandR.reg);
					  setR(inst.operandL.reg, temp);
				break;
			/*if instruction format is ADD reg address*/
			case 'a': temp = getR(inst.operandL.reg) + m.getMem(inst.operandR.address);
					  setR(inst.operandL.reg, temp);
				break;
			/*if instruction format is ADD reg const*/
			case 'c': temp = getR(inst.operandL.reg) + inst.operandR.constant;
					  setR(inst.operandL.reg, temp);
				break;
			default:
				cerr << "Undefined ADD instruction format!" << endl;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
}

/*SUB reg const, SUB reg reg, SUB reg address*/
void CPU::sub(const Instruction& inst, Memory& m)
{
	int temp;
	if(inst.mnemonic == "SUB" && inst.kindOfL == 'r')
		switch(inst.kindOfR)
		{
			/*if instruction format is SUB reg reg*/
			case 'r': temp = getR(inst.operandL.reg) - getR(inst.operandR.reg);
					  setR(inst.operandL.reg, temp);
				break;
			/*if instruction format is SUB reg address*/
			case 'a': temp = getR(inst.operandL.reg) - m.getMem(inst.operandR.address);
					  setR(inst.operandL.reg, temp);
				break;	
			/*if instruction format is SUB reg const*/
			case 'c': temp = getR(inst.operandL.reg) - inst.operandR.constant;
					  setR(inst.operandL.reg, temp);
				break;
			default:
				cerr << "Undefined SUB instruction format!" << endl;
		}
	else
		cerr << "Unexpected mnemonic!" << endl;
}
