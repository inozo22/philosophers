/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:55:10 by nimai             #+#    #+#             */
/*   Updated: 2023/07/05 11:29:24 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @note flag 0 is start, otherwise return the differ time in long
 * @note 230704nimai: eliminate the flag?
 */
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
	while ((get_time() < ret) && philo->bundle->fin == 0)
	{
		check_survival(philo);
		usleep(50);
		usleep(50);
	}
}
