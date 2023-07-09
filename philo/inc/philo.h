/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:25 by nimai             #+#    #+#             */
/*   Updated: 2023/07/09 17:18:00 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>

# define MSG_DIED "is died"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_RIGHT "has taken a fork"
# define MSG_LEFT "has taken a fork"
# define MSG_COMP "They all ate the required number of meals"

# define ERR_MUTEX_LOCK 99
# define ERR_MUTEX_UNLOCK 98
# define HEAP_BUNDLE 1
# define HEAP_FORKS 2
# define HEAP_PH 3

# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define CYAN "\033[1;36m"
# define GREEN "\033[1;32m"
# define CLEAR "\033[0m"

/**
 * @brief structure for each philosophers 
 */
typedef struct s_philo
{
	unsigned int		id;
	unsigned int		ate;
	long				last_meal;
	int					right;
	int					left;
	pthread_t			th;
	struct s_bundle		*bundle;
}	t_philo;

/**
 * @brief main structure 
 */
typedef struct s_bundle
{
	t_philo				*ph;
	int					status;
	int					heap;
	int					fin;
	pthread_t			watchdog;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				philos;
	unsigned int		meals;
	long				start;
	pthread_mutex_t		check_meals;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		death;
}	t_bundle;

//--------------------------------
//utils
//--------------------------------

void	*ft_calloc(size_t count, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
long	myatol(char *str, t_bundle *bundle);

//--------------------------------
//thread
//--------------------------------

void	*routine(void *param);
int		init_mutex(t_bundle *bundle);
int		set_thread(t_bundle *bundle);
int		destroy(t_bundle *bundle);

//--------------------------------
//thread_action
//--------------------------------

void	check_meals(t_bundle *bundle);
void	print_philo(t_philo *philo, char *msg, char	*color);
void	action(t_philo *philo);

//--------------------------------
//errors
//--------------------------------

void	philo_error(int code, t_bundle *bundle);
void	input_error(int code, t_bundle *bundle);
void	heap_error(int flag, t_bundle *bundle);

//--------------------------------
//free
//--------------------------------

void	all_free(t_bundle *bundle);

//--------------------------------
//time
//--------------------------------

long	get_time(void);
void	time_control(t_philo *philo, long time);

//--------------------------------
//watchdog
//--------------------------------

void	*watchdog(void *param);

//--------------------------------
//thread_protect.c
//--------------------------------

void	my_pthread_mutex_lock(pthread_mutex_t *param, t_bundle *bundle);
void	my_pthread_mutex_unlock(pthread_mutex_t *param, t_bundle *bundle);

#endif
