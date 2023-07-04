/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:05:54 by nimai             #+#    #+#             */
/*   Updated: 2023/07/04 16:03:56 by nimai            ###   ########.fr       */
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

/**
 * @brief print with lock the thread
 * @author nimai
 * @note printf("%08ld %s%03d %s: %d%s\n", time, color, philo->id, msg, philo->ate, CLEAR);
 * @note 
 *
 * */
void	print_philo(t_philo *philo, char *msg, char	*color)
{
	long	time;

	pthread_mutex_lock(&philo->bundle->print);
	if (philo->bundle->fin != 1)
	{
		time = get_time(1) - philo->bundle->start;
		if (ft_strcmp(color, GREEN) == 0)
			printf("%08ld %s%03d %s%s\n", time, color, philo->id, msg, CLEAR);
		else if (ft_strcmp(color, BLUE) == 0)
			printf("%08ld %s%s: %d%s\n", time, color, msg, philo->ate, CLEAR);
		else
			printf("%08ld %s%03d %s%s\n", time, color, philo->id, msg, CLEAR);
	}
	pthread_mutex_unlock(&philo->bundle->print);
}
