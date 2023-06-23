/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:19:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/23 12:47:20 by nimai            ###   ########.fr       */
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
	for (int i = 0; i < 1000; i++)
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
	while (++i < 4)
	{
		if (!pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (perror ("Failed to create thread"), 1);
		if (!pthread_join(th[i], NULL) != 0)
			return (perror ("Failed to join thread"), 2);
	}
/* 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
	{
		return (2);
	}
	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
	{
		return (3);
	}
	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
	{
		return (4);
	}*/
/* 	if (pthread_join(t1, NULL) != 0)
	{
		return (5);
	}
	if (pthread_join(t2, NULL) != 0)
	{
		return (6);
	}
	if (pthread_join(t3, NULL) != 0)
	{
		return (7);
	}
	if (pthread_join(t4, NULL) != 0)
	{
		return (8);
	}  */
	printf("Number of mails: %d\n", mails);
/* 	if (ac < 4)
		return (philo_error(1), 0); */
	//check amount of philo, and die time before allocate memory
	pthread_mutex_destroy(&mutex);
	printf("Destroyed mutex\n");
	return (0);
}
