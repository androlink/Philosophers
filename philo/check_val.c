/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:32:08 by gcros             #+#    #+#             */
/*   Updated: 2024/03/27 02:48:26 by gcros            ###   ########.fr       */
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
