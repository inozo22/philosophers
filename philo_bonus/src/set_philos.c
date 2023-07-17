/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:34:09 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 14:02:35 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_philo(t_philo *philo, char *msg, char *color)
{
	long	time;

	sem_wait(philo->bundle->print);
	time = get_time();
	if (ft_strcmp(color, GREEN) == 0)
		printf("%08ld %s%03ld %s: %ld%s\n", time, color, philo->id, \
		msg, philo->ate + 1, CLEAR);
	else if (ft_strcmp(color, RED) == 0)
	{
		if (philo->bundle->time_die <= get_time() - philo->last_meal)
		{
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
			exit (0);
		}
	}
	else if (ft_strcmp(color, BLUE) == 0)
	{
		printf("%08ld %s%s: %ld%s\n", time, color, msg, \
		philo->bundle->times_ate[philo->id - 1], CLEAR);
		exit (0);
	}
	else
		printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
	sem_post(philo->bundle->print);
}

int	action_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep (2000);
	sem_wait(philo->bundle->fork);
	print_philo(philo, MSG_RIGHT, CLEAR);
	sem_wait(philo->bundle->fork);
	print_philo(philo, MSG_LEFT, CLEAR);
	return (0);
}

void	action(t_philo *philo)
{
	action_fork(philo);
	sem_post(philo->eat);
	print_philo(philo, MSG_EAT, CLEAR);
	philo->last_meal = get_time();
	philo->ate++;
	time_control(philo, philo->bundle->time_eat);
	sem_post(philo->bundle->fork);
	sem_post(philo->bundle->fork);
	print_philo(philo, MSG_SLEEP, CLEAR);
	time_control(philo, philo->bundle->time_sleep);
	print_philo(philo, MSG_THINK, CLEAR);
}

/**
 * @note wait all process are started to start process at the same time
 */
void	*routain(void *param)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)param;
	i = -1;
	if (philo->id == philo->bundle->philos)
	{
		while (++i < philo->bundle->philos)
		{
			sem_post(philo->bundle->start_sem);
		}
	}
	sem_wait(philo->bundle->start_sem);
	while (1)
	{
		action(philo);
	}
	return (NULL);
}

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
			if (pthread_create(&bundle->ph[i].th, NULL, &watchdog, \
			(void *)&bundle->ph[i]) != 0)
				exit (1);
			routain(&bundle->ph[i]);
			if (pthread_join(bundle->ph[i].th, NULL) != 0)
				exit(1);
			exit (0);
		}
	}
	return (0);
}
