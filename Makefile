
all: intbst testbst
	
intbst:  intbst.h
	g++ --std=c++11 -c -Wall intbst.h -o intbst
testbst:  intbst.h  testbst.cpp 
	g++ --std=c++11 -Wall testbst.cpp -o testbst
clean: 
	rm -f intbst testbst *.o