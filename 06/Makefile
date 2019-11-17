CC=g++

all: tests

tests: test.cpp format.h
	@$(CC) test.cpp -o tests

test: tests
	@./tests

clean: tests
	@rm *.o tests
