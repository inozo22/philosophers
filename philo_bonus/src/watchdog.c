/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:49:12 by nimai             #+#    #+#             */
/*   Updated: 2023/07/09 18:13:24 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief life control
 */
void	*watchdog(void *param)
{
	t_bundle		*bundle;
	long			i;

	bundle = (t_bundle *)param;
	while (bundle->fin == 0)
	{
		i = 0;
		while (++i < bundle->philos/*  && bundle->fin == 0 */)
		{
			printf("Im hereeeeee!\n");
			if (sem_wait(bundle->print) != 0)
				bundle->fin = 99;
			if ((get_time() - bundle->ph[i].last_meal) > \
			bundle->time_die && bundle->fin == 0)
			{
				print_philo(&bundle->ph[i], MSG_DIED, RED);
				bundle->fin = 1;//maybe I can remove this
				all_free (bundle);
				exit (0);
				return (0);
			}
			if (sem_post(bundle->print) != 0)
				bundle->fin = 99;
			i++;
		}
	}
	return (NULL);
}

void	eat_counter(t_bundle *bundle)
{
	int	i;
	int	counter;

	counter = 0;
	while (counter < bundle->philos)
	{
		i = 0;
		while (i < bundle->philos)
		{
			sem_wait(bundle->ph[i].eat);
			bundle->ph[i].ate++;
			if (bundle->ph[i].ate == bundle->meals)
				counter++;
			i++;
		}
		usleep(100);
		usleep(100);
	}
	printf("they all ate required times!\n");
	all_free (bundle);
	exit (0);
}

/**
 * @brief meal control
 */
int	set_eat_counter(t_bundle *bundle)
{
	bundle->pid_watchdog = fork();
	if (bundle->pid_watchdog < 0)
		return (1);
	if (bundle->pid_watchdog == 0)
	{
		eat_counter(bundle);
	}
	return (0);
}
