/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:18:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/27 19:20:54 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_free(t_bundle *bundle)
{
	if (bundle->heap >= TH_HEAP)
		free (bundle->th);
	if (bundle->heap >= BUNDLE_HEAP)
		free (bundle);
}
