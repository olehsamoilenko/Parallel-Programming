#include <unistd.h> // read
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define PORT 8080
#define BUF_SIZE 1000000

int main(void) 
{ 
	int server_fd;
    	// Creating socket file descriptor 
    	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    	{ 
        	perror("socket failed"); 
        	exit(EXIT_FAILURE); 
    	} 
       	
	int opt;
    	// Forcefully attaching socket to the port 8080 
    	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    	{ 
        	perror("setsockopt"); 
        	exit(EXIT_FAILURE); 
    	}
	
	struct sockaddr_in address; 
    	address.sin_family = AF_INET; 
    	address.sin_addr.s_addr = INADDR_ANY; 
    	address.sin_port = htons(PORT);
    	// Forcefully attaching socket to the port 8080 
    	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) 
    	{ 
        	perror("bind failed"); 
        	exit(EXIT_FAILURE); 
    	}
 
    	if (listen(server_fd, 3) < 0) 
    	{ 
        	perror("listen"); 
        	exit(EXIT_FAILURE); 
    	}
 	
	int new_socket;
	socklen_t addrlen = sizeof(address);
    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) 
    	{ 
        	perror("accept"); 
        	exit(EXIT_FAILURE); 
    	}
	
	char *responce = malloc(sizeof(char) * BUF_SIZE);
	char *buffer = malloc(sizeof(char) * BUF_SIZE);
	int i = -1;
	while (++i < BUF_SIZE)
		responce[i] = '0';
	int counter = -1;
	while (++counter < 100)
	{	
		//char *buffer = malloc(sizeof(char) * BUF_SIZE);
    		read(new_socket, buffer, BUF_SIZE);
    		printf("Got from client: %s\n", buffer);	
		send(new_socket, responce, BUF_SIZE, 0); 
    		printf("Responce sent to client\n");
	}
    
	return (0); 
} 
