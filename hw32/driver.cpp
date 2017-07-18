/*____________________________________________________________________*/
/*                                                                    */
/*					  131044072 KEVSER YOLCU						  */
/*	HW3 * Simple CPU Program										  *
 * 		- Takes file name from console which includes assembly code	  *
 * 		- Analyzes the file and executes instructions				  */
/*___________________________________________________________________ */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "CPU.h"
#include "CPUProgram.h" 

using namespace std;

int main(int argc, char* argv[])
{
	
	if(argc != 3)
	{	
		cerr << "The compilation format is ./prog fileName option" << endl;
		return 1;
	}
	
	CPU x;
	CPUProgram y(argv[1]);
	Instruction inst;
	
	while(!x.halted())
	{ 
		string instruction = y.getLine(x.getPC());
		if(overloadStoi(argv[2]) == 1)
			cout << instruction << endl;
			
		x.execute(instruction);
		
		if(overloadStoi(argv[2]) == 1)
			x.print();
	}
	if(overloadStoi(argv[2]) == 0)
		x.print();
	
	return 0;
}

