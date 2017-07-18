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

/*CPUProgram copy constructor*/
CPUProgram::CPUProgram(const CPUProgram& cp): option(cp.getOption())
{
	if(cp.size() != 0){
		for(int i = 1; i <= static_cast<int>(cp.size()); ++i)
			setLine(cp.getLine(i-1));
	}	
	
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
	if(0 <= lineNumber && lineNumber < (int)insts.size())
		return insts.at(lineNumber);
	cerr << "This line number is invalid!" << endl;
	exit(0);
}

/*Sets a line*/
void CPUProgram::setLine(std::string line)
{
	insts.push_back(line);
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
	}
	file.close();
}

/*Operator+= that takes an instruction line as a string and appends 
 * the instruction to the end of the program*/
const CPUProgram& CPUProgram::operator+=(const std::string& line)
{
	if(line == "")
	{
		cerr << "String cannot be empty!" << endl;
		exit(1);
	}
	this->setLine(line);
	return *this;
}


/*compares the number of lines of the programs
 * if they are equal to each other returns true, 
 * false otherwise*/
bool CPUProgram::operator==(const CPUProgram cp) const
{
	return (this->size() == cp.size());
}

/*compares the number of lines of the programs
 * if they are not equal to each other returns true, 
 * false otherwise*/
bool CPUProgram::operator!=(const CPUProgram cp) const
{
	return !( *this == cp);
}

/*compares the number of lines of the programs
 * if first program greater than second program returns true, 
 * false otherwise*/
bool CPUProgram::operator>(const CPUProgram cp) const
{
	return (this->size() > cp.size());
}

/*compares the number of lines of the programs
 * if first program smaller than second program returns true, 
 * false otherwise*/
bool CPUProgram::operator<(const CPUProgram cp) const
{
	return (this->size() < cp.size());
}

/*compares the number of lines of the programs
 * if first program greater than second program 
 * or equals returns true, 
 * false otherwise*/
bool CPUProgram::operator>=(const CPUProgram cp) const
{
	return !(*this < cp);
}

/*compares the number of lines of the programs
 * if first program smaller than second program 
 * or equals returns true, 
 * false otherwise*/
bool CPUProgram::operator<=(const CPUProgram cp) const
{
	return !(*this > cp);
}

/*Takes line number and returns line as a string*/
const string& CPUProgram::operator[](int lineNumber) const
{
	if(0 <= lineNumber && lineNumber < size())
		return insts.at(lineNumber);
	cerr << "This line number is invalid!" << endl;
	return "";
}

/*Takes a CPUProgram object and a line as a string 
 * Copies object to new object and appends line to new object*/
const CPUProgram CPUProgram::operator+(const std::string& s) const
{
	if(s == "")
	{
		cerr << "String cannot be empty!" << endl;
	}
	CPUProgram newcp(getOption());
	if(size() != 0){
		for(int i = 1; i <= static_cast<int>(size()); ++i)
			newcp.setLine(getLine(i-1));
		newcp.setLine(s);
	}		
	newcp.setOption(getOption());
	
	return newcp;	
}

/*Operator+ that takes two programs and returns a new program 
 * that appends the second programs to the first one*/
const CPUProgram CPUProgram::operator+(const CPUProgram& cp) const
{
	CPUProgram newcp(getOption());
	
	if(cp.size() != 0){
		for(int i = 1; i <= static_cast<int>(size()); ++i)
			newcp.setLine(getLine(i-1));
		for(int i = 1; i <= static_cast<int>(cp.size()); ++i)
			newcp.setLine(cp.getLine(i-1));
	}
	return newcp;
}

/*Operator>> that prints the program*/
ostream& operator<<(ostream& oS, const CPUProgram& cp)
{
	for(int i = 0; i < cp.size(); ++i)
		oS << cp.getLine(i) << endl;
	return oS;
}

/*Deletes the last line of the program*/
const CPUProgram& CPUProgram::operator--()
{
	if(size() > 0)
		insts.pop_back();	
	else
		cerr << "Out of index!" << endl;	
	return *this;
}

/*Deletes the last line of the program*/
const CPUProgram CPUProgram::operator--(int x)
{
	CPUProgram temp(*this);
	if(size() > 0)
		insts.pop_back();	
	else
		cerr << "Out of index!" << endl;
		
	return temp;
}

/*Takes two int and return a new program that contains the instruction
 * between the given integers */
const CPUProgram CPUProgram::operator()(int begin, int end) const
{
	CPUProgram cp(this->option);
	if(begin >= size() || end >= size())
		cerr << "Out of index!" << endl;
	else
		for(int i = begin; i < end; ++i)
			cp.setLine(this->getLine(i-1));
		
	return cp;
}
