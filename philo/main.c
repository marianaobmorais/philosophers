/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:45:54 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/12 19:09:21 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_meals;
	pthread_t	*philo;
}	t_data;

int	check_args(int argc, char **argv) // do I accept long or just int? // check if is positive or negative -> is_digit already checks it
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	init_data(t_data *data)
{
	data->num_of_philo = -1;
	data->time_to_die = -1;
	data->time_to_eat = -1;
	data->time_to_sleep = -1;
	data->num_of_meals = -1;
	data->philo = NULL;
}

t_data	*parse_argv(char **argv)
{
	t_data *data;
	int		i;

	init_data(&data);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_of_meals = ft_atoi(argv[5]);
	data->philo = (pthread_t *)malloc(sizeof(pthread_t) * (data->num_of_philo));
	if (!data->philo)
		return (NULL);
	i = 0;
	while (i < data->num_of_philo) //no idea what to do here
	{
		if (pthread_create(&data->philo[i], NULL, /* &routine */, NULL) != 0)
			return (1);
		i++;
	}
	return (data);
}

/* ALLOWED: memset, printf, malloc, free, write,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (!check_args)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	data = parse_argv(argv);
	if (!data)
		return (free(data), 1);
	
	free(data);
	return (0);
}