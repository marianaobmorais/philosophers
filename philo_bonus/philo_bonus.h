/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:04:12 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/26 14:15:29 by marianamora      ###   ########.fr       */
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

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>

# define ERR_ARG_NUM "Error: Incorrect number of arguments\n"
# define ERR_ARG_INT "Error: Arguments should only contain digits\n"
# define ERR_ARG_LIM "Error: Argument values must be between 1 and INT_MAX\n"

typedef struct s_table	t_table;
typedef struct s_philos	t_philos;

typedef struct s_philos
{
	int			philo_id;
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
	int		philo_count;
	sem_t	*all_alive;
	int		ate_all_meals;
	size_t	start_time;
	sem_t	*forks;
	t_philos	*philos;
}	t_table;

int		check_args(int argc, char **argv);
int		ft_atoi(char *ptr);
t_table	*init(char **argv);
void	init_philos(t_philos *philos, t_table *table, int i, char **argv);
size_t	elapsed_time(size_t start_time);
size_t	get_time(void);
void	philo_process(t_philos *philos);
void	eating(t_philos *philos);
void	sleeping(t_philos *philos);
void	thinking(t_philos *philos);
void	monitoring(t_table *table);

#endif