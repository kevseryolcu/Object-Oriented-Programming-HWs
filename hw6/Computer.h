#ifndef COMPUTERH_
#define COMPUTERH_

#include "CPU.h"
#include "Memory.h"
#include "CPUProgramDyn.h"

//using namespace hey;
class Computer
{
public:
	/*Constructors*/
	Computer(int opt);
	Computer(CPU c, Memory m, hey::CPUProgramDyn cp, int opt);
	/*Setters*/
	void setCPU(CPU c);
	void setCPUProgramDyn(hey::CPUProgramDyn cp);
	void setMemory(Memory m);
	void setOption(int opt);
	/*Getters*/
	int getOption() const;
	CPU getCPU() const;
	hey::CPUProgramDyn getCPUProgramDyn() const;
	Memory getMemory() const;
	/*Executes the given program*/
	void execute();
private:
	int option;
	CPU myCPU;
	Memory myMemory;
	hey::CPUProgramDyn myCPUProg;
};



#endif
