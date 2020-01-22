CC=g++

all: tests

external_sort.o: external_sort.cpp external_sort.h
	@g++ -c external_sort.cpp

test.o: test.cpp
	@g++ -c test.cpp

test: tests
	@./tests

tests: external_sort.o test.o
	@g++ external_sort.o test.o -o tests --std=c++17 -pthread
clean:
	@rm *.o tests
