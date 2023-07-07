/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:11:01 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 10:11:51 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

/**
 * @brief structure for each philosophers 
 */
typedef struct s_philo
{
	long				id;
	long				ate;
	long				last_meal;
	int					right;
	int					left;
	sem_t				*fork;
	sem_t				*eat;
	pthread_t			th;
	pid_t				pid;
	struct s_bundle		*bundle;
}	t_philo;

/**
 * @brief main structure 
 */
typedef struct s_bundle
{
	t_philo				*ph;
	sem_t				*print;
	int					status;
	int					fin;
	int					heap;
	pthread_t			watchdog;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				philos;
	long				meals;
	long				start;
	pid_t				pid_watchdog;
}	t_bundle;

#endif
