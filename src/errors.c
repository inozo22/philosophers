/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:56:04 by nimai             #+#    #+#             */
/*   Updated: 2023/06/09 17:10:47 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_error(int code)
{
	if (code == 1)
	{
		printf("Usage	:[1]number_of_philosophers\n[2]time_to_die\n[3]time_to_eat\n[4]time_to_sleep \n\
	   [5][number_of_times_each_philosopher_must_eat]\n");
		printf("example	:philo 5 800 200 200 [10]\n");
		exit(1);
	}
}
