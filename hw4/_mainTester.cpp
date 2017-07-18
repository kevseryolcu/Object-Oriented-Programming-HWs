#include "requiredIncs.h"

using namespace std;

int main(int argc, char** argv){
	
	if(argc != 3)
	{	
		cerr << "The compilation format is ./prog fileName option" << endl;
		return 1;
	}
	
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
	
	
	//Testing class Memory
	Memory myMemory(option);
	//index, value
	myMemory.setMem(0, 100);
	cout << myMemory.getMem(0) << endl;
	//should print in a way that similar to this:
	//Memory Values:
	//[0] -> 100
	//[1] -> 0
	//[2] -> 0
	//.
	//.
	//[49] -> 0
	myMemory.printAll();
	
	
	//Testing class CPU
	CPU myCPU(option);
	myCPU.execute("MOV #0, R1", myMemory);
	myCPU.execute("MOV R1, #1", myMemory);
	//should print in a way that similar to this:
	//CPU Register Values:
	//[0] -> 100
	//[1] -> 0
	//[2] -> 0
	//[3] -> 0
	//[4] -> 0
	//myCPU.print();
	//should print in a way that similar to this:
	//Memory Values:
	//[0] -> 100
	//[1] -> 100
	//[2] -> 0
	//.
	//.
	//[49] -> 0
	//myMemory.printAll();
	
	//Testing class CPUProgram
	CPUProgram myCPUProgram(option);
	myCPUProgram.ReadFile(filename);
	cout << myCPUProgram.getLine(0) << endl;
	//cout << "sizetest:" << myCPUProgram.size() << endl;
	cout << myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;

	//Testing class Computer
	cout << "1" << endl;
	Computer myComputer1(myCPU, myMemory, myCPUProgram, option);
	cout << "2" << endl;
	Computer myComputer2(option);
	cout << "3" << endl;
	myComputer2.setCPU( myComputer1.getCPU() );
	cout << "4" << endl;
	myComputer2.setCPUProgram(myComputer1.getCPUProgram() );
	cout << "5" << endl;
	myComputer2.setMemory(myComputer1.getMemory() );
	cout << "6" << endl;
	myComputer2.execute();
	cout << "7" << endl;
	

	return 0;
}
