/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:59:51 by nimai             #+#    #+#             */
/*   Updated: 2023/07/14 11:41:51 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	all_goodbye(t_bundle *bundle)
{
	long	i;

	i = -1;
	while (++i < bundle->philos)
	{
		kill(bundle->ph[i].pid, SIGKILL);
	}
	if (bundle->meals)
	{
		kill(bundle->pid_watchdog, SIGKILL);
	}
}

/**
 * @note 230706nimai: you have to send to error, and then, free and exit there
 */
int	run(t_bundle *bundle)
{
	long	i;
	int		status;

	if (set_philos(bundle))
		return (1);
	if (bundle->meals && set_eat_counter(bundle))
		return (1);
	i = -1;
	while (++i < bundle->philos)
	{
		waitpid(-1, &status, 0);
		if (status != SIGKILL)
		{
			all_goodbye(bundle);
		}
	}
	if (bundle->meals)
		waitpid(-1, &status, 0);
	return (0);
}

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
	t_bundle	*bundle;
	int			i;

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1, NULL), NULL);
	bundle->heap = HEAP_BUNDLE;
	if (!obtain_nums(av, bundle))
	{
		all_free(bundle);
		exit(1);
	}
	if (bundle->philos == 1)
		loneliness(bundle);
	bundle->ph = (t_philo *)ft_calloc(bundle->philos, sizeof(t_philo));
	if (!bundle->ph)
		return (NULL);
	bundle->heap = HEAP_PH;
	bundle->times_ate = (long *)ft_calloc(bundle->philos, sizeof(long));
	i = -1;
	while (++i < bundle->philos)
	{
		bundle->ph[i].id = i + 1;
		bundle->ph[i].ate = 0;
		bundle->ph[i].last_meal = 0;
		bundle->ph[i].right = 0;
		bundle->ph[i].left = 0;
		bundle->ph[i].bundle = bundle;
		bundle->times_ate[i] = 0;
	}
	return (bundle);
}

void	close_sem(t_bundle *bundle)
{
	long	i;

	sem_close(bundle->print);
	sem_close(bundle->fork);
	i = -1;
	while (++i < bundle->philos)
	{
		sem_close(bundle->ph[i].eat);
	}
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
	return (all_free(bundle), 0);
}
