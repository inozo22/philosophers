/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:47:47 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 13:42:02 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//--------------------------------
//main
//--------------------------------

int		destroy_process(t_bundle *bundle);
void	terminator(t_bundle *bundle);
void	close_sem(t_bundle *bundle);

//--------------------------------
//utils
//--------------------------------

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
long	get_len(long n);
char	*dup_str(char *str, long nb, unsigned int len);

//--------------------------------
//utils_philo
//--------------------------------

void	loneliness(t_bundle *bundle);
long	myatol(char *str, t_bundle *bundle);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

//--------------------------------
//control_sem
//--------------------------------

int		init_sem(t_bundle *bundle);
void	close_sem(t_bundle *bundle);

//--------------------------------
//set_philos
//--------------------------------

int		set_philos(t_bundle *bundle);
void	print_philo(t_philo *philo, char *msg, char *color);

//--------------------------------
//errors
//--------------------------------

void	philo_error(int code, t_bundle *bundle);
void	input_error(int code, t_bundle *bundle);
void	heap_error(int flag, t_bundle *bundle);

//--------------------------------
//heap
//--------------------------------

void	all_free(t_bundle *bundle);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);

//--------------------------------
//time
//--------------------------------

long	get_time(void);
void	time_control(t_philo *philo, long time);

//--------------------------------
//watchdog
//--------------------------------

void	*watchdog(void *param);
int		set_eat_counter(t_bundle *bundle);

//--------------------------------
//run
//--------------------------------

int		run(t_bundle *bundle);
void	all_goodbye(t_bundle *bundle);

#endif
