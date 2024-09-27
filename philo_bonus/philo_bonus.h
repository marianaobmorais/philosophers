/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:04:12 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/27 12:11:14 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include "colors.h"

#include <fcntl.h>
//#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>

# define ERR_ARG_NUM "Error: Incorrect number of arguments\n"
# define ERR_ARG_INT "Error: Arguments should only contain digits\n"
# define ERR_ARG_LIM "Error: Argument values must be between 1 and INT_MAX\n"

# define ALL_CHILD -1

typedef struct s_table	t_table;
typedef struct s_philos	t_philos;

typedef struct s_philos
{
	pthread_t	monitor_thread;
	pthread_t	stop_process_thread;
	int			philo_id;
	bool		is_alive;
	bool		is_full;
	size_t		die_time;
	size_t		eat_time;
	size_t		last_meal_time;
	size_t		sleep_time;
	int			meals_to_eat;
	int			meals_eaten;
	t_table		*table;
}	t_philos;

typedef struct s_table
{
	int			philo_count;
	size_t		start_time;
	sem_t		*forks_sem;
	sem_t		*stop_sem;
	sem_t		*monitor_sem;
	t_philos	*philos;
}	t_table;

int		check_args(int argc, char **argv);
int		ft_atoi(char *ptr);
t_table	*init(char **argv);
size_t	elapsed_time(size_t start_time);
size_t	get_time(void);
void	philo_process(t_philos *philos);
void	eating(t_philos *philos);
void	sleeping(t_philos *philos);
void	thinking(t_philos *philos);
//void	monitoring(t_table *table);

#endif