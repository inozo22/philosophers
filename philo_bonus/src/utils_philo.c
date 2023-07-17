/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:52:37 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 13:37:44 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief this is a function for one philosopher, maybe better way
 */
void	loneliness(t_bundle *bundle)
{
	long	time;

	time = get_time();
	printf("%08ld %s%03d %s%s\n", time, CLEAR, 1, MSG_RIGHT, CLEAR);
	time_control(NULL, bundle->time_die);
	time = get_time();
	printf("%08ld %s%03d %s%s\n", time, RED, 1, MSG_DIED, CLEAR);
	all_free(bundle);
	exit (0);
}

long	myatol(char *str, t_bundle *bundle)
{
	int				i;
	unsigned int	nbr;
	int				sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (input_error(4, bundle), -1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (str[i] - 48) + (nbr * 10);
		i++;
	}
	if (str[i] != '\0')
		return (input_error(6, bundle), -1);
	if (i > 10)
		return (input_error(5, bundle), -1);
	return (nbr * sign);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*pmem;

	len = ft_strlen(s1) + ft_strlen(s2);
	pmem = malloc(len + 1);
	if (pmem == NULL)
		return (NULL);
	ft_strlcpy(pmem, s1, ft_strlen(s1) + 1);
	ft_strlcat(pmem, s2, len + 1);
	return (pmem);
}

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	t = malloc(len + 1);
	i = 0;
	if (t == NULL)
		return (NULL);
	while (s[i])
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}

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
