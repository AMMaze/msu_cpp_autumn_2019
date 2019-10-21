CC=g++
CFLAGS=-g -Wall --std=c++14
SOURCES=src/*.cpp
TESTS=tests/*.cpp

all:
	$(CC) $(CFLAGS) $(SOURCES) main.cpp -o alloc

.PHONY: run
run: all
	./alloc

test:
	$(CC) $(CFLAGS) $(SOURCES) $(TESTS) -o alloc_tests
	./alloc_tests

.PHONY: clean
clean:
	rm alloc alloc_tests
