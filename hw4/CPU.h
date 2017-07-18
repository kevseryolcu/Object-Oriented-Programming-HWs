#ifndef CPUH_
#define CPUH_

#include <string>
#include "Memory.h"

class CPU
{
public:
	CPU();
	CPU(int opt);
	void setRegisters(int r1, int r2, int r3, int r4, int r5);
	void setPC(int number);
	void setR(int regNumber, int content);
	void setIsHalted(bool b);
	void setOption(int opt);
	int getOption() const;
	int getPC() const{return PC;};
	int getR(int regNumber) const;
	bool halted() const;
	void print() const;
	int execute(std::string line, Memory& m);
	
	
private:
	void prn(const Instruction& inst,  Memory& m) const;
	void move(const Instruction& inst, Memory& m);
	void add(const Instruction& inst, Memory& m);
	void sub(const Instruction& inst, Memory& m);
	
	bool isHalted;
	int R[5];
	int PC;	
	int option;
	
};




#endif

