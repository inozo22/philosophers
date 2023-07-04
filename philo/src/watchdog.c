/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:49:12 by nimai             #+#    #+#             */
/*   Updated: 2023/07/04 10:18:28 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watchdog(void *param)
{
	t_bundle		*bundle;
	unsigned int	i;

	bundle = (t_bundle *)param;
	while (!bundle->is_dead)
	{
		i = -1;
		while (++i < bundle->philos)
		{
			check_survival(&bundle->ph[i]);
			if (bundle->is_dead)
				break ;
		}
	}
	return (NULL);
}
