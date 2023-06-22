/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:19:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/22 13:06:37 by nimai            ###   ########.fr       */
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
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int	main(int ac, char **av)
{
	pthread_t		t1;
	pthread_t		t2;

	(void)av;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
	{
		return (2);
	}
	if (pthread_join(t1, NULL) != 0)
	{
		return (3);
	}
	if (pthread_join(t2, NULL) != 0)
	{
		return (4);
	}
	printf("Number of mails: %d\n", mails);
/* 	if (ac < 4)
		return (philo_error(1), 0); */
	//check amount of philo, and die time before allocate memory
	pthread_mutex_destroy(&mutex);
	printf("Destroyed mutex\n");
	return (0);
}
