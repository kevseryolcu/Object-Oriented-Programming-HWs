#ifndef CPUPROGRAMH_
#define CPUPROGRAMH_

#include <string>
#include <vector>

class CPUProgram 
{
public:
	/*CPUProgram constructors*/
	CPUProgram(int opt);
	explicit CPUProgram(const char* fileName);
	/*CPUProgram copy constructor*/
	CPUProgram(const CPUProgram& cp);
	/*Destructor*/
	~CPUProgram(){};
	/*Sets option*/
	void setOption(int opt);
	/*Gets option*/
	int getOption() const;
	/*Sets a line*/
	void setLine(std::string line);
	/*Takes an integer as the parameter and returns a string that 
	* contains the program line that corresponds to the integer.*/
	std::string getLine(int lineNumber) const;
	/*Operator+= that takes an instruction line as a string and appends 
	* the instruction to the end of the program*/
	const CPUProgram& operator+=(const std::string& line);
	/*compares the number of lines of the programs
	 * if they are equal to each other returns true, 
	 * false otherwise*/
	bool operator==(const CPUProgram cp) const;
	/*compares the number of lines of the programs
	 * if they are not equal to each other returns true, 
	 * false otherwise*/
	bool operator!=(const CPUProgram cp) const;
	/*compares the number of lines of the programs
	 * if first program smaller than second program returns true, 
	 * false otherwise*/
	bool operator<(const CPUProgram cp) const;
	/*compares the number of lines of the programs
	 * if first program greater than second program returns true, 
	 * false otherwise*/
	bool operator>(const CPUProgram cp) const;
	/*compares the number of lines of the programs
	 * if first program greater than second program 
	 * or equals returns true, 
	 * false otherwise*/
	bool operator>=(const CPUProgram cp) const;
	/*compares the number of lines of the programs
	 * if first program smaller than second program 
	 * or equals returns true, 
	 * false otherwise*/
	bool operator<=(const CPUProgram cp) const;
	/*Takes line number and returns line as a string*/
	const std::string& operator[](int lineNumber) const;
	/*Takes a CPUProgram object and a line as a string 
	 * Copies object to new object and appends line to new object*/
	//const CPUProgram operator+(const std::string& s) const;
	/*Operator+ that takes two programs and returns a new program 
	* that appends the second programs to the first one*/
	const CPUProgram operator+(const CPUProgram& cp) const;
	/*Operator>> that prints the program*/
	friend std::ostream& operator<<(std::ostream& oS, const CPUProgram& cp);
	/*Deletes the last line of the program*/
	const CPUProgram& operator--();
	/*Deletes the last line of the program*/
	const CPUProgram operator--(int x);
	/*Takes two int and return a new program that contains the instruction
	* between the given integers */
	const CPUProgram operator()(int begin, int end) const;
	/*Takes a CPUProgram object and a line as a string 
	 * Copies object to new object and appends line to new object*/
	const CPUProgram operator+(const std::string& s) const;
	/*Reads given file and stores instructions to insts string vector*/
	void ReadFile(const char* fileName);
	/*Returns the number of lines read from the file.*/
	int size() const;
private:
	std::vector<std::string> insts;	
	int option;
};

/*Takes a CPUProgram object and a line as a string 
 * Copies object to new object and appends line to new object*/
/*const CPUProgram operator+(const std::string& s, const CPUProgram& cp);
const CPUProgram operator+(const CPUProgram& cp,const std::string& s);*/

#endif
