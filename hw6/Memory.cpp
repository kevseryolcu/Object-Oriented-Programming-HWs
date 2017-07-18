#include <iostream>
#include <cstdlib>
#include <string>
#include "Memory.h"
#include "AssistantFunctions.h"

using namespace std;

/*Constructors*/
Memory::Memory()
{
	for(int i = 0; i < MEM_SIZE; ++i)
		memory[i] = 0;
	option = 0;
}

Memory::Memory(int opt)
{
	if(0 > opt || opt > 2)
	{
		cerr << "Option must be 0, 1, or 2!" << endl;
		exit(1);
	}
	for(int i = 0; i < MEM_SIZE; ++i)
		memory[i] = 0;
	option = opt;
}

/*Sets memory content*/
void Memory::setMem(int memoryLocation, int content)
{
	if(0 > memoryLocation || memoryLocation >= MEM_SIZE)
	{
		cerr << "You try to reach undefined memory location!" << endl;
		exit(1);
	}
	if(content < 0)
	{
		cerr << "Contents of memory must be unsigned!" << endl;
		exit(1);
	}
	
	memory[memoryLocation] = static_cast<unsigned int>(content);
}

/*Gets memory content*/
unsigned int Memory::getMem(int memoryLocation) const
{
	if(0 > memoryLocation || memoryLocation >= MEM_SIZE)
	{
		cerr << "You try to reach undefined memory location!" << endl;
		exit(1);
	}
	return memory[(unsigned int)(memoryLocation)];
	
}

/*Sets option*/
void Memory::setOption(int opt)
{
	if(0 > opt || opt > 2)
	{
		cerr << "Option must be 0, 1, or 2!" << endl;
		exit(1);
	}
	option = opt;
}

/*Gets option*/
int Memory::getOption() const
{
	return option;
}

/*Prints all memory contents*/
void Memory::printAll() const
{
	for(int i = 0; i < MEM_SIZE; ++i)
		cout << "[" << i << "] -> " << memory[i] << endl;
	cout <<  endl;
}
