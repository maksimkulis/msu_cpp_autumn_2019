CC=g++

all: prog

prog: test.o BigInt.o
	@$(CC) -std=c++11 test.o BigInt.o -o prog

test.o: test.cpp
	@$(CC) -c test.cpp -o test.o

BigInt.o: BigInt.cpp BigInt.h
	@$(CC) -c BigInt.cpp -o BigInt.o

test: prog
	@./prog

clean:
	@rm -rf *.o prog
