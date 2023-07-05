/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:58:22 by nimai             #+#    #+#             */
/*   Updated: 2023/07/05 12:05:59 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meals(t_bundle *bundle)
{
	unsigned int	i;

	if (pthread_mutex_lock(&bundle->check_meals) != 0)
		bundle->fin = 99;
	i = 0;
	while (i < bundle->philos)
	{
		if (bundle->ph[i].ate < bundle->meals || bundle->meals == 0)
		{
			if (pthread_mutex_unlock(&bundle->check_meals) != 0)
				bundle->fin = 98;
			return ;
		}
		i++;
	}
	if (pthread_mutex_unlock(&bundle->check_meals) != 0)
		bundle->fin = 98;
	if (bundle->meals != 0 && !bundle->fin)
	{
		print_philo(&bundle->ph[i - 1], MSG_COMP, BLUE);
		bundle->fin = 1;
	}
}

void	print_philo(t_philo *philo, char *msg, char	*color)
{
	long	time;

	if (pthread_mutex_lock(&philo->bundle->print) != 0)
		philo->bundle->fin = 99;
	if (philo->bundle->fin == 0)
	{
		time = get_time() - philo->bundle->start;
		if (ft_strcmp(color, GREEN) == 0)
			printf("%08ld %s%03d %s%s\n", time, color, philo->id, msg, CLEAR);
		else if (ft_strcmp(color, BLUE) == 0)
			printf("%08ld %s%s: %d%s\n", time, color, msg, philo->ate, CLEAR);
		else
			printf("%08ld %s%03d %s%s\n", time, color, philo->id, msg, CLEAR);
	}
	if (pthread_mutex_unlock(&philo->bundle->print) != 0)
		philo->bundle->fin = 98;
}

void	action(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->bundle->forks[philo->right]) != 0)
		philo->bundle->fin = 99;
	print_philo(philo, MSG_RIGHT, CLEAR);
	if (pthread_mutex_lock(&philo->bundle->forks[philo->left]) != 0)
		philo->bundle->fin = 99;
	print_philo(philo, MSG_LEFT, CLEAR);
	if (pthread_mutex_lock(&philo->bundle->eat) != 0)
		philo->bundle->fin = 99;
	philo->ate++;
	print_philo(philo, MSG_EAT, CLEAR);
	philo->last_meal = get_time();
	if (pthread_mutex_unlock(&philo->bundle->eat) != 0)
		philo->bundle->fin = 98;
	check_meals(philo->bundle);
	time_control(philo, philo->bundle->time_eat);
	if (pthread_mutex_unlock(&philo->bundle->forks[philo->right]) != 0)
		philo->bundle->fin = 98;
	if (pthread_mutex_unlock(&philo->bundle->forks[philo->left]) != 0)
		philo->bundle->fin = 98;
}
