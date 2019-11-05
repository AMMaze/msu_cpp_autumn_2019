CC=g++
CFLAGS=-g -Wall --std=c++14
SOURCES=src/*.cpp
TESTS=tests/*.cpp

all:
	$(CC) $(CFLAGS) $(SOURCES) main.cpp -o bigint

run: all
	./bigint

test:
	$(CC) $(CFLAGS) $(SOURCES) $(TESTS) -o bigint_tests
	./bigint_tests

.PHONY: clean
clean:
	rm bigint bigint_tests
