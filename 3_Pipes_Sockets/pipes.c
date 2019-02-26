#include <unistd.h> //pipe
#include <stdlib.h> //exit
#include <string.h> //strlen
#include <stdio.h> //printf
#include <sys/wait.h> //wait
#include <pthread.h> // pthread_t

int fd[2]; // 0-read, 1-write

void reader()
{
	char out[1];
	
	while (1)
	{
		read(fd[0], out, 1);
		printf("Thread 1: reading %s...\n", out);
	}
}

void writer()
{
	char *c = "Hello";

	while (1)
	{
		sleep(1);
		printf("Thread 2: writing %s...\n", c);
		write(fd[1], c, strlen(c));
	}
}

int	main(void)
{
	pipe(fd);

	pthread_t thread_1;
	pthread_t thread_2;

	pthread_create(&thread_1, NULL, (void*)reader, NULL);
	pthread_create(&thread_2, NULL, (void*)writer, NULL);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	return (0);
}
