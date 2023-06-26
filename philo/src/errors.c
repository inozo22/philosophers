/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:56:04 by nimai             #+#    #+#             */
/*   Updated: 2023/06/26 15:48:45 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_error(int code)
{
	if (code == 1)
	{
		printf("Usage	:[1]number_of_philosophers\n");
		printf("	:[2]time_to_die\n");
		printf("	:[3]time_to_eat\n");
		printf("	:[4]time_to_sleep\n");
		printf("	:[5][number_of_times_each_philosopher_must_eat]\n");
		printf("-------------------------------------------------------\n");
		printf("example	:philo 5 800 200 200 [10]\n");
		exit(1);
	}
	if (code == 2)
		printf("Please, number of Philo should be fewer than 201.\n");
	if (code == 3)
		printf("Please, each time should not be under 60ms.\n");
	if (code == 4)
		printf("Please put positive number.\n");
	if (code == 5)
		printf("Please put int number.\n");
}

/**
 * @brief print error message.
 * @author nimai
 * @return nothing.
 */
void	heap_error(int flag)
{
	if (flag == 1)
	{
		printf("memory allocate failure\n");
	}
}
