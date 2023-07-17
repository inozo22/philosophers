/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:49:26 by nimai             #+#    #+#             */
/*   Updated: 2023/07/14 15:19:07 by nimai            ###   ########.fr       */
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
			return (free (name), NULL);
		tmp = name;
		name = ft_strjoin(name, num);
		if (!name)
			return (free (num), free (tmp), NULL);
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

	bundle->start_sem = set_sem("/start", 0, 0);
	bundle->print = set_sem("/print", 1, 0);
	bundle->fork = set_sem("/fork", bundle->philos, 0);
	if (!bundle->start_sem || !bundle->print || !bundle->fork)
		return (close_sem(bundle), all_free(bundle), 1);
	i = -1;
	while (++i < bundle->philos)
	{
		bundle->ph[i].eat = set_sem("/eat_", 0, i + 1);
	}
	return (0);
}
