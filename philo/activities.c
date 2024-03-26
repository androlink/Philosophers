/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:01:47 by gcros             #+#    #+#             */
/*   Updated: 2024/03/26 17:48:17 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philosopher *self);
int	ph_sleep(t_philosopher *self);
int	ph_think(t_philosopher *self);
int	get_fork(t_philosopher *self, t_fork *fork);

void	ph_life(t_philosopher *self)
{
	
	if (self->id & 1)
		usleep(self->table->time_to_eat * .5 + 100 * (self->id == 1));
	while (!is_dead(self))
	{
		if (ph_think(self) == 0)
		{
			drop_fork(self->forks[(self->id) & 1]);
			drop_fork(self->forks[(self->id + 1) & 1]);
			break ;
		}
		if (ph_eat(self) == 0)
			break ;
		if (ph_sleep(self) == 0)
			break ;
	}
	ph_call("lol", self);
}

int	get_fork(t_philosopher *self, t_fork *fork)
{
	(void) self;
	pick_fork(fork);
	return (1);
}

int	ph_eat(t_philosopher *self)
{
	struct timeval	tv;
	int ret;

	ph_call("is eating", self);
	pthread_mutex_lock(&self->_mut);
	gettimeofday(&tv, NULL);
	self->life_time = to_long(tv) + self->table->time_to_die;
	pthread_mutex_unlock(&self->_mut);
	ret = sleep_or_die(self->table->time_to_eat, self);
	drop_fork(self->forks[(self->id + 1) & 1]);
	drop_fork(self->forks[(self->id) & 1]);
	if (ret == 1)
		return (0);
	pthread_mutex_lock(&self->_mut);
	self->eat_count++;
	pthread_mutex_unlock(&self->_mut);
	return (1);
}

int	ph_sleep(t_philosopher *self)
{
	ph_call("is sleeping", self);
	return (!sleep_or_die(self->table->time_to_sleep * 1.1, self));
}

int	ph_think(t_philosopher *self)
{
	ph_call("is thinking", self);
	get_fork(self, self->forks[(self->id + 1) & 1]);
	ph_call("has taken a fork", self);
	get_fork(self, self->forks[(self->id) & 1]);
	ph_call("has taken a fork", self);
	return (!check_stop(self->table));
}
