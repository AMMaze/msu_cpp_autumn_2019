CC=g++
CFLAGS=-g -Wall --std=c++17
SOURCES= #src/*.cpp
TESTS=tests/*.cpp

all:
	$(CC) $(CFLAGS) $(SOURCES) main.cpp -o format

run: all
	./format

test:
	$(CC) $(CFLAGS) $(SOURCES) $(TESTS) -o format_tests
	./format_tests

.PHONY: clean
clean:
	rm format format_tests
