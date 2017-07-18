#include "CPUProgram.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

/*CPUProgram constructor*/
CPUProgram::CPUProgram(char fileName[])
{
	readFile(fileName);
}

/*Takes an integer as the parameter and returns a string that 
 * contains the program line that corresponds to the integer.*/
string CPUProgram::getLine(int lineNumber) const
{
	if(0 < lineNumber && lineNumber-1 <= (int)insts.size())
		return insts.at(lineNumber-1);
	cerr << "This line number is invalid!" << endl;
	exit(0);
}

/*Returns the number of lines read from the file.*/
int CPUProgram::size() const
{
	return insts.size();
}

/*Reads given file and stores instructions to insts string vector*/
void CPUProgram::readFile(char fileName[])
{
	fstream file;
	string line;
	
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
	}
	file.close();
}
