/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:27:13 by gcros             #+#    #+#             */
/*   Updated: 2024/03/23 22:02:13 by gcros            ###   ########.fr       */
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

int	is_num(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
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

int	sleep_or_die(suseconds_t sleep_time, t_philo *self)
{
	struct timeval	t;
	suseconds_t	stop_time;

	gettimeofday(&t, NULL);
	stop_time = to_long(t) + sleep_time;
	while(to_long(t) < stop_time)
	{
		//usleep(PH_AT_TIME);
		if (is_dead(self))
			return (1);
		gettimeofday(&t, NULL);
	}
	return (0);
}
