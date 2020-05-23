CC=gcc
CFLAGS=-O0 -Wall -g
test:test.c seqlist.c
	$(CC) $(CFLAGS) -o $@ $^
.PHONY:clean
clean:
	$(RM) *.o test
