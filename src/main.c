/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:19:36 by nimai             #+#    #+#             */
/*   Updated: 2023/06/06 18:06:08 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	(void)av;
	if (ac < 4)
		return (philo_error(1), 0);
	//check amount of philo, and die time before allocate memory
	return (0);
}
