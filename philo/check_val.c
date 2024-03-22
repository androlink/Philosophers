/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:32:08 by gcros             #+#    #+#             */
/*   Updated: 2024/03/20 00:22:59 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_table *table)
{
	int	val;

	pthread_mutex_lock(&table->stop_mut);
	val = table->stop;
	pthread_mutex_unlock(&table->stop_mut);
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

