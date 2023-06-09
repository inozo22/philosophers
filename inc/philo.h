/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:25 by nimai             #+#    #+#             */
/*   Updated: 2023/06/09 17:13:18 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * temporary header
*/

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <pthread.h>

# define ARGLIMIT 201

/**
 * @brief philosophers 
 */
typedef struct s_philo
{
	int	id;
}	t_philo;

/**
 * @brief main structure 
 */
typedef struct s_bundle
{
	t_philo	philo[ARGLIMIT];
	int		time_die;//If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
	int		time_eat;//The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
	int		time_sleep;//The time a philosopher will spend sleeping.
	int		philos;//The number of philosophers and also the number of forks.
	int		meals;//If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
}	t_bundle;

void	philo_error(int code);

#endif
