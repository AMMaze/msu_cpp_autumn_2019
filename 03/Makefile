CC=g++
CFLAGS=-g -Wall --std=c++14
SOURCES=src/*.cpp
TESTS=tests/*.cpp

all:
	$(CC) $(CFLAGS) $(SOURCES) -o matrix

run: all
	./matrix

test:
	$(CC) $(CFLAGS) $(SOURCES) $(TESTS) -o matrix_tests
	./matrix_tests

.PHONY: clean
clean:
	rm matrix matrix_tests
