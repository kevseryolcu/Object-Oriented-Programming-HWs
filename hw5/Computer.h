#ifndef COMPUTERH_
#define COMPUTERH_

#include "CPU.h"
#include "Memory.h"
#include "CPUProgram.h"

class Computer
{
public:
	/*Constructors*/
	Computer(int opt);
	Computer(CPU c, Memory m, CPUProgram cp, int opt);
	/*Setters*/
	void setCPU(CPU c);
	void setCPUProgram(CPUProgram cp);
	void setMemory(Memory m);
	void setOption(int opt);
	/*Getters*/
	int getOption() const;
	CPU getCPU() const;
	CPUProgram getCPUProgram() const;
	Memory getMemory() const;
	/*Executes the given program*/
	void execute();
private:
	int option;
	CPU myCPU;
	Memory myMemory;
	CPUProgram myCPUProg;
};



#endif
