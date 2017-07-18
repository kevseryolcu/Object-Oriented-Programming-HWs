#ifndef CPUProgramDynH_
#define CPUProgramDynH_

#include <string>
#include <vector>
namespace hey
{
	class CPUProgramDyn 
	{
	public:
		/*CPUProgramDyn constructors*/
		CPUProgramDyn(int opt);
		explicit CPUProgramDyn(const char* fileName);
		/*CPUProgramDyn copy constructor*/
		CPUProgramDyn(const CPUProgramDyn& cp);
		/*Destructor*/
		~CPUProgramDyn();
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
		const CPUProgramDyn& operator+=(const std::string& line);
		/*compares the number of lines of the programs
		 * if they are equal to each other returns true, 
		 * false otherwise*/
		bool operator==(const CPUProgramDyn cp) const;
		/*compares the number of lines of the programs
		 * if they are not equal to each other returns true, 
		 * false otherwise*/
		bool operator!=(const CPUProgramDyn cp) const;
		/*compares the number of lines of the programs
		 * if first program smaller than second program returns true, 
		 * false otherwise*/
		bool operator<(const CPUProgramDyn cp) const;
		/*compares the number of lines of the programs
		 * if first program greater than second program returns true, 
		 * false otherwise*/
		bool operator>(const CPUProgramDyn cp) const;
		/*compares the number of lines of the programs
		 * if first program greater than second program 
		 * or equals returns true, 
		 * false otherwise*/
		bool operator>=(const CPUProgramDyn cp) const;
		/*compares the number of lines of the programs
		 * if first program smaller than second program 
		 * or equals returns true, 
		 * false otherwise*/
		bool operator<=(const CPUProgramDyn cp) const;
		/*Takes line number and returns line as a string*/
		const std::string& operator[](int lineNumber) const;
		/*Takes a CPUProgramDyn object and a line as a string 
		 * Copies object to new object and appends line to new object*/
		//const CPUProgramDyn operator+(const std::string& s) const;
		/*Operator+ that takes two programs and returns a new program 
		* that appends the second programs to the first one*/
		const CPUProgramDyn operator+(const CPUProgramDyn& cp) const;
		/*Operator>> that prints the program*/
		friend std::ostream& operator<<(std::ostream& oS, const CPUProgramDyn& cp);
		/*Deletes the last line of the program*/
		const CPUProgramDyn& operator--();
		/*Deletes the last line of the program*/
		const CPUProgramDyn operator--(int x);
		/*Takes two int and return a new program that contains the instruction
		* between the given integers */
		const CPUProgramDyn operator()(int begin, int end) const;
		/*Takes a CPUProgramDyn object and a line as a string 
		 * Copies object to new object and appends line to new object*/
		const CPUProgramDyn operator+(const std::string& s) const;
		/*Reads given file and stores instructions to insts string vector*/
		void ReadFile(const char* fileName);
		/*Returns the number of lines read from the file.*/
		int size() const {	return getNumberUsed();	}
		
		int getCapacity( ) const { return capacity; }

		int getNumberUsed( ) const { return used; }

		void emptyArray( ){ used = 0; }
		
		bool full( ) const { return (capacity == used); }
		
		void rescale(int scale = 2);
	private:
		std::string* insts;	
		int capacity;
		int used;
		int option;
	};
}
/*Takes a CPUProgramDyn object and a line as a string 
 * Copies object to new object and appends line to new object*/
/*const CPUProgramDyn operator+(const std::string& s, const CPUProgramDyn& cp);
const CPUProgramDyn operator+(const CPUProgramDyn& cp,const std::string& s);*/

#endif
