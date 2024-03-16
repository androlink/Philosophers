/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:34:50 by gcros             #+#    #+#             */
/*   Updated: 2024/03/16 13:33:38 by gcros            ###   ########.fr       */
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
		pthread_mutex_lock(&self->table->stop_mut);
		if (self->table->stop == 0)
			self->is_dead = 1;
		*self->stop = 1;
		pthread_mutex_unlock(&self->table->stop_mut);
	}
	return (self->is_dead || check_stop(self->table));
}

void	*born(t_philosopher *self)
{
	struct timeval	tmp;

	while (check_start(self->table) == 0)
		if (check_stop(self->table) == 1)
			return (NULL);
	ph_life(self);
	if (self->is_dead == 1)
	{
		gettimeofday(&tmp, NULL);
		printf("%ld\t%d died\n", time_ref(to_long(tmp), 0) / 1000, self->id);
	}
	return (NULL);
}
