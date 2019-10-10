CC=g++
CFLAGS=-Wall --std=c++14

all:
	$(CC) $(CFLAGS) sum_by_rows.cpp -o sum_by_rows.out
	$(CC) $(CFLAGS) sum_by_columns.cpp -o sum_by_columns.out

run:
	./sum_by_rows.out
	./sum_by_columns.out

clean:
	rm sum_by_rows.out sum_by_columns.out
