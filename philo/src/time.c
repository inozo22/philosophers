/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:55:10 by nimai             #+#    #+#             */
/*   Updated: 2023/06/30 18:50:21 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


/**
 * @note flag 0 is start, otherwise return the differ time in long
 */
long	get_time(int flag)
{
	static struct timeval	start;
	struct timeval			now;
	long					ret;

	if (flag == 0)
	{
		gettimeofday(&start, NULL);
		ret = 0;
	}
	else
	{
		gettimeofday(&now, NULL);
		ret = now.tv_sec - start.tv_sec + (float)(now.tv_usec - start.tv_usec);
	}
	return (ret);
}

void	check_survival(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->death);
	if ((get_time(1) - philo->last_meal) > philo->bundle->time_die
		&& philo->bundle->is_dead == 0)
	{
		print_philo(philo, "died", "\033[1;31m");
		philo->bundle->is_dead = 1;
	}
	pthread_mutex_unlock(&philo->bundle->death);
}

void	time_control(t_philo *philo, long time)
{
	long	ret;

	ret = get_time(1) + time;
	while ((get_time(1) < ret) && !(philo->bundle->is_dead))
	{
		check_survival(philo);
		usleep(50);
		usleep(50);
	}
}

/* int main()
{
    struct timeval time1;
    struct timeval time2;
    float diff_time;
 
    gettimeofday(&time1, NULL);
//    printf("sec: %d, usec: %d\n", (int)time1.tv_sec, (int)time1.tv_usec);
 
    * Describe Function for Measurement of time *
	printf("dskfjslkdgjtlkjgskdjfajksdhkjsfhjskdfnsjkdfnskdnfjsndjfnsjkdnfjnsjndfjnsjfnjsndfkjnsjkdnfjsndkjfnjksndfk\n");
 
    gettimeofday(&time2, NULL);
//    printf("sec: %d, usec: %d\n", (int)time2.tv_sec, (int)time2.tv_usec);
 
    diff_time = time2.tv_sec - time1.tv_sec +  (float)(time2.tv_usec - time1.tv_usec) / 1000000;
    printf("diff: %f[s]\n", diff_time);
 
    return 0;
} */
