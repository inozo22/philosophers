/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/07/05 11:29:33 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief check all av before start
 * @note it's not necessary, but to protect program
 */
int	check_av(unsigned int num, int flag, t_bundle *bundle)
{
	if (num > 2147483647)
		return (input_error(5, bundle), 0);
	else if (flag == 1 && num > 200)
		return (input_error(2, bundle), 0);
	else if (flag >= 2 && flag <= 4 && num < 60)
		return (input_error(3, bundle), 0);
	return (1);
}

/**
 * @note if there is invalid number, return 0 and terminate the program
 * @note I can put check_av here, but to control error message let it like this
 */
int	obtain_nums(char **av, t_bundle *bundle)
{
	int				i;
	long			num;

	i = 0;
	while (av[++i] && !bundle->status)
	{
		num = myatoi(av[i], bundle);
		if (num == -1 || !check_av(num, i, bundle))
			return (0);
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

/**
 * @brief initialization according to the av position
 * @return main structure
 * @note maybe put obtain_nums here if I will not put more lines here
 */
t_bundle	*init_bundle(char **av)
{
	t_bundle	*bundle;

	bundle = NULL;
	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1, NULL), NULL);
	if (!obtain_nums(av, bundle))
		return (all_free(bundle), NULL);
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
	system ("leaks philo");
	return (0);
}
