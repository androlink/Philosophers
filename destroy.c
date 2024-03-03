/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 01:10:03 by gcros             #+#    #+#             */
/*   Updated: 2024/02/29 03:56:42 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(t_fork *forks, int count);
int	destroy_philos(t_philo *philo, int count);

int	destroy_table(t_table *table)
{
	destroy_forks(table->forks, table->forks_number);
	destroy_philos(table->philosophers, table->phi_number);
	free(table->forks);
	free(table->philosophers);
}

int	destroy_forks(t_fork *forks, int count)
{
	int	i;

	i = 0;
	while (forks && i < count && forks[i].id)
	{
		while (pthread_mutex_destroy(&forks[i]._mut) && errno == EBUSY)
			pthread_mutex_unlock(&forks[i]._mut);
		i++;
	}
	return (0);
}

int	destroy_philos(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (philo && i < count && philo[i].id)
	{
		//pthread_detach(philo[i].thread);
		i++;
	}
	return (0);
}