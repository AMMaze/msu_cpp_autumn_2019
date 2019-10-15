CC=g++
CFLAGS=-g -Wall --std=c++14

all:
	$(CC) $(CFLAGS) *.cpp -o calc

.PHONY: run
run: calc
	./calc "$(filter-out $@, $(MAKECMDGOALS))"

%:
	@true

test: all
	python3 tests.py 

.PHONY: clean
clean:
	rm calc
