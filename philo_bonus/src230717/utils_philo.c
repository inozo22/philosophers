/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:52:37 by nimai             #+#    #+#             */
/*   Updated: 2023/07/12 10:56:45 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief this is a function for one philosopher, maybe better way
 */
void	loneliness(t_bundle *bundle)
{
	long	time;

	time = get_time() - bundle->start;
	printf("%08ld %s%03d %s%s\n", time, CLEAR, 1, MSG_RIGHT, CLEAR);
	time_control(NULL, bundle->time_die);
	time = get_time() - bundle->start;
	printf("%08ld %s%03d %s%s\n", time, RED, 1, MSG_DIED, CLEAR);
	all_free(bundle);
	exit (0);
}
