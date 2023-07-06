/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:34:09 by nimai             #+#    #+#             */
/*   Updated: 2023/07/06 14:14:29 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	func(void)
{
	while (1)
	{
		;
	}
}

int	run(t_bundle *bundle)
{
	int	i;

	i = -1;
//	bundle->pid[0] = fork();
	printf("Line: %d\n", __LINE__);
	while (++i < bundle->philos)
	{
		bundle->ph[i].pid = fork();
		if (bundle->ph[i].pid < 0)
			return (1);
		if (bundle->ph[i].pid == 0)
		{
			printf("Hello, I'm %d!\n", i);
			func();
		}
	}
	return (0);
}

