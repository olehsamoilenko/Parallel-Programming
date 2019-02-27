#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <string.h> 
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024
   
int main(int argc, char const *argv[]) 
{ 
    	int socket_id;
    	if ((socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    	{ 
        	perror("socket creation error"); 
        	exit(EXIT_FAILURE); 
    	}
 
	struct sockaddr_in serv_addr;
    	memset(&serv_addr, '0', sizeof(serv_addr));    
    	serv_addr.sin_family = AF_INET; 
    	serv_addr.sin_port = htons(PORT); 
    	// Convert IPv4 and IPv6 addresses from text to binary form 
    	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    	{
        	perror("address not supported"); 
        	exit(EXIT_FAILURE); 
    	} 
   
    	if (connect(socket_id, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    	{ 
        	perror("connection failed"); 
        	exit(EXIT_FAILURE);
    	}
	
	char *hello = "hello from client";
	while (1)
	{
		sleep(1);
    		send(socket_id, hello, strlen(hello), 0);
    		printf("Message sent to server\n");
		char buffer[1024] = {0};
    		read(socket_id, buffer, BUF_SIZE); 
    		printf("Got from server: %s\n",buffer);
	}
    	
	return (0); 
}
