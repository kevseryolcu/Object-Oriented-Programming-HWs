all: hello

hello: AssistantFunctions.o CPUProgramDyn.o Memory.o CPU.o Computer.o _mainTester.o
	g++ AssistantFunctions.o CPUProgramDyn.o Memory.o CPU.o Computer.o _mainTester.o -o exe -std=c++11
	rm *.o

main.o: _mainTester.cpp
	g++ -c -std=c++11 _mainTester.cpp

AssistantFunctions.o: AssistantFunctions.cpp
	g++ -c -std=c++11 AssistantFunctions.cpp

CPUProgramDyn.o: CPUProgramDyn.cpp
	g++ -c -std=c++11 CPUProgramDyn.cpp

Memory.o: Memory.cpp
	g++ -c -std=c++11 Memory.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp

Computer.o: Computer.cpp
	g++ -c -std=c++11 Computer.cpp

clean:
	rm exe
