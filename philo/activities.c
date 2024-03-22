/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:01:47 by gcros             #+#    #+#             */
/*   Updated: 2024/03/20 20:38:47 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philosopher *self);
int	ph_sleep(t_philosopher *self);
int	ph_think(t_philosopher *self);
int	get_fork(t_philosopher *self, t_fork *fork);

void	ph_life(t_philosopher *self)
{
	usleep((self->id % 2) * 200);
	while (!is_dead(self))
		if (ph_think(self))
			if (ph_eat(self))
				if (ph_sleep(self))
					(void) "tkt";
	ph_call("lol", self);
}

int	get_fork(t_philosopher *self, t_fork *fork)
{
	while (!is_dead(self))
	{
		if (pick_fork(fork) == 1)
			return (1);
		//usleep(1);
	}
	return (0);
}

int	ph_eat(t_philosopher *self)
{
	struct timeval	tv;
	int ret;

	ph_call("is eating", self);
	gettimeofday(&tv, NULL);
	self->life_time = to_long(tv) + self->table->time_to_die;
	ret = sleep_or_die(self->table->time_to_eat, self);
	drop_fork(self->forks[(self->id) % 2]);
	drop_fork(self->forks[(self->id + 1) % 2]);
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
	return (!sleep_or_die(self->table->time_to_sleep, self));
}

int	ph_think(t_philosopher *self)
{
	ph_call("is thinking", self);
	if (get_fork(self, self->forks[(self->id) % 2]) == 0)
		return (0);
	ph_call("has taken a fork", self);
	if (get_fork(self, self->forks[(self->id + 1) % 2]) == 0)
	{
		drop_fork(self->forks[(self->id) % 2]);
		return (0);
	}
	ph_call("has taken a fork", self);
	return (!is_dead(self));
}
