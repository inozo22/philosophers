/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/06/22 16:23:35 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (num < 0)
		return (philo_error(4), false);
	return (true);
}


/**
 * @brief atoi, because there is no libft neither atoi...
 * @return int
 * @note 
 */
int	myatoi(char *str)
{
	unsigned int	i;
	int				nbr;
	int				sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (str[i] - 48) + (nbr * 10);
		i++;
	}
	return (nbr * sign);
}

/**
 * @note if there is invalid number, return 0 and terminate the program
 */
int	obtain_nums(char **av, t_bundle *bundle)
{
	int	i;
	int	num;

	i = 0;
	bundle->meals = 0;
	while (av[++i])
	{
		num = myatoi(av[i]);
		if (!check_av(num, i))
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
 * @note 
 */
t_bundle	*init_bundle(char **av)
{
	t_bundle	*bundle;

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1), NULL);
	if (!obtain_nums(av, bundle))
		return (free (bundle), NULL);
	/**
	 * initialize the philos here.
	 *  
	 * 
	 * 
	 */
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

	printf("bundle->philos: %d\n", bundle->philos);
	printf("bundle->time_die: %d\n", bundle->time_die);
	printf("bundle->time_eat: %d\n", bundle->time_eat);
	printf("bundle->time_sleep: %d\n", bundle->time_sleep);
	printf("bundle->meals: %d\n", bundle->meals);
	return (0);
}
