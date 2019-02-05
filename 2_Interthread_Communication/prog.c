#include <unistd.h> //pipe
#include <stdlib.h> //exit
#include <string.h> //strlen
#include <stdio.h> //printf
#include <sys/wait.h> //wait

#define MSG "Hello from the child"

int	main(void)
{
	int fd[2]; // 0-read, 1-write
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0)
	{
		//child
		write(fd[1], MSG, strlen(MSG));
		exit(0);
	}
	else
	{	
		//parent
		wait(NULL);
		char out[strlen(MSG)];
		read(fd[0], out, strlen(MSG));
		printf("Message from parent: '%s'\n", out);
	}
	return (0);
}



