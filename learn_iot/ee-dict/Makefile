all:server client

server:server.c
	gcc -Wall -o $@ $^ -lsqlite3
client:client.c
	gcc -Wall -o $@ $^

.PHONY:clean
clean:
	rm server client
