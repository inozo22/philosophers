/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:56:04 by nimai             #+#    #+#             */
/*   Updated: 2023/07/04 13:29:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_error(int code, t_bundle *bundle)
{
	if (code == 1)
		printf("philos could not create a thread\n");
	else if (code == 2)
		printf("watchdog could not create a thread\n");
	else if (code == 3)
		printf("philos could not join a thread\n");
	else if (code == 4)
		printf("watchdog could not join a thread\n");
	else if (code == 5)
		;
	else if (code == 6)
		;
	else if (code == 99)
		;
	if (bundle)
		all_free(bundle);
}

/**
 * @brief print error message, free and exit.
 * @author nimai
 * @return exit directory after free.
 * @note at the moment separate all cases to know where is the problem. Maybe I will merge then
 */
void	input_error(int code, t_bundle *bundle)
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
		return ;
	}
	else if (code == 2)
		printf("Please, number of Philo should be fewer than 201.\n");
	else if (code == 3)
		printf("Please, each time should not be under 60ms.\n");
	else if (code == 4)
		printf("Please put positive number.\n");
	else if (code == 5)
		printf("Please put int number.\n");
	else if (code == 6)
		printf("Please put only numeric letter.\n");
	else if (code == 99)
		printf("UNKNOWN ERROR\n");
	bundle->status++;
}

/**
 * @brief print error message, free and exit.
 * @author nimai
 * @return exit directory after free.
 * @note at the moment separate all cases to know where is the problem. Maybe I will merge then
 * @note flag 1 has valor as NULL, if you have problem with this, check it
 */
void	heap_error(int flag, t_bundle *bundle)
{
	if (flag == 1)
	{
		printf("bundle memory allocate failure\n");
		if (bundle)
			all_free(bundle);
		exit (1);
	}
	if (flag == 2)
	{
		printf("th memory allocate failure\n");
		if (bundle)
			all_free(bundle);
		exit (1);
	}
}
