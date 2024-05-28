/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:01:47 by gcros             #+#    #+#             */
/*   Updated: 2024/05/28 11:35:52 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philosopher *self);
int	ph_sleep(t_philosopher *self);
int	ph_think(t_philosopher *self);
int	get_fork(t_philosopher *self, t_fork *fork);

void	ph_life(t_philosopher *self)
{
	if (self->table->number == 1)
		return ;
	if (self->id & 1)
		usleep(self->table->time_to_eat + 100 * (self->id == 1));
	while (!check_stop(self->table))
	{
		if (ph_think(self) == 0)
		{
			drop_fork(self->hands.forks[(self->id) & 1]);
			drop_fork(self->hands.forks[(self->id + 1) & 1]);
			break ;
		}
		if (ph_eat(self) == 0)
			break ;
		if (ph_sleep(self) == 0)
			break ;
	}
	printf("%d out\n", self->id);
}

int	get_fork(t_philosopher *self, t_fork *fork)
{
	(void) self;
	if (pick_fork(fork))
	{
		ph_call("has taken a fork", self);
		return (1);
	}
	return (0);
}

int	ph_eat(t_philosopher *self)
{
	struct timeval	tv;
	int				ret;

	ph_call("is eating", self);
	pthread_mutex_lock(&self->_mut);
	gettimeofday(&tv, NULL);
	self->life_time = to_long(tv) + self->table->time_to_die;
	pthread_mutex_unlock(&self->_mut);
	ret = sleep_or_die(self->table->time_to_eat);
	drop_fork(self->hands.forks[(self->id + 1) & 1]);
	drop_fork(self->hands.forks[(self->id) & 1]);
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
	return (!sleep_or_die(self->table->time_to_sleep + 10));
}

int	ph_think(t_philosopher *self)
{
	int	ret[2];

	ret[0] = 0;
	ret[1] = 0;
	ph_call("is thinking", self);
	while ((ret[0] == 0 || ret[1] == 0))
	{
		if (ret[0] == 0)
		{
			if (get_fork(self, self->hands.forks[(self->id) & 1]))
			{
				ret[0] = 1;
			}
		}
		if (ret[1] == 0)
		{
			if (get_fork(self, self->hands.forks[(self->id + 1) & 1]))
			{
				ret[1] = 1;
			}
		}
		usleep(200);
	}
	return (!check_stop(self->table));
}
