/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:34:50 by gcros             #+#    #+#             */
/*   Updated: 2024/03/23 22:40:06 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philosopher *self)
{
	struct timeval	tmp;
	int res;
	t_table *const	_table = self->table;

	res = 0;
	gettimeofday(&tmp, NULL);
	if ((to_long(tmp)) > self->life_time)
	{
		pthread_mutex_lock(&_table->stop_mut);
		if (_table->stop == 0)
			res = 1;
		*self->stop = 1;
		pthread_mutex_unlock(&_table->stop_mut);
		if (res == 1)
			ph_call("died", self);
		return (1);
	}
	return (check_stop(_table));
}

void	*born(t_philosopher *self)
{
	struct timeval	tmp;
	t_table *const _table = self->table;

	pthread_mutex_lock(&_table->start_mut);
	pthread_mutex_unlock(&_table->start_mut);
	gettimeofday(&tmp, NULL);
	self->life_time = to_long(tmp) + _table->time_to_die;
	ph_life(self);
	return (NULL);
}

void	ph_call(char *msg, t_philo *self)
{
	struct timeval	tmp;
	pthread_mutex_t *const _tmp = &self->table->print_mut;

	pthread_mutex_lock(_tmp);
	gettimeofday(&tmp, NULL);
	//printf("%5ld.%.3ld\t%d\t%s\n", time_ref(to_long(tmp), 0) / 1000, time_ref(to_long(tmp), 0) % 1000, self->id, msg);
	printf("%ld\t%d\t%s\n", time_ref(to_long(tmp), 0) / 1000, self->id, msg);
	pthread_mutex_unlock(_tmp);
}