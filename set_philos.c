/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:34:09 by nimai             #+#    #+#             */
/*   Updated: 2023/07/11 18:11:43 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_philo(t_philo *philo, char *msg, char *color)
{
	long	time;

	if (sem_wait(philo->bundle->print) != 0)
		philo->bundle->fin = 99;
	if (philo->bundle->fin == 0)
	{
		time = get_time() - philo->bundle->start;
		if (ft_strcmp(color, GREEN) == 0)
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
		else if (ft_strcmp(color, RED) == 0)
		{
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
			exit (0);
		}
		else if (ft_strcmp(color, BLUE) == 0)
		{
			printf("%08ld %s%s: %ld%s\n", time, color, msg, philo->ate + 1, CLEAR);
			exit (0);
		}
		else
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
	}
	if (sem_post(philo->bundle->print) != 0)
		philo->bundle->fin = 98;
}

int	action_fork(t_philo *philo)
{
	if (sem_wait(philo->bundle->fork) != 0)
		philo->bundle->fin = 99;
	print_philo(philo, MSG_RIGHT, CLEAR);
	if (sem_wait(philo->bundle->fork) != 0)
		philo->bundle->fin = 99;
	print_philo(philo, MSG_LEFT, CLEAR);
	return (0);
}

void	action(t_philo *philo)
{
	action_fork(philo);
	print_philo(philo, MSG_EAT, GREEN);
	sem_post(philo->eat);
	philo->last_meal = get_time();
	time_control(philo, philo->bundle->time_eat);
	print_philo(philo, MSG_SLEEP, CYAN);
	if (sem_post(philo->bundle->fork) != 0)
		philo->bundle->fin = 98;
	if (sem_post(philo->bundle->fork) != 0)
		philo->bundle->fin = 98;
	time_control(philo, philo->bundle->time_sleep);
	print_philo(philo, MSG_THINK, YELLOW);
}

void	*routain(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		action(philo);
	}
	return (NULL);
}

/**
 * @note 230706nimai: if I execute quickly, sometimes doesn't fork watchdog
 */
int	set_philos(t_bundle *bundle)
{
	int	i;

	i = -1;
	while (++i < bundle->philos)
	{
 		bundle->ph[i].pid = fork();
		if (bundle->ph[i].pid < 0)
			return (1);
		if (bundle->ph[i].pid == 0)
		{
			bundle->ph[i].last_meal = bundle->start;
			if (pthread_create(&bundle->ph[i].th, NULL, &watchdog, (void *)&bundle->ph[i]) != 0)
				exit (1);//error
			routain(&bundle->ph[i]);
			pthread_join(bundle->ph[i].th, NULL);
			exit(0);
		}
	}
	return (0);
}
