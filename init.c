/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:34:47 by gcros             #+#    #+#             */
/*   Updated: 2024/03/13 00:29:01 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_fork **forks, int count);
int	init_philos(t_table	*table, int count);
int	get_times(t_table	*table, int ac, char **av);

int	init_table(t_table	*table, int ac, char **av)
{
	int	n;

	n = ft_atoi(av[1]);
	memset(table, '\0', sizeof(t_table));
	table->number = n;
	if (n < 0 || get_times(table, ac, av) == 0)
		return (0);
	if (pthread_mutex_init(&table->stop_mut, NULL))
		return (0);
	if (pthread_mutex_init(&table->start_mut, NULL))
		return (pthread_mutex_destroy(&table->stop_mut), 0);
	return (init_forks(&table->forks, n) && init_philos(table, n));
}

int	get_times(t_table	*table, int ac, char **av)
{
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		table->eat_count = ft_atoi(av[5]);
	else
		table->eat_count = __LONG_MAX__;
	if (table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0 || table->eat_count < 0)
		return (0);
	return (1);
}

int	init_forks(t_fork **forks, int count)
{
	int	i;

	*forks = malloc(count * sizeof(t_fork));
	if (*forks == NULL)
		return (0);
	memset(*forks, '\0', sizeof(t_fork) * count);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(*forks)[i]._mut, NULL))
			return (0);
		(*forks)[i]._lock = 0;
		(*forks)[i].id = i + 1;
		i++;
	}
	return (1);
}

int	init_philos(t_table	*table, int count)
{
	int	i;

	table->philosophers = malloc(count * sizeof(t_phi));
	if (table->philosophers == NULL)
	{
		free(table->forks);
		pthread_mutex_destroy(&table->stop_mut);
		pthread_mutex_destroy(&table->start_mut);
		return ((long)(table->forks = NULL));
	}
	memset(table->philosophers, '\0', sizeof(t_phi) * count);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&table->philosophers[i]._mut, NULL))
			return (0);
		table->philosophers[i].left_hand = &table->forks[i];
		table->philosophers[i].right_hand = &table->forks[(i + 1) % count];
		table->philosophers[i].stop = &table->stop;
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		i++;
	}
	return (1);
}
