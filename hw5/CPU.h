#ifndef CPUH_
#define CPUH_

#include <string>
#include "Memory.h"

class CPU
{
public:
	/*Constructors*/
	CPU();
	CPU(int opt);
	/*Setters*/
	void setRegisters(int r1, int r2, int r3, int r4, int r5);
	void setPC(int number);
	void setR(int regNumber, int content);
	void setIsHalted(bool b);
	void setOption(int opt);
	/*Getters*/
	int getOption() const;
	int getPC() const{return PC;};
	int getR(int regNumber) const;
	/*If program is halted returns true, false otherwise*/
	bool halted() const;
	/*Prints all the registers and the PC*/
	void print() const;
	/*Takes a string that contains an instruction line, executes it and 
	* advances the PC accordingly*/
	int execute(std::string line, Memory& m);
	
	
private:
	/*PRN reg, PRN const, PRN address*/
	void prn(const Instruction& inst,  Memory& m) const;
	/*MOVE reg const, MOVE reg reg, MOVE reg address, 
	* MOVE address reg, MOVE address constant		*/
	void move(const Instruction& inst, Memory& m);
	/*ADD reg const, ADD reg reg, ADD reg address*/
	void add(const Instruction& inst, Memory& m);
	/*SUB reg const, SUB reg reg, SUB reg address*/
	void sub(const Instruction& inst, Memory& m);
	
	bool isHalted;
	/*Registers*/
	int R[5];
	/*Program Counter*/
	int PC;	
	int option;
	
};




#endif

