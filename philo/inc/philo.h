/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:25 by nimai             #+#    #+#             */
/*   Updated: 2023/07/03 11:26:41 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * temporary header
*/

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

# define ARGLIMIT 200
# define BUNDLE_HEAP 0//it's not necessary define here, but not to foreget
# define TH_HEAP 1

/**
 * @brief mutex control 
 */
/* typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				*cnt;
}	t_mutex; */

/**
 * @brief philosophers 
 */
typedef struct s_philo
{
	unsigned int		id;
//	int					is_dead;
	unsigned int		ate;
	float				last_meal;
	int					right;
	int					left;
	pthread_t			th;
	struct s_bundle		*bundle;
}	t_philo;

/**
 * @brief main structure 
 * @note 230622nimai: maybe I can allocate just number of philos for t_philo philo
 */
typedef struct s_bundle
{
	t_philo				ph[ARGLIMIT];
	int					heap;
	int					status;
	int					is_dead;
	unsigned int		have_eaten;
	long				time_die;//If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
	long		 		time_eat;//The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
	long				time_sleep;//The time a philosopher will spend sleeping.
	unsigned int		philos;//The number of philosophers and also the number of forks.
	unsigned int		meals;//If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
	long				start;
//	struct timeval		clock;   //maybe it's not neccesary (because I can declear when I need it)
	pthread_mutex_t		philos_mutex;
	pthread_mutex_t		forks[ARGLIMIT];
	pthread_mutex_t		print;
	pthread_mutex_t		eat;
	pthread_mutex_t		death;
//	pthread_t			*th;
	
}	t_bundle;

//--------------------------------
//errors
//--------------------------------

void	philo_error(int code, t_bundle *bundle);
void	heap_error(int flag, t_bundle *bundle);

//--------------------------------
//urils
//--------------------------------

void	*ft_calloc(size_t count, size_t size);


//--------------------------------
//free
//--------------------------------

void	all_free(t_bundle *bundle);

//--------------------------------
//time
//--------------------------------

long	get_time(int flag);
void	time_control(t_philo *philo, long time);
void	check_survival(t_philo *philo);

//--------------------------------
//print
//--------------------------------

void	print_philo(t_philo *philo, char *msg, char	*color);

#endif
