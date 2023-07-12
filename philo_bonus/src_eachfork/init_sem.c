/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:49:26 by nimai             #+#    #+#             */
/*   Updated: 2023/07/12 09:07:17 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*set_sem(char *sem_name, int amount, int id)
{
	sem_t	*ret;
	char	*name;
	char	*tmp;
	char	*num;

	(void)id;
	name = ft_strdup(sem_name);
	if (!name)
		return (NULL);
	if (id > 0)
	{
		num = ft_itoa(id);
		if (!num)
			return (NULL);//calloc failure put error
		tmp = name;
		name = ft_strjoin(name, num);
		if (!name)
			return (NULL);//calloc failure put error
		free (num);
		free (tmp);
	}
	sem_unlink(name);
	ret = sem_open(name, O_CREAT, 0600, amount);
	free (name);
	return (ret);
}

int	init_sem(t_bundle *bundle)
{
	int	i;

	bundle->print = set_sem("/print", 1, 0);
	bundle->ph[0].fork = set_sem("/fork", bundle->philos, 0);
	i = -1;
	while (++i < bundle->philos)
	{
		bundle->ph[i].eat = set_sem("/eat_", 0, i + 1);
		bundle->ph[i].fork = bundle->ph[0].fork;
	}
	return (0);
}
