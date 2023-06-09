/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:18:36 by nimai             #+#    #+#             */
/*   Updated: 2023/07/09 16:52:10 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief free main structure.
 */
void	all_free(t_bundle *bundle)
{
	if (bundle->heap >= HEAP_FORKS)
	{
		free (bundle->forks);
		bundle->forks = NULL;
	}
	if (bundle->heap >= HEAP_PH)
	{
		free (bundle->ph);
		bundle->ph = NULL;
	}
	if (bundle->heap >= HEAP_BUNDLE)
	{
		free (bundle);
		bundle = NULL;
	}
}
