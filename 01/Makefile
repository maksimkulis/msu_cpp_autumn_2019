CC=g++

all: program

program: main.o calculator.o lexer.o
	@$(CC) main.o calculator.o lexer.o -o program
	@echo Done

main.o: main.cpp
	@$(CC) -c main.cpp

calculator.o: calculator.cpp
	@$(CC) -c calculator.cpp

lexer.o: lexer.cpp
	@$(CC) -c lexer.cpp

run: program
	@./program

test: program
	@python3 ./test.py

clean:
	@rm -rf *.o program
