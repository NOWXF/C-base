all:server client
server:server_pth.c
	gcc -Wall -o $@ $^ -lpthread
client:client.c
	gcc -Wall -o $@ $^

.PHONY:clean
clean:
	rm -f server client
