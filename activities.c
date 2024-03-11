/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:01:47 by gcros             #+#    #+#             */
/*   Updated: 2024/03/11 14:23:26 by gcros            ###   ########.fr       */
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
	while (*self->stop == 0 && !is_dead(self))
		(void) (ph_think(self) && ph_eat(self) && ph_sleep(self));
}

int	get_fork(t_philosopher *self, t_fork *fork)
{
	struct timeval	tmp;

	if (pick_fork(fork) == 0)
		return (0);
	gettimeofday(&tmp, NULL);
	printf("%ld %d has taken a fork\n", time_ref(to_long(tmp), 0) / 1000, self->id);
	return (1);
}

int	ph_eat(t_philosopher *self)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld %d is eating\n", time_ref(to_long(tv), 0) / 1000, self->id);
	self->life_time = to_long(tv) + self->table->time_to_die;
	if (self->table->time_to_eat > self->life_time)
	{
		fuck_it_him_out(self, self->table->time_to_die);
		return (0);
	}
	usleep(self->table->time_to_eat);
	self->eat_count++;
	drop_fork(self->forks[1]);
	drop_fork(self->forks[0]);
	return (1);
}

int	ph_sleep(t_philosopher *self)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", time_ref(to_long(tv), 0) / 1000, self->id);
	if (self->table->time_to_sleep > self->life_time)
	{
		fuck_it_him_out(self, self->table->time_to_die);
		return (0);
	}
	usleep(self->table->time_to_sleep);
	usleep(100);
	return (1);
}

int	ph_think(t_philosopher *self)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld %d is thinking\n", time_ref(to_long(tv), 0) / 1000, self->id);
	while (*self->stop == 0 && !is_dead(self))
	{
		if (get_fork(self, self->forks[1]) == 0)
			continue ;
		if (*self->stop == 1 || is_dead(self))
		{
			drop_fork(self->forks[1]);
			break ;
		}
		if (get_fork(self, self->forks[0]) == 0)
			drop_fork(self->forks[1]);
		else
			break ;
	}
	return (!*self->stop);
}
