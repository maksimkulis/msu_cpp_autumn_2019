CC=g++

all: prog

prog: tests.o matrix.o
	@$(CC) tests.o matrix.o -o prog

tests.o: tests.cpp
	@$(CC) -c tests.cpp -o tests.o

matrix.o: matrix.cpp matrix.h
	@$(CC) -c matrix.cpp -o matrix.o

clean:
	@rm -rf *.o prog

test: prog
	@./prog
