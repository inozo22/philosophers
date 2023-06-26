/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:23:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/26 16:37:49 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void* arg)
{
	int	index = *(int*)arg;
	printf("%d ", primes[index]);
	free (arg);
	return (arg);
}

int	main(int ac, char **av)
{
	pthread_t	th[10];
	int			i;

	(void)ac;
	(void)av;
	i = -1;
	while (++i < 10)
	{
		int* a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			return (perror("Failed to create thread"), 1);
	}
	i = -1;
	while (++i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (perror("Failed to join thread"), 2);
	}
	return (0);
}
