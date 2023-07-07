/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:26:34 by nimai             #+#    #+#             */
/*   Updated: 2023/07/07 14:55:06 by nimai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;

	i = 0;
	dlen = ft_strlen(dst);
	if (dlen >= dstsize)
		return (dstsize + ft_strlen((char *)src));
	while (src[i] && (i < (dstsize - dlen -1)))
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + ft_strlen((char *)src));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned long	i;
	unsigned long	slen;

	slen = 0;
	while (src[slen])
		slen++;
	i = 0;
	if (dstsize < 1)
	{
		return (slen);
	}
	if ((dst < src) || (dst >= src + dstsize))
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (slen);
}

unsigned int	get_len(long n)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*dup_str(char *str, long nb, unsigned int len)
{
	if (nb == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (nb < 0)
		nb *= -1;
	while (len--)
	{
		str[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	if (str[0] == 48)
		str[0] = '-';
	return (str);
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


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*pmem;

	len = ft_strlen(s1) + ft_strlen(s2);
	pmem = malloc(len + 1);
	if (pmem == NULL)
		return (NULL);
	ft_strlcpy(pmem, s1, ft_strlen(s1) + 1);
	ft_strlcat(pmem, s2, len + 1);
	return (pmem);
}

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	t = malloc(len + 1);
	i = 0;
	if (t == NULL)
		return (NULL);
	while (s[i])
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
	{
		if (!s2)
			return (0);
		else
			return (-s2[0]);
	}
	else if (!s2)
		return (*s1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

long	myatoi(char *str, t_bundle *bundle)
{
	int				i;
	unsigned int	nbr;
	int				sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (input_error(4, bundle), -1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = (str[i] - 48) + (nbr * 10);
		i++;
	}
	if (str[i] != '\0')
		return (input_error(6, bundle), -1);
	return (nbr * sign);
}
