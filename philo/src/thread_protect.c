/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_protect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:54:04 by nimai             #+#    #+#             */
/*   Updated: 2023/07/09 16:05:43 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_pthread_mutex_lock(pthread_mutex_t *param, t_bundle *bundle)
{
	if (pthread_mutex_lock(param) != 0)
		bundle->fin = ERR_MUTEX_LOCK;
}

void	my_pthread_mutex_unlock(pthread_mutex_t *param, t_bundle *bundle)
{
	if (pthread_mutex_unlock(param) != 0)
		bundle->fin = ERR_MUTEX_UNLOCK;
}
