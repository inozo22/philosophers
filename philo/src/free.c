/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:18:36 by nimai             #+#    #+#             */
/*   Updated: 2023/07/04 13:12:56 by nimai            ###   ########.fr       */
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
//	unsigned int	i;

//	i = 0;
	if (bundle->heap >= TH_HEAP)
	{
/* 		while (i < bundle->philos)
		{
			free (bundle->ph[i].th);
			i++;
		} */
		;
	}
	if (bundle->heap >= BUNDLE_HEAP)
	{
//		bundle->heap = 0;
		printf("free memory\n");
//		free (&bundle);
		bundle = NULL;
	}
}
