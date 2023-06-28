/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:18:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/28 10:18:16 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief free all structure.
 * @author nimai
 * @note as the bundle has heap which is a counter for heap memories, you will not double free or free which has not allocated
 */
void	all_free(t_bundle *bundle)
{
	if (bundle->heap >= TH_HEAP)
		free (bundle->th);
	if (bundle->heap >= BUNDLE_HEAP)
		free (bundle);
}
