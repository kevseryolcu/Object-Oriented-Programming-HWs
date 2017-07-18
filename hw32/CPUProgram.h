#ifndef CPUPROGRAMH_
#define CPUPROGRAMH_

#include <string>
#include <vector>

class CPUProgram 
{
public:
	CPUProgram(char fileName[]);
	std::string getLine(int lineNumber) const;
	int size() const;
private:
	void readFile(char fileName[]);
	std::vector<std::string> insts;	
};

#endif
