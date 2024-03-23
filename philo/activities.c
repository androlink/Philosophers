/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:01:47 by gcros             #+#    #+#             */
/*   Updated: 2024/03/23 22:40:21 by gcros            ###   ########.fr       */
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
		usleep(1000 + 100 * (self->id == 1));
	while (!is_dead(self))
	{
		if (ph_think(self) == 0)
			break ;
		if (ph_eat(self) == 0)
			break ;
		if (ph_sleep(self) == 0)
			break ;
		usleep(100);
	}
	//ph_call("lol", self);
}

int	get_fork(t_philosopher *self, t_fork *fork)
{
	int i;

	i = 1;
	while (i || !is_dead(self))
	{
		//write(2, ".", 1);
		if (pick_fork(fork) == 1)
			return (1);
		//usleep(PH_AT_TIME * 2);
		i = (i + 1) % 20;
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
	drop_fork(self->forks[(self->id) & 1]);
	drop_fork(self->forks[(self->id + 1) & 1]);
	if (ret == 1)
		return (0);
	pthread_mutex_lock(&self->_mut);
	self->eat_count++;
	pthread_mutex_unlock(&self->_mut);
	return (1);
}

inline int	ph_sleep(t_philosopher *self)
{
	ph_call("is sleeping", self);
	return (!sleep_or_die(self->table->time_to_sleep, self));
}

int	ph_think(t_philosopher *self)
{
	ph_call("is thinking", self);
	if (get_fork(self, self->forks[(self->id) & 1]) == 0)
		return (0);
	ph_call("has taken a fork", self);
	if (get_fork(self, self->forks[(self->id + 1) & 1]) == 0)
	{
		drop_fork(self->forks[(self->id) & 1]);
		return (0);
	}
	ph_call("has taken a fork", self);
	return (!is_dead(self));
}
