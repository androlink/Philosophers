/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:34:50 by gcros             #+#    #+#             */
/*   Updated: 2024/03/11 16:34:35 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fuck_it_him_out(t_philo *self, long time)
{
	printf("fuck life %d\n", self->id);
	usleep(time);
	self->is_dead = 1;
	*self->stop = 1;
}

int	is_dead(t_philosopher *self)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	if ((to_long(tmp)) > self->life_time)
	{
		if (*self->stop == 0)
			self->is_dead = 1;
		*self->stop = 1;
	}
	return (self->is_dead || *self->stop);
}

void	*born(t_philosopher *self)
{
	struct timeval	tmp;

	while (self->table->start == 0)
	{
		if (self->table->stop == 1)
			return (NULL);
	}
	ph_life(self);
	if (self->is_dead == 1)
	{
		gettimeofday(&tmp, NULL);
		pthread_mutex_lock(&self->table->p_mut);
		printf("%ld\t%d died\n", time_ref(to_long(tmp), 0) / 1000, self->id);
		pthread_mutex_unlock(&self->table->p_mut);
	}
	return (NULL);
}
