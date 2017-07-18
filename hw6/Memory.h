#ifndef MEMORYH_
#define MEMORYH_

#include "AssistantFunctions.h"

class Memory
{
public:
	/*Constructors*/
	Memory();
	Memory(int opt);
	/*Sets memory contents*/
	void setMem(int memoryLocation, int content);
	/*Gets memory content*/
	unsigned int getMem(int memoryLocation) const;
	void setOption(int opt);
	int getOption() const;
	/*Prints all memory contents*/
	void printAll() const;

private:
	/*Memory*/
	unsigned int memory[MEM_SIZE];
	int option;
};


#endif
