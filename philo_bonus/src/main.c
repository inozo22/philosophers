/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:59:51 by nimai             #+#    #+#             */
/*   Updated: 2023/07/11 16:58:16 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @note 230706nimai: you have to send to error, and then, free and exit there
 */
int	destroy_process(t_bundle *bundle)
{
	long	i;
	long	j;
	int		status;

	i = 0;
	while (i < bundle->philos)
	{
		waitpid(-1, &status, 0);
		if (status != SIGKILL)
		{
			j = -1;
			while (++j < bundle->philos)
			{
				printf("MEALS: %ld	i: %ld	j: %ld	bundle->philos: %ld\n", bundle->meals, i, j, bundle->philos);
				kill(bundle->ph[j].pid, SIGKILL);
			}
			if (bundle->meals)
			{
				kill(bundle->pid_watchdog, SIGKILL);
			}
		}
		printf("Line: %d\n", __LINE__);
		i++;
	}
	if (bundle->meals)
		waitpid(-1, &status, 0);
	return (0);
}

/* void	terminator(t_bundle *bundle)
{
	int			i;
	int			status;

	i = -1;
	status = 0;
	while (++i < bundle->philos)
	{
		waitpid(-1, &status, 0);
		if (status != SIGKILL)
		{
			printf("Im here! status: %d\n", status);
			destroy_process(bundle);
		}
		printf("Line: %d Im here! status: %d\n", __LINE__, status);
	}
	printf("Im here! status: %d\n", status);
	if (bundle->meals)
		waitpid(-1, &status, 0);
	if (destroy_process(bundle) == 0)
		all_free(bundle);
} */

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
		return (all_free(bundle), NULL);
	bundle->start = get_time();
	if (bundle->philos == 1)
		loneliness(bundle);
	bundle->ph = (t_philo *)ft_calloc(bundle->philos, sizeof(t_philo));
	if (!bundle->ph)
		return (NULL);
	bundle->heap = HEAP_PH;
	i = -1;
	while (++i < bundle->philos)
	{
		bundle->ph[i].id = i + 1;
		bundle->ph[i].ate = 0;
		bundle->ph[i].last_meal = bundle->start;
		bundle->ph[i].right = 0;
		bundle->ph[i].left = 0;
		bundle->ph[i].bundle = bundle;
	}
	return (bundle);
}

/* void	all_kill(t_bundle *bundle)
{
	int	i;

	i = -1;
	while (++i < bundle->philos)
	{
		kill(bundle->ph[i].pid, SIGKILL);
	}
	if (bundle->meals)
	{
		kill(bundle->pid_watchdog, SIGKILL);
	}
} */

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
 	if (init_sem(bundle))
		return (1);
	if (run(bundle))
		return (1);
	if (bundle->meals && set_eat_counter(bundle))
		return (1);
	destroy_process(bundle);
/* 	i = -1;
	while (++i < bundle->philos)
	{
		waitpid(-1, &status, 0);
		if (status != SIGKILL)
		{
			destroy_process(bundle);
		}
	}
	if (bundle->meals)
		waitpid(-1, &status, 0);
	if (destroy_process(bundle) == 0)
		all_free(bundle); */
	return (0);
}
