/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:49:12 by nimai             #+#    #+#             */
/*   Updated: 2023/07/11 12:24:50 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief life control
 */
void	*watchdog(void *param)
{
	t_philo		*philo;
	long			i;

	philo = (t_philo *)param;
	while (1)
	{
		i = -1;
		while (++i < philo->bundle->philos/*  && bundle->fin == 0 */)
		{
			if (!philo->last_meal)
				continue ;
			if (philo->bundle->time_die <= get_time() - philo->last_meal)
			{
				printf("Line: %d\n", __LINE__);
/* 				if (sem_wait(philo->bundle->print) != 0)
					philo->bundle->fin = 99; */
				print_philo(philo, MSG_DIED, RED);
				return (NULL);
			}
		}
		usleep (200);
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
			printf("BEFORE bundle->ph[%d].ate: %ld\n", i, bundle->ph[i].ate);
			sem_wait(bundle->ph[i].eat);
			bundle->ph[i].ate++;
			printf("AFTER bundle->ph[%d].ate: %ld\n", i, bundle->ph[i].ate);
			if (bundle->ph[i].ate >= bundle->meals - 1)
				counter++;
			if (counter == bundle->philos)
				break ;
			printf("COUNTER: %d\n", counter);
			i++;
		}
	}
	print_philo(&bundle->ph[i - 1], MSG_COMP, BLUE);
//	all_free (bundle);
//	exit (0);
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
