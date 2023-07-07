/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:23:25 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 12:48:54 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include "structure.h"
# include "functions.h"

# define ARGLIMIT 200
# define HEAP_BUNDLE 1
# define HEAP_PHILO 2
# define MSG_DIED "is starved to death👻"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_RIGHT "has taken first chopstick"
# define MSG_LEFT "has taken second chopstick"
# define MSG_COMP "They all ate the required number of meals🥳"

# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define CYAN "\033[1;36m"
# define GREEN "\033[1;32m"
# define CLEAR "\033[0m"

#endif
