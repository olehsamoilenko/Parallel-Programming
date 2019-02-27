#include <pthread.h>
#include <unistd.h> //sleep
#include <stdio.h>
#include <signal.h>

pthread_t	main_thread;
pthread_t	add_thread_1;
pthread_t	add_thread_2;
int		counter = 0;

void sig_func(int sig)
{
	printf("Caught signal %d\n", sig);
	if (sig == SIGUSR1)
		counter++;
	else if (sig == SIGUSR2)
		counter -= 2;
}

void add_func_1()
{
	signal(SIGUSR1, sig_func);
	while (1)
		;
}

void add_func_2()
{
	signal(SIGUSR2, sig_func);
	while (1)
		;
}

void main_func()
{
	while (1)
	{
		sleep(1);
		pthread_kill(add_thread_1, SIGUSR1);
		pthread_kill(add_thread_2, SIGUSR2);
		printf("Main thread: Counter value: %d\n", counter);
	}
}

int main()
{
	pthread_create(&main_thread, NULL, (void*)main_func, NULL);
	pthread_create(&add_thread_1, NULL, (void*)add_func_1, NULL);
	pthread_create(&add_thread_2, NULL, (void*)add_func_2, NULL);
	
	pthread_join(main_thread, NULL);
	pthread_join(add_thread_1, NULL);
	pthread_join(add_thread_2, NULL);
}
