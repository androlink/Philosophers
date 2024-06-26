/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 03:34:01 by gcros             #+#    #+#             */
/*   Updated: 2024/03/23 22:43:39 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	give_life(t_philosopher *phi, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if(pthread_create(&phi[i].thread, NULL, (void *(*)(void *))&born, &phi[i]))
			return (i);
		i++;
	}
	return (i);
}

int	take_life(t_philosopher *phi, int count)
{
	int		i;
	void	*nothing;

	i = 0;
	while (i < count)
	{
		pthread_join(phi[i].thread, &nothing);
		i++;
	}
	return (0);
}

int	manage_life(t_table *table)
{
	size_t	count;
	size_t	i;

	while (!check_stop(table))
	{
		usleep(100 * table->number);
		count = 0;
		i = 0;
		while (i < table->number)
		{
			pthread_mutex_lock(&table->philosophers[i]._mut);
			if (table->philosophers[i].eat_count >= table->eat_count)
				count++;
			pthread_mutex_unlock(&table->philosophers[i]._mut);
			i++;
		}
		if (count == i)
		{
			pthread_mutex_lock(&table->stop_mut);
			table->stop = 1;
			pthread_mutex_unlock(&table->stop_mut);
		}
	}
	return (1);
}

int	god(t_table *table)
{
	struct timeval	tmp;
	size_t			i;

	table->stop = 0;
	pthread_mutex_lock(&table->start_mut);
	i = give_life(table->philosophers, table->number);
	if (i != table->number)
	{
		pthread_mutex_lock(&table->stop_mut);
		table->stop = 1;
		pthread_mutex_unlock(&table->stop_mut);
		pthread_mutex_unlock(&table->start_mut);
	}
	else
	{
		usleep(100);
		gettimeofday(&tmp, NULL);
		time_ref(0, to_long(tmp));
		pthread_mutex_unlock(&table->start_mut);
		usleep(1000);
		manage_life(table);
	}
	take_life(table->philosophers, i);
	return (0);
}

