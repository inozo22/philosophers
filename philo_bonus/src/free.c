/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:18:36 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 16:04:00 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @note maybe conbine with destroyers, then name terminater
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
