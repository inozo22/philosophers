/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:49:12 by nimai             #+#    #+#             */
/*   Updated: 2023/07/14 10:51:58 by nimai            ###   ########.fr       */
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
			my_pthread_mutex_lock(&bundle->death, bundle);
			if ((get_time() - bundle->ph[i].last_meal) > \
			bundle->time_die && bundle->fin == 0)
			{
				print_philo(&bundle->ph[i], MSG_DIED, RED);
				bundle->fin = 1;
			}
			my_pthread_mutex_unlock(&bundle->death, bundle);
		}
	}
	return (NULL);
}
