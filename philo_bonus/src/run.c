/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:34:09 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 16:06:29 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_philo(t_philo *philo, char *msg, char *color)
{
	long	time;

	if (sem_wait(philo->bundle->print) != 0)
		philo->bundle->fin = 99;
	if (philo->bundle->fin == 0)
	{
		time = get_time() - philo->bundle->start;
		if (ft_strcmp(color, GREEN) == 0)
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
		else if (ft_strcmp(color, BLUE) == 0)
			printf("%08ld %s%s: %ld%s\n", time, color, msg, philo->ate, CLEAR);
		else
			printf("%08ld %s%03ld %s%s\n", time, color, philo->id, msg, CLEAR);
	}
	if (sem_post(philo->bundle->print) != 0)
		philo->bundle->fin = 98;
}

/* void	check_meals(t_bundle *bundle)
{
//	(void)bundle;
	unsigned int	i;

 	if (pthread_mutex_lock(&bundle->check_meals) != 0)
		bundle->fin = 99; 
	i = 0;
	while (i < bundle->philos)
	{
		if (bundle->ph[i].ate < bundle->meals || bundle->meals == 0)
		{
 			if (pthread_mutex_unlock(&bundle->check_meals) != 0)
				bundle->fin = 98; 
			return ;
		}
		i++;
	}
 	if (pthread_mutex_unlock(&bundle->check_meals) != 0)
		bundle->fin = 98; 
	if (bundle->meals != 0 && !bundle->fin)
	{
		print_philo(&bundle->ph[i - 1], MSG_COMP, BLUE);
		bundle->fin = 1;
	}
} */

int	action_fork(t_philo *philo)
{
	if (philo->id % 2 == 0 || philo->id == philo->bundle->philos)
		usleep(200);
	if (sem_wait(philo->bundle->fork) != 0)
		philo->bundle->fin = 99;
	print_philo(philo, MSG_RIGHT, CLEAR);
	if (sem_wait(philo->bundle->fork) != 0)
		philo->bundle->fin = 99;
	print_philo(philo, MSG_LEFT, CLEAR);
	return (0);
}

void	action(t_philo *philo)
{
	action_fork(philo);
	print_philo(philo, MSG_EAT, GREEN);
	if (sem_post(philo->eat) != 0)
		philo->bundle->fin = 99;
	philo->last_meal = get_time();
	if (sem_post(philo->eat) != 0)
		philo->bundle->fin = 98;
//	check_meals(philo->bundle);
	time_control(philo, philo->bundle->time_eat);
	//KOKOMADE
	if (sem_post(philo->bundle->fork) != 0)
		philo->bundle->fin = 98;
	if (sem_post(philo->bundle->fork) != 0)
		philo->bundle->fin = 98;
}

void	*routain(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0 || philo->id == philo->bundle->philos)
		usleep(200);
	while (philo->bundle->fin == 0 && (philo->bundle->meals == 0 || \
	philo->ate < philo->bundle->meals))
	{
		action(philo);
		print_philo(philo, MSG_SLEEP, CYAN);
		time_control(philo, philo->bundle->time_sleep);
		print_philo(philo, MSG_THINK, YELLOW);
	}
	return (NULL);
}

/**
 * @note 230706nimai: if I execute quickly, sometimes doesn't fork watchdog
 */
int	run(t_bundle *bundle)
{
	int	i;

	i = -1;
	while (++i < bundle->philos)
	{
		bundle->ph[i].pid = fork();
		if (bundle->ph[i].pid < 0)
			return (1);
		if (bundle->ph[i].pid == 0)
		{
			if (pthread_create(&bundle->ph[i].th, NULL, &watchdog, (void *)&bundle->ph[i]) != 0)
				exit (1);//error
			routain(&bundle->ph[i]);
			pthread_join(bundle->ph[i].th, NULL);
			exit(0);
		}
	}
/* 	bundle->pid_watchdog = fork();
	if (bundle->pid_watchdog < 0)
		return (1);
	if (bundle->pid_watchdog == 0)
	{
		printf("Hello, I'm watchdog!\n");
		func();
	} */
	return (0);
}

