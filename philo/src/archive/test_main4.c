/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:23:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/26 15:41:35 by nimai            ###   ########.fr       */
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
	int	sum = 0;
	int	i = -1;
	while (++i < 5)
	{
		sum += primes[index + i];
	}
	*(int*)arg = sum;
	printf("sum: %d\n", sum);
	return (arg);
}

int	main(int ac, char **av)
{
	pthread_t	th[2];
	int			i;

	i = -1;
	while (++i < 2)
	{
		int* a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			return (perror("Failed to create thread"), 1);
	}
	i = -1;
	int	globalSum = 0;
	while (++i < 2)
	{
		int	*r;
		if (pthread_join(th[i], (void **) &r) != 0)
			return (perror("Failed to join thread"), 2);
		globalSum += *r;
		free (r);
	}
	printf ("globalSum: %d\n", globalSum);
	return (0);
}
