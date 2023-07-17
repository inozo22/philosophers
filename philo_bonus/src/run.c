/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:21:27 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 13:23:58 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	all_goodbye(t_bundle *bundle)
{
	long	i;

	i = -1;
	while (++i < bundle->philos)
	{
		kill(bundle->ph[i].pid, SIGKILL);
	}
	if (bundle->meals)
	{
		kill(bundle->pid_watchdog, SIGKILL);
	}
}

int	run(t_bundle *bundle)
{
	int		status;

	if (set_philos(bundle))
		return (1);
	if (bundle->meals && set_eat_counter(bundle))
		return (1);
	waitpid(-1, &status, 0);
	all_goodbye(bundle);
	return (0);
}
