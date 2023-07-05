/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:59:51 by nimai             #+#    #+#             */
/*   Updated: 2023/07/05 13:23:05 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>//kesu

void	*function(void *param)
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
	int			status;
	pthread_t	thread;
	int	i = 0;

	(void)ac;
	(void)av;
	sem_unlink("/aaa");
	sem = sem_open("/aaa", O_CREAT, 0600, 5);// "/" から始まれば名前付きsem。同じ名前で共有できる。
	sem2 = sem;
	sem_unlink("/aaa");
	pid = fork();
	if (pid == 0)
	{
		printf("child pid: %d\n", pid);
		pthread_create(&thread, NULL, &function, sem2);
		pthread_join(thread, NULL);
		exit (0);
	}
	int microsecond = 1.5 * 1000000;
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
}
