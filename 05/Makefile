CC=g++

all: tests

tests: test.cpp Serializer.h
	@$(CC) test.cpp -o tests

test: tests
	./tests

clean:
	rm tests
