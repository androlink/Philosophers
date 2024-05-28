/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:14:29 by gcros             #+#    #+#             */
/*   Updated: 2024/05/07 04:55:17 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	quit(t_exit_code code)
{
	const char	*str;
	size_t		i;

	if (code != 0)
	{
		i = 0;
		str = str_quit(code);
		while (str[i])
			i++;
		write(2, str, i);
		write(2, "\n", 1);
	}
	exit(code);
}

const char	*str_quit(t_exit_code code)
{
	const char	*strs[] = {
	[good_exit] = "UwU",
	[bad_arg] = "<number_of_philosophers> <time_to_die> <time_to_eat>"
		" <time_to_sleep>"
		" [number_of_times_each_philosopher_must_eat]",
	[init_failed] = "bad thing append",
	};

	return (strs[code]);
}
