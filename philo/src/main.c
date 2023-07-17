/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 09:08:44 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	obtain_nums(char **av, t_bundle *bundle)
{
	int				i;
	long			num;

	i = 0;
	while (av[++i] && !bundle->status)
	{
		num = myatol(av[i], bundle);
		if (num == -1)
			return (0);
		if (num > INT_MAX)
			return (input_error(5, bundle), 0);
		if (num == 0)
			return (input_error(2, bundle), 0);
		if (i == 1)
			bundle->philos = num;
		if (i == 2)
			bundle->time_die = num;
		if (i == 3)
			bundle->time_eat = num;
		if (i == 4)
			bundle->time_sleep = num;
		if (i == 5)
			bundle->meals = num;
	}
	return (1);
}

t_bundle	*init_bundle(char **av)
{
	t_bundle		*bundle;

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1, NULL), NULL);
	bundle->heap = HEAP_BUNDLE;
	if (!obtain_nums(av, bundle))
		return (all_free(bundle), NULL);
	bundle->forks = (pthread_mutex_t *)ft_calloc(bundle->philos, \
	sizeof(pthread_mutex_t));
	if (!bundle->forks)
		return (heap_error(2, bundle), NULL);
	bundle->heap = HEAP_FORKS;
	bundle->ph = (t_philo *)ft_calloc(bundle->philos, sizeof(t_philo));
	if (!bundle->ph)
		return (heap_error(3, bundle), NULL);
	bundle->heap = HEAP_PH;
	return (bundle);
}

int	main(int ac, char **av)
{
	t_bundle	*bundle;

	if (ac < 5 || ac > 6)
	{
		input_error(1, NULL);
		return (1);
	}
	bundle = init_bundle(av);
	if (!bundle)
		return (1);
	bundle->start = get_time();
	if (init_mutex(bundle))
		return (1);
	if (set_thread(bundle))
		return (1);
	if (bundle->fin > 1)
		printf("PTHEREAD ERROR: %d\n", bundle->fin);
	if (destroy(bundle) == 0)
		all_free (bundle);
	return (0);
}
