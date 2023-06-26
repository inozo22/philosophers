#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t	mutex;

void	*roll_dice(void)
{
	int	value;
	int	*ret;

	value = (rand() % 6) + 1;
	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	*ret = value;
	return ((void *)ret);
}

int	main(int ac, char **av)
{
	int	*ret;
	int	i;
	srand(time(NULL));
	pthread_t	th[8];

	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < 8)
	{
		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
			return (1);
		printf("Thread %d has started\n", i);
	}
	i = -1;
	while (++i < 8)
	{
		if (pthread_join(th[i], (void **) &ret) != 0)
			return (2);
		printf("result[%d]: %d\n", i, *ret);
		printf("Thread %d has finished execution\n", i);
		free (ret);
	}
//	printf("Main ret: %p\n", ret);
/* 	i = -1;
	while (++i < 8)
	{
		printf("result: %d\n", *ret);
	} */
	pthread_mutex_destroy(&mutex);
	printf("Destroyed mutex\n");
	printf("Freed ret\n");
	system ("leaks a.out");
	return (0);
}
