#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include "CPUProgram.h"
#include "AssistantFunctions.h"

using namespace std;

/*CPUProgram constructors*/
CPUProgram::CPUProgram(const char* fileName)
{
	ReadFile(fileName);
}

CPUProgram::CPUProgram(int opt)
{
	setOption(opt);
}

/*Sets option*/
void CPUProgram::setOption(int opt)
{
	if(0 > opt || opt > 2)
	{
		cerr << "Option must be 0, 1, or 2!" << endl;
		exit(1);
	}
	option = opt;
}

/*Gets option*/
int CPUProgram::getOption() const
{
	return option;
}

/*Takes an integer as the parameter and returns a string that 
 * contains the program line that corresponds to the integer.*/
string CPUProgram::getLine(int lineNumber) const
{
	//cout << "instssizetest:"<<(int)insts.size() << endl;
	if(0 <= lineNumber && lineNumber < (int)insts.size())
		return insts.at(lineNumber);
	cerr << "This line number is invalid!" << endl;
	exit(0);
}

/*Sets a line*/
void CPUProgram::setLine(std::string line, int lineNumber)
{
	//insts.assign(lineNumber-1, line);	
	insts.push_back(line);
	//cout << "linetest:" << line<< endl;
	//cout << "insts[i]:" << insts[lineNumber -1] << endl;
}

/*Returns the number of lines read from the file.*/
int CPUProgram::size() const
{
	return insts.size();
}

/*Reads given file and stores instructions to insts string vector*/
void CPUProgram::ReadFile(const char* fileName)
{
	fstream file;
	string line;
	int count = 0;
	
	file.open(fileName);
	
	if(!file.is_open())
	{
		cerr << "File could not be opened!" << endl;
		exit(1);
	}
	
	while(!file.eof())
	{
		getline(file, line);
		if(!line.empty())
		{ 
			insts.push_back(line);	
		}
		if(count > MEM_SIZE)
		{
			cerr << "Number of instructions must be smaller than 200!"<<endl;
			exit(1);
		}
	}
	file.close();
}

