#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include "Computer.h"
#include "AssistantFunctions.h"

using namespace std;

Computer::Computer(int opt) : myCPU(opt), myMemory(opt), myCPUProg(opt)
{
	if(0 > opt || opt > 2)
	{
		cerr << "Option must be 0, 1, or 2!" << endl;
		exit(1);
	}
	myCPU.setOption(opt);
	myMemory.setOption(opt);
	myCPUProg.setOption(opt);
	setOption(opt);
}

Computer::Computer(CPU c, Memory m, CPUProgram cp, int opt) : Computer(opt)
{
	if(0 > option || option > 2)
	{
		cerr << "Option must be 0, 1, or 2!" << endl;
		exit(1);
	}
	
	setMemory(m);
	setCPUProgram(cp);
	setCPU(c);
	m.setOption(opt);
	c.setOption(opt);
	cp.setOption(opt);
	setOption(opt);
}

void Computer::setCPU(CPU c)
{
	myCPU.setRegisters(c.getR(1), c.getR(2), c.getR(3), c.getR(4), c.getR(5));
	myCPU.setPC(c.getPC());
	myCPU.setIsHalted(c.halted());
	myCPU.setOption(c.getOption());
}

void Computer::setCPUProgram(CPUProgram cp)
{
	if(cp.size() != 0){
		//cout <<"cpsizebefore for:" << static_cast<int>(cp.size()) << endl;
		for(int i = 1; i <= static_cast<int>(cp.size()); ++i)
		{
		//	cout << "heytest: " << cp.getLine(i) << ":i: " << i << endl;
			myCPUProg.setLine(cp.getLine(i-1), i-1);
		}
	}		
	myCPUProg.setOption(cp.getOption());
}

void Computer::setMemory(Memory m)
{
	for(int i = 0; i < MEM_SIZE; ++i)
		myMemory.setMem(i, m.getMem(i));
	myMemory.setOption(m.getOption());
}

CPU Computer::getCPU() const
{
	return myCPU;
}

CPUProgram Computer::getCPUProgram() const
{
	return myCPUProg;
}

/*Sets option*/
void Computer::setOption(int opt)
{
	if(0 > opt || opt > 2)
	{
		cerr << "Option must be 0, 1, or 2!" << endl;
		exit(1);
	}
	option = opt;
}

/*Gets option*/
int Computer::getOption() const
{
	return option;
}


void Computer::execute()
{
	/*CPU x(opt);
	CPUProgram y(filename);
	Memory z(opt);
	Instruction inst;
	
	y.setOption(opt);*/
	
	while(!myCPU.halted())
	{ 
		//cout << "getpctest:" << myCPU.getPC() << endl;//////////
		string instruction = myCPUProg.getLine(myCPU.getPC()-1);
		/*if(opt == 1 || opt == 2)
			cout << instruction << endl;*/
			
		myCPU.execute(instruction, myMemory);
		cout << "PC:" << myCPU.getPC()+1<< endl;
		myCPU.setPC(myCPU.getPC()+1);
		
		/*if(opt == 1)
			x.print();*/
	}
	/*if(opt == 0)
		x.print();*/
	
}


Memory Computer::getMemory() const
{
	return myMemory;
}
