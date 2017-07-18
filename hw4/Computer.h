#ifndef COMPUTERH_
#define COMPUTERH_

#include "CPU.h"
#include "Memory.h"
#include "CPUProgram.h"

class Computer
{
public:
	Computer(int opt);
	Computer(CPU c, Memory m, CPUProgram cp, int opt);
	void setCPU(CPU c);
	void setCPUProgram(CPUProgram cp);
	void setMemory(Memory m);
	void setOption(int opt);
	int getOption() const;
	CPU getCPU() const;
	CPUProgram getCPUProgram() const;
	Memory getMemory() const;
	void execute();
private:
	int option;
	CPU myCPU;
	Memory myMemory;
	CPUProgram myCPUProg;
};



#endif
