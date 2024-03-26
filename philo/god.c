/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 03:34:01 by gcros             #+#    #+#             */
/*   Updated: 2024/03/26 17:18:55 by gcros            ###   ########.fr       */
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
		pthread_join(phi[i++].thread, &nothing);
	return (0);
}



int	manage_life(t_table *table)
{
	size_t	check;
	size_t	i;

	while (!check_stop(table))
	{
		usleep(table->time_to_die / 5);
		check = 1;
		i = 0;
		while (i < table->number)
		{
			pthread_mutex_lock(&table->philosophers[i]._mut);
			if (table->philosophers[i].eat_count < table->eat_count)
				check = 0;
			pthread_mutex_unlock(&table->philosophers[i]._mut);
			if (is_dead(&table->philosophers[i]))
				break ;
			i++;
		}
		if (check == 1)
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
		usleep(80 * table->number / 2);
		gettimeofday(&tmp, NULL);
		time_ref(0, to_long(tmp));
		pthread_mutex_unlock(&table->start_mut);
		manage_life(table);
	}
	take_life(table->philosophers, i);
	return (0);
}

