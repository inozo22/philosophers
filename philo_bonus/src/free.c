/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:18:36 by nimai             #+#    #+#             */
/*   Updated: 2023/07/06 09:26:40 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief free main structure.
 */
void	all_free(t_bundle *bundle)
{
	if (bundle->heap >= 2)
	{
		free (bundle->ph);
		bundle->ph = NULL;
	}
	if (bundle->heap >= 1)
	{
		free (bundle);
		bundle = NULL;
	}
}
