/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:05:54 by nimai             #+#    #+#             */
/*   Updated: 2023/06/30 17:19:20 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, char *msg, char	*color)
{
	float	diff_time;

	pthread_mutex_lock(&philo->bundle->print);
	diff_time = get_time(1);
	printf("%08.0f %sPhilo %03d %s\033[0m\n", diff_time, color, philo->id, msg);
	pthread_mutex_unlock(&philo->bundle->print);
}
