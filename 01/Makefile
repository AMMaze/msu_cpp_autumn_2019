CC=g++
CFLAGS=-g -Wall --std=c++17

all:
	$(CC) $(CFLAGS) *.cpp -o calc

.PHONY: run
run: calc
	./calc "$(filter-out $@, $(MAKECMDGOALS))"

%:
	@true

.PHONY: clean
clean:
	rm calc
