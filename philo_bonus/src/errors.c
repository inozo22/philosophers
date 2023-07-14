/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:56:04 by nimai             #+#    #+#             */
/*   Updated: 2023/07/14 14:50:35 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @note there are a lot of error which are not controled yet
 */
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
		printf("pthread_mutex_init failure\n");
	else if (code == 6)
		printf("pthread_mutex_destroy failure\n");
	else if (code == 99)
		;
	if (bundle)
		all_free(bundle);
}

/**
 * @brief print error message.
 * @return only print message and give bad status
 */
void	input_error(int code, t_bundle *bundle)
{
	(void)bundle;
	if (code == 1)
	{
		printf("Usage	:[1]number_of_philosophers\n");
		printf("	:[2]time_to_die\n");
		printf("	:[3]time_to_eat\n");
		printf("	:[4]time_to_sleep\n");
		printf("	:[5][number_of_times_each_philosopher_must_eat]\n");
		printf("-------------------------------------------------------\n");
		printf("example	:philo 5 800 200 200 [10]\n");
		exit (1);
	}
	else if (code == 4)
		printf("Please put positive number.\n");
	else if (code == 5)
		printf("Please put int number.\n");
	else if (code == 6)
		printf("Please put only numeric letter.\n");
	else if (code == 99)
		printf("UNKNOWN ERROR\n");
//	bundle->status++;
}

/**
 * @brief print error message
 * @return only print the message
 * @note flag 1 has valor as NULL, if you have problem with this, check it
 */
void	heap_error(int flag, t_bundle *bundle)
{
	(void)bundle;
	if (flag == 1)
	{
		printf("bundle memory allocate failure\n");
	}
	exit (1);
}
