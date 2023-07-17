/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:49:12 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 10:02:49 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief life control
 */
void	*watchdog(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (!philo->last_meal)
			continue ;
		if (philo->bundle->time_die <= get_time() - philo->last_meal)
		{
			print_philo(philo, MSG_DIED, RED);
			return (NULL);
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
			sem_wait(bundle->ph[i].eat);
			bundle->times_ate[i]++;
			if (bundle->times_ate[i] == bundle->meals)
				counter++;
			if (counter == bundle->philos)
			{
				print_philo(&bundle->ph[i - 1], MSG_COMP, BLUE);
//				break ;
			}
			i++;
		}
	}
//	print_philo(&bundle->ph[i - 1], MSG_COMP, BLUE);
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
