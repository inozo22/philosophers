/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/06/30 15:29:28 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief check all av before start
 * @note it's not necessary, but to protect program
 */
void	check_av(unsigned int num, int flag, t_bundle *bundle)
{
	if (flag == 1 && num > 200)
		philo_error(2, bundle);
	if (flag >= 2 && flag <= 4 && num < 60)
		philo_error(3, bundle);
	if (num < 0)
		philo_error(4, bundle);
	if (num > 2147483647)
		philo_error(5, bundle);
}


/**
 * @brief atoi, because there is no libft neither atoi...
 * @return int
 * @note 
 */
unsigned int	myatoi(char *str, t_bundle *bundle)
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
	if (str[i] != '\0')
		philo_error(6, bundle);
	return (nbr * sign);
}

/**
 * @note if there is invalid number, return 0 and terminate the program
 * @note I can put check_av here, but to control error message let it like this
 */
int	obtain_nums(char **av, t_bundle *bundle)
{
	int				i;
	unsigned int	num;

	i = 0;
	while (av[++i])
	{
		num = myatoi(av[i], bundle);
		check_av(num, i, bundle);
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

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		heap_error(1, NULL);
	if (!obtain_nums(av, bundle))
		philo_error (99, bundle);
	/**
	 * initialize the philos here.
	 *  
	 * 
	 * 
	 */
//	printf("bundle->ph[150].is_dead: %d\n", bundle->ph[150].is_dead);
//	printf("bundle->ph[150].ate: %d\n", bundle->ph[150].ate);
	return (bundle);
}

void	*routine(void *param)
{
	t_philo		*philo;
	float		diff_time;

	philo = (t_philo *)param;

	for (int i = 0; i < 1; i++)
	{
		pthread_mutex_lock(&philo->bundle->philos_mutex);
		diff_time = get_time(1);
		printf("%08.0f Philo %03d has taken a fork\n", diff_time, philo->id);
		pthread_mutex_unlock(&philo->bundle->philos_mutex);
	}
	return (NULL);
}

int	run_thread(t_bundle *bundle)
{
//	int cnt = 0;
	unsigned int	i = 0;
	int				*ret;

	pthread_mutex_init(&bundle->philos_mutex, NULL);
	pthread_mutex_init(&bundle->print, NULL);
	pthread_mutex_init(&bundle->eat, NULL);
	pthread_mutex_init(&bundle->death, NULL);
	while (i < bundle->philos)
	{
/* 		bundle->ph[i].th = ft_calloc(1, sizeof(pthread_t));
		if (!bundle->ph[i].th)
			heap_error(2, bundle); */
		bundle->ph[i].id = i + 1;
		bundle->ph[i].bundle = bundle;
		bundle->ph[i].right = i;
		if (i == 0)
			bundle->ph[i].left = bundle->philos - 1;
		else
			bundle->ph[i].left = i - 1;
		pthread_mutex_init(&bundle->forks[i], NULL);
		i++;
	}
//	bundle->heap++;
	i = 0;
	while (i < bundle->philos)
	{
		if (pthread_create(&bundle->ph[i].th, NULL, &routine, &bundle->ph[i]) != 0)
		{
			bundle->status = 1;
			return (bundle->status);
		}
		i++;
	}
	i = 0;
	get_time(0);
	while (i < bundle->philos)
	{
		ret = 0;
		if (pthread_join(bundle->ph[i].th, (void **) &ret) != 0)
		{
			bundle->status = 2;
			return (bundle->status);
		}
		free (ret);
		i++;
	}
	pthread_mutex_destroy(&bundle->philos_mutex);
	pthread_mutex_destroy(&bundle->print);
	pthread_mutex_destroy(&bundle->eat);
	pthread_mutex_destroy(&bundle->death);
	i = 0;
	while (i < bundle->philos)
	{
		pthread_mutex_destroy(&bundle->forks[i]);
		i++;
	}
	printf("Destroyed mutexs\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_bundle	*bundle;

	if (ac < 5 || ac > 6)
		philo_error(1, NULL);
	bundle = init_bundle(av);
	if (!bundle)
		return (1);
	if (run_thread(bundle) != 0)
	{
		//put error message here? using bundle->status
		all_free(bundle);
		return (1);
	}
	printf("bundle->philos: %d\n", bundle->philos);
	printf("bundle->time_die: %d\n", bundle->time_die);
	printf("bundle->time_eat: %d\n", bundle->time_eat);
	printf("bundle->time_sleep: %d\n", bundle->time_sleep);
	printf("bundle->meals: %d\n", bundle->meals);
	all_free (bundle);
//	system ("leaks philo");
	return (0);
}
