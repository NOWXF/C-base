all:receiver sender

receiver:receiver.c
	gcc -Wall -o $@ $^
sender:sender.c
	gcc -Wall -o $@ $^

.PHONY:clean
clean:
	rm -f receiver sender
