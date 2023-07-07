/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:55:10 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 09:25:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return ((1000 * time.tv_sec) + (time.tv_usec / 1000));
}

void	time_control(t_philo *philo, long time)
{
	long	ret;

	ret = get_time() + time;
	if (philo == NULL)
	{
		while (get_time() < ret)
		{
			usleep(50);
			usleep(50);
		}
	}
	else
	{
		while ((get_time() < ret) && philo->bundle->fin == 0)
		{
			usleep(50);
			usleep(50);
		}
	}
}
