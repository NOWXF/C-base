CC = gcc
CFLAGS = -Wall -g
OBJS = test
SRC = test.c btree.c queue.c

$(OBJS):$(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm $(OBJS) 
