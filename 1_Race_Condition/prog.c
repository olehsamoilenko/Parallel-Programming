#include <pthread.h>
#include <stdio.h>

int g_counter;

void	*increment(void *arg)
{
	int i = -1;
	while (++i < 100000)
	{
		g_counter++;
		printf("\x1B[32mIncrement\x1B[0m\n");
	}
	return (NULL);
}

void	*decrement(void *arg)
{
	int i = -1;
	while (++i < 100000)
	{
		g_counter--;
		printf("\x1B[31mDecrement\x1B[0m\n");
	}
	return (NULL);
}

int main(void)
{
	pthread_t thread[10];
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
	printf("Main: %d\n", g_counter);
	return (0);
}
