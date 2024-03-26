/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:32:08 by gcros             #+#    #+#             */
/*   Updated: 2024/03/24 19:50:29 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t stop_count = 0;

int	check_stop(t_table *table)
{
	int	val;

	pthread_mutex_lock(&table->stop_mut);
	val = table->stop;
	pthread_mutex_unlock(&table->stop_mut);
	stop_count++;
	return (val);
}

int	check_start(t_table *table)
{
	int	val;

	pthread_mutex_lock(&table->start_mut);
	val = table->start;
	pthread_mutex_unlock(&table->start_mut);
	return (val);
}

