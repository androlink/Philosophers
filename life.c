/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:34:50 by gcros             #+#    #+#             */
/*   Updated: 2024/03/12 20:29:00 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fuck_it_him_out(t_philo *self, long time)
{
	printf("fuck life %d\n", self->id);
	self->is_dead = 1;
	pthread_mutex_lock(&self->table->stop_mut);
	*self->stop = 1;
	pthread_mutex_unlock(&self->table->stop_mut);
	usleep(time);
}

int	is_dead(t_philosopher *self)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	if ((to_long(tmp)) > self->life_time)
	{
		if (check_stop(self->table) == 0)
			self->is_dead = 1;
		pthread_mutex_lock(&self->table->stop_mut);
		*self->stop = 1;
		pthread_mutex_unlock(&self->table->stop_mut);
	}
	return (self->is_dead || check_stop(self->table));
}

void	*born(t_philosopher *self)
{
	struct timeval	tmp;
DEBUG_PRINT
	while (check_start(self->table) == 0)
	{DEBUG_PRINT
		if (check_stop(self->table) == 1)
			return (NULL);
	}DEBUG_PRINT
	ph_life(self);
	if (self->is_dead == 1)
	{
		gettimeofday(&tmp, NULL);
		printf("%ld\t%d died\n", time_ref(to_long(tmp), 0) / 1000, self->id);
	}
	return (NULL);
}
