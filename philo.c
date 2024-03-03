/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 05:55:27 by gcros             #+#    #+#             */
/*   Updated: 2024/02/29 05:14:58 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <number_of_philosophers>
 * <time_to_die>
 * <time_to_eat>
 * <time_to_sleep>
 * number_of_times_each_philosopher_must_eat]
 */
int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		quit(bad_arg);
	init_table(&table, ac, av);
	god(&table);
	destroy_table(&table);
	quit(good_exit);
}
