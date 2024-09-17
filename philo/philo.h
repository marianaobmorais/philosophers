/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:20:17 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/17 19:51:50 by mariaoli         ###   ########.fr       */
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

typedef struct s_table	t_table;
typedef struct s_philos	t_philos;

typedef struct s_philos
{
	pthread_t		philo;
	int				philo_id;
	int				die_time; // or is_alive?
	int				eat_time;
	int				sleep_time;
	int				meals_count;
	pthread_mutex_t fork;
	struct s_philos	*next; // or index?
	t_table			*table;
}	t_philos;

typedef struct s_table
{
	int			philo_count;
	int			start_time;
	t_philos	*philos;
}	t_table;

int		check_args(int argc, char **argv);
t_table	*init(char **argv);
void	free_structs(t_philos *philos, int count);

#endif