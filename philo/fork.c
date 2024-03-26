/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:18:06 by gcros             #+#    #+#             */
/*   Updated: 2024/03/24 01:15:05 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->_mut);
	return (1);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_unlock(&fork->_mut);
}
