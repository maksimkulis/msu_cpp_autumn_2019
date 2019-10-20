CC=g++

all: prog

prog: test.o alloc.o
	@$(CC) test.o alloc.o -o tests

alloc.o: alloc.cpp
	@$(CC) -c alloc.cpp -o alloc.o

test.o: test.cpp
	@$(CC) -c test.cpp -o test.o

clean:
	@rm -rf *.o

test: tests
	@./tests
