/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:00:08 by nimai             #+#    #+#             */
/*   Updated: 2023/07/04 15:13:51 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meals(t_bundle *bundle)
{
	unsigned int	i;

	pthread_mutex_lock(&bundle->check_meals);
	i = 0;
	while (i < bundle->philos)
	{
		if (bundle->ph[i].ate < bundle->meals)
		{
			pthread_mutex_unlock(&bundle->check_meals);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&bundle->check_meals);
	if (bundle->meals != 0 && !bundle->is_dead)
	{
		print_philo(&bundle->ph[i - 1], MSG_COMP, BLUE);
		bundle->is_dead = 1;
	}
}

/**
 * @brief check all av before start
 * @note it's not necessary, but to protect program
 */
int	check_av(unsigned int num, int flag, t_bundle *bundle)
{
	if (flag == 1 && num > 200)
		return (input_error(2, bundle), 0);
	else if (flag >= 2 && flag <= 4 && num < 60)
		return (input_error(3, bundle), 0);
/* 	if (num < 0)
		input_error(4, bundle); */
	else if (num > 2147483647)
		return (input_error(5, bundle), 0);
	return (1);
}


/**
 * @brief atoi, because there is no libft neither atoi...
 * @return int
 * @note 
 */
long	myatoi(char *str, t_bundle *bundle)
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
			return (input_error(4, bundle), -1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (str[i] - 48) + (nbr * 10);
		i++;
	}
	if (str[i] != '\0')
		return (input_error(6, bundle), -1);
	return (nbr * sign);
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

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1, NULL), NULL);
//	bundle->heap++;
	if (!obtain_nums(av, bundle))
		return (all_free(bundle), NULL);
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

/**
 * @note when should I put "ate"? when the philo finish eat or before? 
 * @note depend on the place of check_meals, you can change the timing of stop.
 * 
 */
void	*routine(void *param)
{
	t_philo		*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0 || philo->id == philo->bundle->philos)
		usleep(200);
	while (philo->bundle->is_dead != 1 && (/* philo->bundle->meals == 0 ||  */philo->ate < philo->bundle->meals))
	{
		check_survival(philo);//
		pthread_mutex_lock(&philo->bundle->forks[philo->right]);
		print_philo(philo, MSG_RIGHT, "\033[0m");
		if (philo->bundle->philos == 1)
		{
			pthread_mutex_unlock(&philo->bundle->forks[philo->right]);// iru?
			break ;
		}
		pthread_mutex_lock(&philo->bundle->forks[philo->left]);
		print_philo(philo, MSG_LEFT, CLEAR);
		pthread_mutex_lock(&philo->bundle->eat);
		print_philo(philo, MSG_EAT, GREEN);
		philo->ate++;
		philo->last_meal = get_time(1);
		pthread_mutex_unlock(&philo->bundle->eat);
		check_meals(philo->bundle);
		time_control(philo, philo->bundle->time_eat);
		pthread_mutex_unlock(&philo->bundle->forks[philo->right]);
		pthread_mutex_unlock(&philo->bundle->forks[philo->left]);
		print_philo(philo, MSG_SLEEP, CYAN);
		time_control(philo, philo->bundle->time_sleep);
		check_survival(philo);
		print_philo(philo, MSG_THINK, YELLOW);
	}
	return (NULL);
}

int	set_thread(t_bundle *bundle)
{
	unsigned int	i = 0;

	pthread_mutex_init(&bundle->check_meals, NULL);
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
		bundle->ph[i].last_meal = bundle->start;
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

/**
 * @note 230703nimai: separate routine between normal and only one philo.
 */
void	hold_thread(t_bundle *bundle)
{
	long	i;

	i = -1;
	while (++i < bundle->philos)
	{
		if (pthread_create(&bundle->ph[i].th, NULL, &routine, &bundle->ph[i]) != 0)
		{
			philo_error(1, bundle);
			return ;
		}
	}
	if (pthread_create(&bundle->watchdog, NULL, &watchdog, bundle) != 0)
	{
		philo_error(2, bundle);
		return ;
	}
	if (bundle->is_dead)
		return ;
}

void	destroy_thread(t_bundle *bundle)
{
	long	i;

	i = -1;
	while (++i < bundle->philos)
	{
		if (pthread_join(bundle->ph[i].th, NULL) != 0)
		{
			philo_error(3, bundle);
			return ;
		}
	}
	if (pthread_join(bundle->watchdog, NULL) != 0)
	{
		philo_error(4, bundle);
		return ;
	}
	pthread_mutex_destroy(&bundle->check_meals);
	pthread_mutex_destroy(&bundle->print);
	pthread_mutex_destroy(&bundle->eat);
	pthread_mutex_destroy(&bundle->death);
	i = -1;
	while (++i < bundle->philos)
		pthread_mutex_destroy(&bundle->forks[i]);
	printf("Destroyed mutexs\n");
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
	bundle->start = get_time(0);
	if (ac == 5)
		bundle->meals = 2147483647;
	if (set_thread(bundle) != 0)
	{
		all_free(bundle);
		return (1);
	}
	hold_thread(bundle);
	destroy_thread(bundle);
	all_free (bundle);
	system ("leaks philo");
	return (0);
}
