/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:58:22 by nimai             #+#    #+#             */
/*   Updated: 2023/07/14 10:29:19 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meals(t_bundle *bundle)
{
	long	i;

	i = 0;
	while (i < bundle->philos)
	{
		if (bundle->ph[i].ate < bundle->meals || bundle->meals == 0)
		{
			return ;
		}
		i++;
	}
	if (bundle->meals != 0 && !bundle->fin)
	{
		print_philo(&bundle->ph[i - 1], MSG_COMP, BLUE);
		bundle->fin = 1;
	}
}

/**
 * @note if (ft_strcmp(color, GREEN) == 0)
 * printf("%08ld %s%03d %s: %u%s\n", time, color, philo->id, msg, 
 * philo->ate, CLEAR);
 */
void	print_philo(t_philo *philo, char *msg, char	*color)
{
	long	time;

	my_pthread_mutex_lock(&philo->bundle->print, philo->bundle);
	if (philo->bundle->fin == 0)
	{
		time = get_time() - philo->bundle->start;
		if (ft_strcmp(color, BLUE) == 0)
			printf("%08ld %s%s: %ld%s\n", time, color, msg, philo->ate, CLEAR);
		else if (ft_strcmp(color, GREEN) == 0)
			printf("%08ld %s%03ld %s: %ld%s\n", time, color, philo->id, \
			msg, philo->ate, CLEAR);
		else if (ft_strcmp(color, RED) == 0)
		{
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
			philo->bundle->fin = 1;
		}
		else
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
	}
	my_pthread_mutex_unlock(&philo->bundle->print, philo->bundle);
}

void	action(t_philo *philo)
{
	my_pthread_mutex_lock(&philo->bundle->forks[philo->right], philo->bundle);
	print_philo(philo, MSG_RIGHT, CLEAR);
	my_pthread_mutex_lock(&philo->bundle->forks[philo->left], philo->bundle);
	print_philo(philo, MSG_LEFT, CLEAR);
	philo->ate++;
	print_philo(philo, MSG_EAT, CLEAR);
	philo->last_meal = get_time();
	check_meals(philo->bundle);
	time_control(philo, philo->bundle->time_eat);
	print_philo(philo, MSG_SLEEP, CLEAR);
	my_pthread_mutex_unlock(&philo->bundle->forks[philo->right], philo->bundle);
	my_pthread_mutex_unlock(&philo->bundle->forks[philo->left], philo->bundle);
	time_control(philo, philo->bundle->time_sleep);
	print_philo(philo, MSG_THINK, CLEAR);
}
