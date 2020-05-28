all:server client

server:server.c
	gcc -Wall -o $@ $^
client:client.c
	gcc -Wall -o $@ $^

.PHONY:clean
clean:
	rm -f server client
