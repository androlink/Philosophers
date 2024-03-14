/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:01:47 by gcros             #+#    #+#             */
/*   Updated: 2024/03/14 01:16:08 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philosopher *self);
int	ph_sleep(t_philosopher *self);
int	ph_think(t_philosopher *self);
int	get_fork(t_philosopher *self, t_fork *fork);

void	ph_life(t_philosopher *self)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	self->life_time = to_long(tmp) + self->table->time_to_die;
	while (!is_dead(self))
		if (ph_think(self))
			if (ph_eat(self))
				if (!is_dead(self))
					ph_sleep(self);
}

int	get_fork(t_philosopher *self, t_fork *fork)
{
	struct timeval	tmp;

	if (pick_fork(fork) == 0)
		return (0);
	gettimeofday(&tmp, NULL);
	printf("%ld\t%d has taken a fork\n", time_ref(to_long(tmp), 0) / 1000, self->id);
	return (1);
}

int	ph_eat(t_philosopher *self)
{
	struct timeval	tv;
	int ret;

	gettimeofday(&tv, NULL);
	printf("%ld\t%d is eating\n", time_ref(to_long(tv), 0) / 1000, self->id);
	self->life_time = to_long(tv) + self->table->time_to_die;
	ret = sleep_or_die(self->table->time_to_eat, self);
	drop_fork(self->forks[1]);
	drop_fork(self->forks[0]);
	if (ret == 1)
		return (0);
	pthread_mutex_lock(&self->_mut);
	self->eat_count++;
	pthread_mutex_unlock(&self->_mut);
	return (1);
}

int	ph_sleep(t_philosopher *self)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld\t%d is sleeping\n", time_ref(to_long(tv), 0) / 1000, self->id);
	return (!sleep_or_die(self->table->time_to_sleep, self));
}

int	ph_think(t_philosopher *self)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld\t%d is thinking\n", time_ref(to_long(tv), 0) / 1000, self->id);
	while (!is_dead(self))
	{
		usleep(1000);
		if (!is_dead(self) && get_fork(self, self->forks[self->id % 2]) == 0)
			continue ;
		if (is_dead(self))
		{
			drop_fork(self->forks[self->id % 2]);
			break ;
		}
		if (get_fork(self, self->forks[(self->id + 1) % 2]) == 0)
			drop_fork(self->forks[self->id % 2]);
		else
			break ;
	}
	return (!check_stop(self->table));
}
