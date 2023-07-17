/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:18:36 by nimai             #+#    #+#             */
/*   Updated: 2023/07/17 13:28:01 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @note maybe conbine with destroyers, then name terminater
 * @brief free main structure.
 */
void	all_free(t_bundle *bundle)
{
	if (bundle->heap >= HEAP_TIMES_ATE)
	{
		free (bundle->times_ate);
		bundle->times_ate = NULL;
	}
	if (bundle->heap >= HEAP_PH)
	{
		free (bundle->ph);
		bundle->ph = NULL;
	}
	if (bundle->heap >= HEAP_BUNDLE)
	{
		free (bundle);
		bundle = NULL;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = get_len(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (str)
		str = dup_str(str, n, len);
	return (str);
}
