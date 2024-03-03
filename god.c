/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 03:34:01 by gcros             #+#    #+#             */
/*   Updated: 2024/03/03 15:54:01 by gcros            ###   ########.fr       */
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
			return (1);
		i++;
	}
	return (0);
}

int	take_life(t_philosopher *phi, int count)
{
	int		i;
	void	*nothing;

	i = 0;
	while (i < count)
	{
		if(pthread_join(phi[i].thread, &nothing))
			return (1);
		i++;
	}
	return (0);
}

int	manage_life(t_table *table)
{
	int	count;
	int	i;

	while (!table->stop)
	{
		count = 0;
		i = 0;
		while (i < table->phi_number)
		{
			if (table->philosophers[i].eat_count >= table->eat_count)
				count++;
			i++;
		}
		if (count == i)
			table->stop = 1;
	}
}

int	god(t_table *table)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	table->start = 0;
	table->stop = 0;
	time_ref(0, to_long(tmp));
	if (give_life(table->philosophers, table->phi_number))
	{
		table->stop = 1;
		printf("[GOD] : fail to give life\n");
	}
	else
	{
		printf("[GOD] :  success lifes\n");
		table->start = 1;
		manage_life(table);
	}
	if (take_life(table->philosophers, table->phi_number))
		printf("[GOD] : fail to take life\n");
	return (0);
}

