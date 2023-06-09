/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/06/09 18:10:12 by nimai            ###   ########.fr       */
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

/**
 * @brief check all av before start
 * @note it's not necessary, but to protect programm
 */
bool	check_av(int num, int flag)
{
	int	i;

	(void)flag;
	i = 0;
	if (num > 200)
		return (false);

	return (true);
}

/**
 * @brief initialization according to the av position
 * @return main structure
 * @note 230609nimai: OMW
 */
t_bundle	*init_bundle(char **av)
{
	t_bundle	*ret;
	int			i;
	int			num;

	i = 0;
	ret = NULL;
	ret = (t_bundle *)malloc(sizeof(t_bundle));
	if (!ret)
		return (NULL);
	while (av[i])
	{
		num = myatoi(av[i]);
		if (!check_av(num, i))
			return (NULL);
		if (i == 1)
			ret->philos = num;
		if (i == 2)
		{
			ret->time_die = num;
		}
		if (i == 3)
		{
			ret->time_eat = num;
		}
		if (i == 4)
		{
			;
		}
		if (i == 5)
		{
			;
		}
	}

		philo_error(2);
	return(ret);
}

int	main(int ac, char **av)
{
	t_bundle	*bundle;

	if (ac < 5 || ac > 6)
	{
		philo_error(1);
	}
	bundle = init_bundle(av);
	if (!bundle)
		return (0);
	int i = -1;
	while (av[++i])
		printf("av[%d]: %s\n", i, av[i]);
	return (0);
}
