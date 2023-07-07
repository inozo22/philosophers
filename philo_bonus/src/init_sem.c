/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:49:26 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 12:50:59 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

sem_t	*set_sem(char *sem_name, int amount, int id)
{
	sem_t	*ret;
	char	*name;

	(void)id;
	name = ft_strdup(sem_name);
	if (!name)
		return (NULL);

	sem_unlink(name);
	ret = sem_open(name, O_CREAT, 0600, amount);
	free (name);
	return (ret);
}

int	init_sem(t_bundle *bundle)
{
	bundle->print = set_sem("/print", 1, 0);
	bundle->ph[0].fork = set_sem("/fork", bundle->philos, 0);
	return (0);
}
