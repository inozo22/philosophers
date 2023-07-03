/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:05:54 by nimai             #+#    #+#             */
/*   Updated: 2023/07/03 10:13:52 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @note for debug, maybe I will delete it later 
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
	{
		if (!s2)
			return (0);
		else
			return (-s2[0]);
	}
	else if (!s2)
		return (*s1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_philo(t_philo *philo, char *msg, char	*color)
{
	float	diff_time;

	pthread_mutex_lock(&philo->bundle->print);
	if (philo->bundle->is_dead != 1)
	{
		diff_time = get_time(1);
		if (ft_strcmp(color, "\033[1;32m") == 0)
			printf("%08.0f %sPhilo %03d %s: %d\033[0m\n", diff_time, color, philo->id, msg, philo->ate + 1);
		else
			printf("%08.0f %sPhilo %03d %s\033[0m\n", diff_time, color, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->bundle->print);
}
