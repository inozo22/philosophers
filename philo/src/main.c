/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/06/22 13:59:49 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief atoi, because there is no libft neither atoi...
 * @return int
 * @note 230609nimai: OMW
 */
int	myatoi(char *str)
{
	int	ret;

	ret = 0;
	(void)str;
	return (ret);
}

void	obtain_nums(av)
{
	while (av[++i])
	{
		num = myatoi(av[i]);
		if (!check_av(num, i))
			return (NULL);
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
	
}

/**
 * @brief check all av before start
 * @note it's not necessary, but to protect program
 */
bool	check_av(int num, int flag)
{
	if (flag == 1 && num > 200)
		return (philo_error(2), false);
	if (flag >= 2 && flag <= 4 && num < 60)
		return (philo_error(3), false);
	return (true);
}

/**
 * @brief initialization according to the av position
 * @return main structure
 * @note 
 */
t_bundle	*init_bundle(char **av)
{
	t_bundle	*bundle;
	int			i;
	int			num;

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1), NULL);
	i = 0;
/* 	while (av[++i])
	{
		num = myatoi(av[i]);
		if (!check_av(num, i))
			return (NULL);
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
	} */
	return (bundle);
}

int	main(int ac, char **av)
{
	t_bundle	*bundle;

	if (ac < 5 || ac > 6)
	{
		philo_error(1);
		return (1);
	}
	bundle = init_bundle(av);
	if (!bundle)
		return (1);
	int i = -1;
	while (av[++i])
		printf("av[%d]: %s\n", i, av[i]);
	return (0);
}
