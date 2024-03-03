/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:27:13 by gcros             #+#    #+#             */
/*   Updated: 2024/03/03 18:01:53 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int			s;
	int			res;
	const char	*str;

	str = nptr;
	res = 0;
	s = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if ((res * 10 + (*str - '0') - (s == -1)) < res)
			return (-(s == 1));
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (res * s);
}

long	time_ref(long test, long set)
{
	static long	init;

	if (set != 0)
		init = set;
	return (test - init);
}

long	to_long(struct timeval t1)
{
	return (t1.tv_sec * 1000000 + t1.tv_usec);
}

int	pick_fork(t_fork *fork)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&fork->_mut);
	if (fork->_lock == 0)
	{
		fork->_lock = 1;
		res = 1;
	}
	pthread_mutex_unlock(&fork->_mut);
	return (res);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->_mut);
	fork->_lock = 0;
	pthread_mutex_unlock(&fork->_mut);
}
