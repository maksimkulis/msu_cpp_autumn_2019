all: test.cpp threadpool.h
	@g++ test.cpp -std=c++1z -pthread -o tests

test: all
	./tests

clean:
	@rm tests
