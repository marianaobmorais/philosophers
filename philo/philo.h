/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:20:17 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/19 19:24:13 by mariaoli         ###   ########.fr       */
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

typedef struct s_table	t_table;
typedef struct s_philos	t_philos;

typedef struct s_philos
{
	pthread_t		philo;
	int				philo_id;
	bool			is_alive;
	size_t			die_time;
	size_t			eat_time;
	size_t			last_meal_time;
	size_t			sleep_time;
	size_t			meals_count;
	pthread_mutex_t fork;
	struct s_philos	*next;
	t_table			*table;
}	t_philos;

typedef struct s_table
{
	int			philo_count;
	size_t		start_time;
	t_philos	*philos;
}	t_table;

int			check_args(int argc, char **argv);
t_table		*init(char **argv);
t_philos	init_philos(char **argv, t_table *table, int id);
void		free_structs(t_philos *philos, int count);
void		*routine(void *arg);
size_t		get_time(void);
size_t		elapsed_time(size_t start_time);

#endif