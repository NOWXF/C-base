OBJS=f1.o f2.o main.o
CFLAGS=-Wall -g -c
CFLAGS+=-I include
test:$(OBJS)
	gcc $(OBJS) -o $@
f1.o:f1.c
	gcc f1.c $(CFLAGS) -o $@
f2.o:f2.c
	gcc f2.c $(CFLAGS) -o $@ 
main.o:main.c
	gcc main.c $(CFLAGS) -o $@ 
.PHONY:clean
clean:
	rm *.o test -f
