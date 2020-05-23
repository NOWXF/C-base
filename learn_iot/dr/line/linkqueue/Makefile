CFLAGS = -g -Wall -O0
CC = gcc

test:test.c linkqueue.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm test
