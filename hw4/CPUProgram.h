#ifndef CPUPROGRAMH_
#define CPUPROGRAMH_

#include <string>
#include <vector>

class CPUProgram 
{
public:
	CPUProgram(int opt);
	CPUProgram(const char* fileName);
	void setOption(int opt);
	int getOption() const;
	void setLine(std::string line, int lineNumber);
	std::string getLine(int lineNumber) const;
	void ReadFile(const char* fileName);
	int size() const;
private:
	std::vector<std::string> insts;	
	int option;
};

#endif
