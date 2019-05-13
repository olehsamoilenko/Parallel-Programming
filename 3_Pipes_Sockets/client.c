#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <string.h> 
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define BUF_SIZE 1000000
   
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
	int counter = -1;
	long sum = 0;
	char *buffer = malloc(sizeof(char) * BUF_SIZE);
	while (++counter < 100)
	{
		//sleep(1);
    		send(socket_id, hello, strlen(hello), 0);
    		printf("Message sent to server\n");
		//static char *buffer = malloc(sizeof(char) * BUF_SIZE);
		clock_t begin = clock();
    		read(socket_id, buffer, BUF_SIZE - 1); 
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		double speed = BUF_SIZE / time_spent;
		sum += speed;
    		printf("(time = %f, symbols = %d, speed = %ld)\n", time_spent,
			BUF_SIZE, (long)((double)BUF_SIZE / time_spent));
	}
	printf("AVG: %f\n", (double)sum / 10000);

    	
	return (0); 
}
