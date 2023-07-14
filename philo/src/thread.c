/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:52:59 by nimai             #+#    #+#             */
/*   Updated: 2023/07/14 10:47:54 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	if (philo->bundle->philos == 1)
		return (print_philo(philo, MSG_RIGHT, CLEAR), NULL);
	if (philo->id % 2 == 0 || philo->id == philo->bundle->philos)
		usleep(50);
	while (philo->bundle->fin == 0 && (philo->bundle->meals == 0 || \
	philo->ate < philo->bundle->meals))
	{
		action(philo);
	}
	return (NULL);
}

int	init_mutex(t_bundle *bundle)
{
	long	i;

	i = 0;
	if (pthread_mutex_init(&bundle->check_meals, NULL) != 0 || \
	pthread_mutex_init(&bundle->print, NULL) != 0 || \
	pthread_mutex_init(&bundle->death, NULL) != 0)
		return (philo_error(5, bundle), 1);
	while (i < bundle->philos)
	{
		bundle->ph[i].id = i + 1;
		bundle->ph[i].bundle = bundle;
		bundle->ph[i].last_meal = bundle->start;
		bundle->ph[i].right = i;
		if (i == 0)
			bundle->ph[i].left = bundle->philos - 1;
		else
			bundle->ph[i].left = i - 1;
		bundle->ph[i].ate = 0;
		if (pthread_mutex_init(&bundle->forks[i], NULL) != 0)
			return (philo_error(5, bundle), 1);
		i++;
	}
	return (0);
}

int	set_thread(t_bundle *bundle)
{
	long	i;

	i = -1;
	while (++i < bundle->philos)
	{
		if (pthread_create(&bundle->ph[i].th, NULL, &routine, \
		&bundle->ph[i]) != 0)
			return (philo_error(1, bundle), 1);
	}
	if (pthread_create(&bundle->watchdog, NULL, &watchdog, bundle) != 0)
		return (philo_error(2, bundle), 1);
	return (0);
}

int	destroy(t_bundle *bundle)
{
	long	i;

	i = -1;
	while (++i < bundle->philos)
	{
		if (pthread_join(bundle->ph[i].th, NULL) != 0)
			return (philo_error(3, bundle), 1);
	}
	if (pthread_join(bundle->watchdog, NULL) != 0)
		return (philo_error(4, bundle), 1);
	if (pthread_mutex_destroy(&bundle->check_meals) != 0 || \
	pthread_mutex_destroy(&bundle->print) != 0 || \
	pthread_mutex_destroy(&bundle->death) != 0)
		return (philo_error(6, bundle), 1);
	i = -1;
	while (++i < bundle->philos)
		if (pthread_mutex_destroy(&bundle->forks[i]) != 0)
			return (philo_error(6, bundle), 1);
	return (0);
}
