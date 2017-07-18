#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include "CPUProgramDyn.h"
#include "AssistantFunctions.h"

using namespace std;
namespace hey
{
	/*CPUProgramDyn constructors*/
	CPUProgramDyn::CPUProgramDyn(const char* fileName): capacity(50), used(0) 
	{
		insts = new string[capacity];
		ReadFile(fileName);
	}

	CPUProgramDyn::CPUProgramDyn(int opt): capacity(50), used(0) 
	{
		insts = new string[capacity];
		setOption(opt);
	}

	/*CPUProgramDyn copy constructor*/
	CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& cp): option(cp.getOption()), capacity(cp.getCapacity()), used(0) 
	{		
		insts = new string[capacity];
		if(cp.size() != 0){
			for(int i = 1; i <= cp.size(); ++i)
				setLine(cp.getLine(i-1));
			if(used != cp.size())
				used = cp.size();
		}	
		
	}

	/*Sets option*/
	void CPUProgramDyn::setOption(int opt)
	{
		if(0 > opt || opt > 2)
		{
			cerr << "Option must be 0, 1, or 2!" << endl;
			exit(1);
		}
		option = opt;
	}

	/*Gets option*/
	int CPUProgramDyn::getOption() const
	{
		return option;
	}

	/*Takes an integer as the parameter and returns a string that 
	 * contains the program line that corresponds to the integer.*/
	string CPUProgramDyn::getLine(int lineNumber) const
	{
		if(0 <= lineNumber && lineNumber < size())
			return insts[lineNumber];
		cerr << "Line " << lineNumber << "is invalid!" << endl;
		return "";
	}

	/*Sets a line*/
	void CPUProgramDyn::setLine(std::string line)
	{
		if(line != "")
		{
			if (full()) 
				rescale();
				
			if (used >= capacity)
			{
				cout << "Attempt to exceed capacity in PFArrayD.\n";
				exit(0);
			}
			
			insts[used] = line;
			used++;
		}
	}

	/*Destructor*/
	CPUProgramDyn::~CPUProgramDyn(){
		delete[] insts;
	}

	/*Reads given file and stores instructions to insts string vector*/
	void CPUProgramDyn::ReadFile(const char* fileName)
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
				setLine(line);
			}
		}
		file.close();
	}

	/*Operator+= that takes an instruction line as a string and appends 
	 * the instruction to the end of the program*/
	const CPUProgramDyn& CPUProgramDyn::operator+=(const std::string& line)
	{
		if(line == "")
		{
			cerr << "String cannot be empty!" << endl;
			return *this;
		}
		this->setLine(line);
		return *this;
	}


	/*compares the number of lines of the programs
	 * if they are equal to each other returns true, 
	 * false otherwise*/
	bool CPUProgramDyn::operator==(const CPUProgramDyn cp) const
	{
		return (this->size() == cp.size());
	}

	/*compares the number of lines of the programs
	 * if they are not equal to each other returns true, 
	 * false otherwise*/
	bool CPUProgramDyn::operator!=(const CPUProgramDyn cp) const
	{
		return !( *this == cp);
	}

	/*compares the number of lines of the programs
	 * if first program greater than second program returns true, 
	 * false otherwise*/
	bool CPUProgramDyn::operator>(const CPUProgramDyn cp) const
	{
		return (this->size() > cp.size());
	}

	/*compares the number of lines of the programs
	 * if first program smaller than second program returns true, 
	 * false otherwise*/
	bool CPUProgramDyn::operator<(const CPUProgramDyn cp) const
	{
		return (this->size() < cp.size());
	}

	/*compares the number of lines of the programs
	 * if first program greater than second program 
	 * or equals returns true, 
	 * false otherwise*/
	bool CPUProgramDyn::operator>=(const CPUProgramDyn cp) const
	{
		return !(*this < cp);
	}

	/*compares the number of lines of the programs
	 * if first program smaller than second program 
	 * or equals returns true, 
	 * false otherwise*/
	bool CPUProgramDyn::operator<=(const CPUProgramDyn cp) const
	{
		return !(*this > cp);
	}

	/*Takes line number and returns line as a string*/
	const string& CPUProgramDyn::operator[](int lineNumber) const
	{
		if(0 <= lineNumber && lineNumber < size())
			return insts[lineNumber];
		cerr << "Line " << lineNumber << " is invalid!" << endl;
		return "";
	}

	/*Takes a CPUProgramDyn object and a line as a string 
	 * Copies object to new object and appends line to new object*/
	const CPUProgramDyn CPUProgramDyn::operator+(const std::string& s) const
	{
		if(s == "")
		{
			cerr << "String cannot be empty!" << endl;
		}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		CPUProgramDyn newcp(getOption());
		if(size() != 0){
			for(int i = 1; i <= size(); ++i)
				newcp.setLine(getLine(i-1));
			newcp.setLine(s);
		}		
		newcp.setOption(getOption());
		
		return newcp;	
	}

	/*Operator+ that takes two programs and returns a new program 
	 * that appends the second programs to the first one*/
	const CPUProgramDyn CPUProgramDyn::operator+(const CPUProgramDyn& cp) const
	{
		CPUProgramDyn newcp(getOption());
		
		if(cp.size() != 0){
			for(int i = 1; i <= size(); ++i)
				newcp.setLine(getLine(i-1));
			for(int i = 1; i <= cp.size(); ++i)
				newcp.setLine(cp.getLine(i-1));
		}
		return newcp;
	}

	/*Operator>> that prints the program*/
	ostream& operator<<(ostream& oS, const CPUProgramDyn& cp)
	{
		for(int i = 0; i < cp.size(); ++i)
			oS << cp.getLine(i) << endl;
		return oS;
	}

	/*Deletes the last line of the program*/
	const CPUProgramDyn& CPUProgramDyn::operator--()//////////////////////////////////////
	{
		CPUProgramDyn temp(*this);
		if(size() > 0)
		{	
			delete [] insts;
			string *insts = new string[capacity];
			for(int i = 0; i < temp.size()-1; ++i)
				setLine(temp.getLine(i));
			used = temp.used - 1;
		}
		else
			cerr << "Out of index!" << endl;	
		return *this;
	}

	/*Deletes the last line of the program*/
	const CPUProgramDyn CPUProgramDyn::operator--(int x)//////////////////////////////////////
	{
		CPUProgramDyn temp(*this);
		if(size() > 0)
		{	
			delete [] insts;
			string *insts = new string[capacity];
			for(int i = 0; i < temp.size()-1; ++i)
				setLine(temp.getLine(i));
			used = temp.used - 1;
		}
		else
			cerr << "Out of index!" << endl;
			
		return temp;
	}

	/*Takes two int and return a new program that contains the instruction
	 * between the given integers */
	const CPUProgramDyn CPUProgramDyn::operator()(int begin, int end) const
	{
		CPUProgramDyn cp(this->option);
		if(begin >= size() || end >= size())
			cerr << "Out of index!" << endl;
		else
			for(int i = begin; i < end; ++i)
				cp.setLine(this->getLine(i-1));
			
		return cp;
	}
	
	void CPUProgramDyn::rescale(int scale)
	{

		capacity *= scale;
		string* newData = new string[capacity];

		for (int i = 0; i < used; i++)
			newData[i] = insts[i];

		delete[] insts;

		insts = newData;
	}
}
