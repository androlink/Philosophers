/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:18:06 by gcros             #+#    #+#             */
/*   Updated: 2024/05/28 12:36:54 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_fork(t_fork *fork)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&fork->_mut);
	if (fork->_lock == 0)
	{
		i = 1;
		fork->_lock = 1;
	}
	pthread_mutex_unlock(&fork->_mut);
	return (i);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->_mut);
	fork->_lock = 0;
	pthread_mutex_unlock(&fork->_mut);
}
