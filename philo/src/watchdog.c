/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:49:12 by nimai             #+#    #+#             */
/*   Updated: 2023/07/05 12:00:41 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watchdog(void *param)
{
	t_bundle		*bundle;
	long			i;

	bundle = (t_bundle *)param;
	while (bundle->fin == 0)
	{
		i = -1;
		while (++i < bundle->philos && bundle->fin == 0)
		{
			if (pthread_mutex_lock(&bundle->death) != 0)
				bundle->fin = 99;
			if ((get_time() - bundle->ph[i].last_meal) > \
			bundle->time_die && bundle->fin == 0)
			{
				print_philo(&bundle->ph[i], MSG_DIED, RED);
				bundle->fin = 1;
			}
			if (pthread_mutex_unlock(&bundle->death) != 0)
				bundle->fin = 98;
		}
	}
	return (NULL);
}
