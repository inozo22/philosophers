/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:55:10 by nimai             #+#    #+#             */
/*   Updated: 2023/07/04 15:43:52 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
 * @note flag 0 is start, otherwise return the differ time in long
 * @note 230704nimai: eliminate the flag?
 */
long	get_time(int flag)
{
	struct timeval	time;

	(void)flag;
	gettimeofday (&time, NULL);
	return ((1000 * time.tv_sec) + (time.tv_usec / 1000));
}

void	check_survival(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->death);
	if ((get_time(1) - philo->last_meal) > philo->bundle->time_die
		&& philo->bundle->fin == 0)
	{
		print_philo(philo, MSG_DIED, "\033[1;31m");
		philo->bundle->fin = 1;
	}
	pthread_mutex_unlock(&philo->bundle->death);
}

void	time_control(t_philo *philo, long time)
{
	long	ret;

	ret = get_time(1) + time;
	while ((get_time(1) < ret) && !(philo->bundle->fin))
	{
		check_survival(philo);
		usleep(50);
		usleep(50);
	}
}
