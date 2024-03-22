/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:34:50 by gcros             #+#    #+#             */
/*   Updated: 2024/03/20 20:39:34 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philosopher *self)
{
	struct timeval	tmp;
	int res;

	res = 0;
	gettimeofday(&tmp, NULL);
	if ((to_long(tmp)) > self->life_time)
	{
		
		pthread_mutex_lock(&self->table->stop_mut);
		if (self->table->stop == 0)
			res = 1;
		*self->stop = 1;
		pthread_mutex_unlock(&self->table->stop_mut);
		if (res == 1)
			ph_call("died", self);
		return (1);
	}
	return (check_stop(self->table));
}

void	*born(t_philosopher *self)
{
	struct timeval	tmp;

	pthread_mutex_lock(&self->table->start_mut);
	gettimeofday(&tmp, NULL);
	self->life_time = to_long(tmp) + self->table->time_to_die;
	pthread_mutex_unlock(&self->table->start_mut);
	ph_life(self);
	return (NULL);
}

void	ph_call(char *msg, t_philo *self)
{
	struct timeval	tmp;

	pthread_mutex_lock(&self->table->print_mut);
	gettimeofday(&tmp, NULL);
	printf("%ld\t%d\t%s\n", time_ref(to_long(tmp), 0) / 1000, self->id, msg);
	pthread_mutex_unlock(&self->table->print_mut);
}