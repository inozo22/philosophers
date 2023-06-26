/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/06/26 16:30:20 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t	mutex;

/**
 * @brief check all av before start
 * @note it's not necessary, but to protect program
 */
bool	check_av(unsigned int num, int flag)
{
	if (flag == 1 && num > 200)
		return (philo_error(2), false);
	if (flag >= 2 && flag <= 4 && num < 60)
		return (philo_error(3), false);
	if (num < 0)
		return (philo_error(4), false);
	if (num > 2147483647)
		return (philo_error(5), false);
	return (true);
}


/**
 * @brief atoi, because there is no libft neither atoi...
 * @return int
 * @note 
 */
unsigned int	myatoi(char *str)
{
	int				i;
	unsigned int	nbr;
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
	int				i;
	unsigned int	num;

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

void	*roll_dice(void)
{
	int	value;
	int	*ret;

	value = (rand() % 6) + 1;
	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	*ret = value;
	return ((void *)ret);
}

void	init_thread(t_bundle *bundle)
{
	pthread_t		*th;
	unsigned int	i;
	int				*ret;
	srand(time(NULL));

	th = malloc(sizeof(pthread_t) * bundle->philos);
	if (!th)
		return ;
	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < bundle->philos)
	{
		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
		{
			perror("Failed to create thread");
			return ;
		}
		printf("Philo %d has started\n", i);
	}
	i = -1;
	while (++i < bundle->philos)
	{
		if (pthread_join(th[i], (void **) &ret) != 0)
		{
			perror("Failed to join thread");
			return ;
		}
		printf("Philo %d dice: %d\n", i, *ret);
		printf("Philo %d has finished execution\n", i);
		free (ret);
	}
	pthread_mutex_destroy(&mutex);
	printf("Destroyed mutex\n");
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
	init_thread(bundle);

	printf("bundle->philos: %d\n", bundle->philos);
	printf("bundle->time_die: %d\n", bundle->time_die);
	printf("bundle->time_eat: %d\n", bundle->time_eat);
	printf("bundle->time_sleep: %d\n", bundle->time_sleep);
	printf("bundle->meals: %d\n", bundle->meals);
	return (0);
}
