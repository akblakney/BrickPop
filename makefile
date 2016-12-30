test: test.o brickPop.o
	g++ -o test test.o brickPop.o

test.o: test.cpp brickPop.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra -c test.cpp

brickPop.o: brickPop.cpp brickPop.hpp
	g++ -std=c++11 -pedantic -Wall -Wextra -c brickPop.cpp
