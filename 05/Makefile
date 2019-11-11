CC=g++
CFLAGS=-g -Wall --std=c++17
SOURCES= #src/*.cpp
TESTS=tests/*.cpp

all:
	$(CC) $(CFLAGS) $(SOURCES) main.cpp -o serializer

run: all
	./serializer

test:
	$(CC) $(CFLAGS) $(SOURCES) $(TESTS) -o serializer_tests
	./serializer_tests

.PHONY: clean
clean:
	rm serializer serializer_tests
