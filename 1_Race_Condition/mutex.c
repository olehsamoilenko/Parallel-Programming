#include <pthread.h>
#include <stdio.h>

int		g_counter;
pthread_mutex_t	g_mutex;

void	*increment(void *arg)
{
	pthread_mutex_lock(&g_mutex);
	int i = -1;
	while (++i < 100000)
	{
		g_counter++;
		printf("\x1B[32mIncrement\x1B[0m\n");
	}
	pthread_mutex_unlock(&g_mutex);
	return (NULL);
}

void	*decrement(void *arg)
{
	pthread_mutex_lock(&g_mutex);
	int i = -1;
	while (++i < 100000)
	{
		g_counter--;
		printf("\x1B[31mDecrement\x1B[0m\n");
	}
	pthread_mutex_unlock(&g_mutex);
	return (NULL);
}

int main(void)
{
	pthread_t thread[10];
	pthread_mutex_init(&g_mutex, NULL);
	int i = 0;
	while (i < 10)
	{
		pthread_create(&thread[i], NULL, increment, NULL);
		pthread_create(&thread[i + 1], NULL, decrement, NULL);
		i += 2;
	}
	i = -1;
	while (++i < 10)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&g_mutex);
	printf("Main: %d\n", g_counter);
	return (0);
}
