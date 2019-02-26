all:
	gcc -o pipes pipes.c -pthread
	gcc server.c -o server
	gcc client.c -o client

clean:
	rm pipes
	rm server client
