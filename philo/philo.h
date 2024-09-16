/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:20:17 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/16 20:09:10 by mariaoli         ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t		person;
	int				time_to_die; // or is_alive
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	pthread_mutex_t fork;
	struct s_philo	*next; // or index?
}	t_philo;

typedef struct s_table
{
	int				num_of_philo;
	t_philo			*philo;
	//pthread_t		*philo;
}	t_table;

int		check_args(int argc, char **argv);
t_table	*parse_argv(char **argv);

#endif