/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:14:29 by gcros             #+#    #+#             */
/*   Updated: 2024/02/29 03:36:53 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	quit(t_exit_code code)
{
	printf("%s\n", str_quit(code));
	exit(code);
}

const char	*str_quit(t_exit_code code)
{
	const char	*strs[] = {
	[good_exit] = "UwU",
	[bad_arg] = "<number_of_philosophers> <time_to_die> <time_to_eat>"
		" <time_to_sleep>"
		" [number_of_times_each_philosopher_must_eat]",
	};

	return (strs[code]);
}
