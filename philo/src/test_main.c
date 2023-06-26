/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:19:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/26 12:41:42 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int	mails = 0;

pthread_mutex_t	mutex;

void*	routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int	main(int ac, char **av)
{
	pthread_t		th[4];
	int				i;

	i = -1;
	(void)av;
	pthread_mutex_init(&mutex, NULL);
	while (++i < 8)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (perror ("Failed to create thread"), 1);
		printf("Thread %d has started\n", i);
	}
	i = -1;
	while (++i < 8)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (perror ("Failed to join thread"), 2);
		printf("Thread %d has finished execution\n", i);
	}
	printf("Number of mails: %d\n", mails);
/* 	if (ac < 4)
		return (philo_error(1), 0); */
	//check amount of philo, and die time before allocate memory
	pthread_mutex_destroy(&mutex);
	printf("Destroyed mutex\n");
	return (0);
}
