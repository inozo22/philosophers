/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/06/30 18:25:19 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meals(t_bundle *bundle)
{
	unsigned int	i;

	pthread_mutex_lock(&bundle->philos_mutex);
	i = 0;
	while (i < bundle->philos)
	{
		if (bundle->ph[i].ate < bundle->meals)
		{
			pthread_mutex_unlock(&bundle->philos_mutex);
			return ;
		}
		i++;
	}
	if (bundle->meals != 0)
	{
		all_free(bundle);
		printf("\033[1;34mThey all ate the required number of meals🥳\n\033[0m");
		exit (0);
	}
}

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

	philo = (t_philo *)param;
	if (philo->id % 2 == 0 || philo->id == philo->bundle->philos || philo->ate)
		usleep(200);
	pthread_mutex_lock(&philo->bundle->forks[philo->right]);
//	printf("Philo: %d, Fork[%d]\n", philo->id, philo->right);
	print_philo(philo, "has taken a right fork", "\033[0m");
	pthread_mutex_lock(&philo->bundle->forks[philo->left]);
//	printf("Philo: %d, Fork[%d]\n", philo->id, philo->left);
	print_philo(philo, "has taken a left fork", "\033[0m");
	print_philo(philo, "is eating", "\033[1;32m");
	philo->ate++;
	philo->last_meal = get_time(1);
	pthread_mutex_lock(&philo->bundle->eat);
	check_meals(philo->bundle);
	usleep(philo->bundle->time_eat);
	pthread_mutex_unlock(&philo->bundle->eat);
	print_philo(philo, "is sleeping", "\033[1;36m");
	pthread_mutex_unlock(&philo->bundle->forks[philo->left]);
	pthread_mutex_unlock(&philo->bundle->forks[philo->right]);
	usleep(philo->bundle->time_sleep);
	print_philo(philo, "is thinking", "\033[1;33m");
	return (NULL);
}

int	set_thread(t_bundle *bundle)
{
	unsigned int	i = 0;

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
	return (0);
}

void	hold_thread(t_bundle *bundle)
{
	unsigned int	i;

	i = 0;
	while (i < bundle->philos)
	{
/* 		if (bundle->ph[i].id % 2 == 0 || bundle->ph[i].id == bundle->philos)
			usleep(500); */
		if (pthread_create(&bundle->ph[i].th, NULL, &routine, &bundle->ph[i]) != 0)
		{
			bundle->status = 1;
		}
//		usleep(10);
		i++;
	}
}

void	destroy_thread(t_bundle *bundle)
{
	unsigned int	i;

	i = 0;
	while (i < bundle->philos)
	{
		if (pthread_join(bundle->ph[i].th, NULL) != 0)
		{
			bundle->status = 2;
//			return (bundle->status);
		}
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
}

int	main(int ac, char **av)
{
	t_bundle	*bundle;

	if (ac < 5 || ac > 6)
		philo_error(1, NULL);
	bundle = init_bundle(av);
	if (!bundle)
		return (1);
	if (set_thread(bundle) != 0)
	{
		//put error message here? using bundle->status
		all_free(bundle);
		return (1);
	}
	get_time(0);
	hold_thread(bundle);
	destroy_thread(bundle);
	all_free (bundle);
//	system ("leaks philo");
	return (0);
}
