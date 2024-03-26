/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:34:50 by gcros             #+#    #+#             */
/*   Updated: 2024/03/24 20:09:10 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philosopher *self)
{
	struct timeval	tmp;
	int res;
	t_table *const	_table = self->table;

	res = 0;
	pthread_mutex_lock(&self->_mut);
	gettimeofday(&tmp, NULL);
	if ((to_long(tmp)) / 1000 > self->life_time / 1000)
	{
		pthread_mutex_unlock(&self->_mut);
		pthread_mutex_lock(&_table->stop_mut);
		if (_table->stop == 0)
			res = 1;
		*self->stop = 1;
		pthread_mutex_unlock(&_table->stop_mut);
		pthread_mutex_lock(&_table->print_mut);
		if (res == 1)
			printf("%ld\t%d\t%s\n", time_ref(to_long(tmp), 0) / 1000, self->id, "died");
		pthread_mutex_unlock(&_table->print_mut);
		return (1);
	}
	pthread_mutex_unlock(&self->_mut);
	return (0);
}

void	*born(t_philosopher *self)
{
	struct timeval	tmp;
	t_table *const _table = self->table;

	pthread_mutex_lock(&self->_mut);
	pthread_mutex_lock(&_table->start_mut);
	pthread_mutex_unlock(&_table->start_mut);
	gettimeofday(&tmp, NULL);
	self->life_time = to_long(tmp) + _table->time_to_die;
	pthread_mutex_unlock(&self->_mut);
	ph_life(self);
	return (NULL);
}

void	ph_call(char *msg, t_philo *self)
{
	struct timeval	tmp;
	pthread_mutex_t *const _tmp = &self->table->print_mut;

	pthread_mutex_lock(_tmp);
	gettimeofday(&tmp, NULL);
	if (!check_stop(self->table))
		//printf("%5ld.%.3ld\t%d\t%s\n", time_ref(to_long(tmp), 0) / 1000, time_ref(to_long(tmp), 0) % 1000, self->id, msg);
		printf("%ld\t%d\t%s\n", time_ref(to_long(tmp), 0) / 1000, self->id, msg);
	pthread_mutex_unlock(_tmp);
}