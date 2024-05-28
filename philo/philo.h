/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 05:55:30 by gcros             #+#    #+#             */
/*   Updated: 2024/04/25 01:49:03 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>

# define PH_AT_SLEEP_TIME 1000

typedef enum e_exit_code
{
	good_exit,
	bad_arg,
	init_failed,
}	t_exit_code;

typedef struct s_fork
{
	int				id;
	int				_lock;
	pthread_mutex_t	_mut;
}	t_fork;

typedef struct s_table	t_table;

typedef union u_hands
{
	struct
	{
		t_fork	*left_hand;
		t_fork	*right_hand;
	};
	t_fork	*forks[2];
}	t_hands;
typedef struct s_philosopher
{
	int				id;
	long			eat_count;
	suseconds_t		life_time;
	pthread_t		thread;
	int				is_dead;
	int				*stop;
	t_table			*table;
	t_hands			hands;
	pthread_mutex_t	_mut;
} t_philosopher, t_phi,	t_philo;

typedef struct s_table
{
	t_philosopher	*philosophers;
	t_fork			*forks;
	size_t			number;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	long			eat_count;
	int				stop;
	int				start;
	pthread_mutex_t	stop_mut;
	pthread_mutex_t	start_mut;
	pthread_mutex_t	print_mut;
}	t_table;

void		quit(t_exit_code code);
const char	*str_quit(t_exit_code code);
int			init_table(t_table	*table, int ac, char **av);
int			destroy_table(t_table *table);

int			ft_atoi(const char *nptr);
long		to_long(struct timeval t1);
void		*born(t_philosopher *self);
long		time_ref(long test, long set);
void		drop_fork(t_fork *fork);
int			pick_fork(t_fork *fork);
int			is_dead(t_philosopher *self);
int			check_stop(t_table *table);
int			is_num(char *s);
int			sleep_or_die(suseconds_t sleep_time);
void		ph_call(char *msg, t_philo *self);

int			god(t_table *table);
void		ph_life(t_philosopher *me);

#endif
