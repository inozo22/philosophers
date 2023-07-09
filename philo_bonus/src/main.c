/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:59:51 by nimai             #+#    #+#             */
/*   Updated: 2023/07/09 09:50:48 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @note 230706nimai: you have to send to error, and then, free and exit there
 */
int	destroy_process(t_bundle *bundle)
{
	long	i;

	i = -1;
	while (++i < bundle->philos)
	{
		if (kill(bundle->ph[i].pid, SIGKILL) != 0)
			return (1);
	}
	if (kill(bundle->pid_watchdog, SIGKILL) != 0)
		return (1);
	return (0);
}

int	check_input(unsigned int num, int flag, t_bundle *bundle)
{
	if (num > 2147483647)
		return (input_error(5, bundle), 0);
	else if (flag == 1 && num > 200)
		return (input_error(2, bundle), 0);
	else if (flag >= 2 && flag <= 4 && num < 60)
		return (input_error(3, bundle), 0);
	return (1);
}

int	obtain_nums(char **av, t_bundle *bundle)
{
	int				i;
	long			num;

	i = 0;
	while (av[++i] && !bundle->status)
	{
		num = myatoi(av[i], bundle);
		if (num == -1 || !check_input(num, i, bundle))
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

t_bundle	*init_bundle(char **av)
{
	t_bundle	*bundle;
	int			i;

	bundle = (t_bundle *)ft_calloc(1, sizeof(t_bundle));
	if (!bundle)
		return (heap_error(1, NULL), NULL);
	bundle->heap++;
	if (!obtain_nums(av, bundle))
		return (all_free(bundle), NULL);
	bundle->start = get_time();
	if (bundle->philos == 1)
		loneliness(bundle);
	bundle->ph = (t_philo *)ft_calloc(bundle->philos, sizeof(t_philo));
	if (!bundle->ph)
		return (NULL);
	bundle->heap++;
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
	int			i;
	int			status;

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
	i = -1;
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
		all_free(bundle);
//	system ("leaks philo_bonus");
	return (0);
}

/* void	*function(void *param)
{
	sem_t *sem2 = param;
	int	i = 0;

	while (i < 5)
	{
		sem_wait(sem2);
		printf("[function]%d called\n", i);
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	sem_t		*sem;
	sem_t		*sem2;
	pid_t		pid;
	pid_t		cpid[2];
	int			status;
	pthread_t	thread;
	int	i = 0;

	(void)ac;
	(void)av;
	sem_unlink("/philo");
	sem = sem_open("/philo", O_CREAT, 0600, atoi(av[1]) / 2);// "/" から始まれば名前付きsem。同じ名前で共有できる。
	sem2 = sem;
	sem_unlink("/philo");
	pid = fork();

	while (i < 2)
	{
		if (pid != 0)
		{
			cpid[i] = fork();
		}
		i++;
	}
	while (1)
	{
		;
	}
	exit (1);
	if (pid == 0)
	{
		printf("");
		printf("child pid: %d\n", pid);
		pthread_create(&thread, NULL, &function, sem2);
		pthread_join(thread, NULL);
		exit (0);
	}
	int microsecond = 1.5 * 1000000;
	i = 0;
	while (i < 3)
	{
		printf("parent pid: %d\n", pid);
		usleep(microsecond);
		sem_post(sem);
		i++;
	}
	waitpid(-1, &status, 0);
	sem_close(sem);
	return (0);
} */
