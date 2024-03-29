/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:59:51 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 13:32:27 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	obtain_nums(char **av, t_bundle *bundle)
{
	int				i;
	long			num;

	i = 0;
	while (av[++i])
	{
		num = myatol(av[i], bundle);
		if (num == -1)
			return (0);
		if (num > INT_MAX)
			return (input_error(5, bundle), 0);
		if (i == 1 && num == 0)
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

void	fill_philo(t_philo *philo)
{
	philo->ate = 0;
	philo->last_meal = 0;
	philo->right = 0;
	philo->left = 0;
}

t_bundle	*init_bundle(char **av)
{
	t_bundle	*bundle;
	int			i;

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1, NULL), NULL);
	bundle->heap = HEAP_BUNDLE;
	obtain_nums(av, bundle);
	if (bundle->philos == 1)
		loneliness(bundle);
	bundle->ph = (t_philo *)ft_calloc(bundle->philos, sizeof(t_philo));
	bundle->times_ate = (long *)ft_calloc(bundle->philos, sizeof(long));
	if (!bundle->ph || !bundle->times_ate)
		return (heap_error(4, bundle), NULL);
	bundle->heap = HEAP_PH;
	bundle->heap = HEAP_TIMES_ATE;
	i = -1;
	while (++i < bundle->philos)
	{
		fill_philo(&bundle->ph[i]);
		bundle->ph[i].id = i + 1;
		bundle->ph[i].bundle = bundle;
		bundle->times_ate[i] = 0;
	}
	return (bundle);
}

int	main(int ac, char **av)
{
	t_bundle	*bundle;

	if (ac < 5 || ac > 6)
		input_error(1, NULL);
	bundle = init_bundle(av);
	if (!bundle)
		return (1);
	if (init_sem(bundle))
		return (1);
	run(bundle);
	close_sem(bundle);
	all_free(bundle);
	return (0);
}
