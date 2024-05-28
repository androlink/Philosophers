/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 05:55:27 by gcros             #+#    #+#             */
/*   Updated: 2024/05/07 04:56:58 by gcros            ###   ########.fr       */
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
	t_table		table;
	t_exit_code	code;

	code = good_exit;
	if (ac != 5 && ac != 6)
		return (quit(bad_arg));
	if (!init_table(&table, ac, av))
		return (quit(init_failed));
	god(&table);
	destroy_table(&table);
	return (quit(code));
}
