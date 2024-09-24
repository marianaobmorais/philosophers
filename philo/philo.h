/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:20:17 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/24 13:43:53 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include "colors.h"

# define ERR_ARG_NUM "Error: Incorrect number of arguments\n"
# define ERR_ARG_INT "Error: Arguments should only contain digits\n"
# define ERR_ARG_LIM "Error: Argument values must be between 1 and INT_MAX\n"

# define MESSAGE_FORK "%zu %d has taken a fork\n"
# define MESSAGE_EAT "%zu %d is eating\n"
# define MESSAGE_SLEEP "%zu %d is sleeping\n"
# define MESSAGE_THINK "%zu %d is thinking\n"
# define MESSAGE_DEATH "%zu %d died\n"

typedef struct s_table	t_table;
typedef struct s_philos	t_philos;

typedef struct s_philos
{
	pthread_t		philo;
	int				philo_id;
	size_t			die_time;
	size_t			eat_time;
	size_t			last_meal_time;
	size_t			sleep_time;
	int				meals_to_eat;
	int				meals_eaten;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_table			*table;
}	t_philos;

typedef struct s_table
{
	int				philo_count;
	bool			all_alive;
	int				ate_all_meals;
	size_t			start_time;
	pthread_mutex_t	check_vitals;
	pthread_mutex_t	check_meals;
	pthread_mutex_t	check_clock;
	pthread_mutex_t	*fork;
	t_philos		*philos;
}	t_table;

int			check_args(int argc, char **argv);
int			ft_atoi(char *ptr);
t_table		*init(char **argv);
void		*routine(void *arg);
bool		print_message(t_philos *philos, char c);
void		ft_wait(t_philos *philos, size_t interval);
void		eating(t_philos *philos);
void		sleeping(t_philos *philos);
void		thinking(t_philos *philos);
size_t		get_time(void);
size_t		elapsed_time(size_t start_time);
void		monitoring(t_table *table);
void		free_structs(t_table *table, t_philos *philos, int count);

#endif