all: hello

hello: CPU.o CPUProgram.o driver.o
	g++ CPU.o CPUProgram.o driver.o -o driver -std=c++11
	rm *.o

driver.o: driver.cpp
	g++ -c -std=c++11 driver.cpp

CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp

CPUProgram.o: CPUProgram.cpp
	g++ -c -std=c++11 CPUProgram.cpp

clean:
	rm driver
