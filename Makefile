
all: intbst testbst
	
intbst: intbst.cpp  intbst.h
	g++ --std=c++11 -c -Wall intbst.cpp -o intbst
testbst: intbst.cpp  intbst.h  testbst.cpp 
	g++ --std=c++11 -Wall testbst.cpp intbst.cpp -o testbst
clean: 
	rm -f intbst testbst *.o