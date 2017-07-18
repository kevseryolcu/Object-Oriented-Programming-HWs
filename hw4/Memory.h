#ifndef MEMORYH_
#define MEMORYH_

#include "AssistantFunctions.h"

class Memory
{
public:
	Memory();
	Memory(int opt);
	void setMem(int memoryLocation, int content);
	unsigned int getMem(int memoryLocation) const;
	void setOption(int opt);
	int getOption() const;
	void printAll() const;

private:
	unsigned int memory[MEM_SIZE];
	int option;
};


#endif
