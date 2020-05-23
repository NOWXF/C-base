test:f1.o f2.o main.o
	gcc f1.o f2.o main.o -o test
f1.o:f1.c
	gcc -c f1.c -Wall -o f1.o
f2.o:f2.c
	gcc -c f2.c -Wall -o f2.o
main.o:main.c
	gcc -c main.c -Wall -o main.o
.PHONY:clean
clean:
	rm *.o test -f
