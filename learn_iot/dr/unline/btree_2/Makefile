CC = gcc
CFLAGS = -Wall -g -O0
OBJS = test
SRC = test.c btree.c queue.c stack.c

$(OBJS):$(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm $(OBJS) 
