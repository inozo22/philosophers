/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:49:12 by nimai             #+#    #+#             */
/*   Updated: 2023/07/04 15:44:37 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watchdog(void *param)
{
	t_bundle		*bundle;
	long			i;

	bundle = (t_bundle *)param;
	while (!bundle->fin)
	{
		i = -1;
		while (++i < bundle->philos)
		{
			check_survival(&bundle->ph[i]);
			if (bundle->fin)
				break ;
		}
	}
	return (NULL);
}
