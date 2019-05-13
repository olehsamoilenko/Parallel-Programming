#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdbool.h>

int	g_counter;
sem_t	g_semaphore;

void	*increment(void *arg)
{
	sem_wait(&g_semaphore);
	int i = -1;
	while (++i < 100000)
	{
		
		g_counter++;		
		printf("\x1B[32mIncrement\x1B[0m\n");
		
	}
	sem_post(&g_semaphore);
	
	return (NULL);
}

void	*decrement(void *arg)
{
	sem_wait(&g_semaphore);
	int i = -1;
	while (++i < 100000)
	{
		
		g_counter--;
		printf("\x1B[31mDecrement\x1B[0m\n");
		
	}
	sem_post(&g_semaphore);
	return (NULL);
}

int main(void)
{
	pthread_t thread[10];
	int i = 0;
	sem_init(&g_semaphore, false, 1);
	while (i < 10)
	{
		pthread_create(&thread[i], NULL, increment, NULL);
		pthread_create(&thread[i + 1], NULL, decrement, NULL);
		i += 2;
	}
	i = -1;
	while (++i < 10)
		pthread_join(thread[i], NULL);
	sem_destroy(&g_semaphore);
	printf("Main: %d\n", g_counter);
	return (0);
}
