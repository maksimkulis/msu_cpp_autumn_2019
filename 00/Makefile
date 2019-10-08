CC=g++

all: program clean run

program: sum_by_rows.o sum_by_colums.o functions.o
	$(CC) -O2 sum_by_rows.o functions.o -o sum_by_rows --std=c++11
	$(CC) -O2 sum_by_colums.o functions.o -o sum_by_colums --std=c++11

sum_by_rows.o: sum_by_rows.cpp
	$(CC) -O2 -c sum_by_rows.cpp -o sum_by_rows.o --std=c++11

sum_by_colums: sum_by_colums.cpp
	$(CC) -O2 -c sum_by_colums.cpp -o sum_by_colums.o --std=c++11

functions.o: functions.cpp
	$(CC) -O2 -c functions.cpp -o functions.o --std=c++11

clean:
	rm -rf *.o

run: sum_by_rows sum_by_colums
	./sum_by_rows
	./sum_by_colums

.PHONY: all run
