/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:47:47 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 12:57:51 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//--------------------------------
//utils
//--------------------------------

void	*ft_calloc(size_t count, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
long	myatoi(char *str, t_bundle *bundle);

//--------------------------------
//init_sem
//--------------------------------

int		init_sem(t_bundle *bundle);

//--------------------------------
//run
//--------------------------------

int		run(t_bundle *bundle);
void	print_philo(t_philo *philo, char *msg, char *color);

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
//utils_philo
//--------------------------------

void	loneliness(t_bundle *bundle);

#endif
