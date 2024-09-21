/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:24:16 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/21 16:17:09 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(char *ptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ptr[i] == 32 || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ptr[i] != '\0' && (ptr[i] >= 48 && ptr[i] <= 57))
	{
		res = res * 10 + (ptr[i] - 48);
		i++;
	}
	return (res * sign);
}

t_philos	init_philos(char **argv, t_table *table, int i)
{
	t_philos	philos;

	philos.philo_id = i + 1;
	philos.die_time = ft_atoi(argv[2]); // input in milliseconds
	philos.eat_time = ft_atoi(argv[3]);
	philos.last_meal_time = table->start_time;
	philos.sleep_time = ft_atoi(argv[4]);
	philos.meals_to_eat = -1;
	philos.meals_eaten = 0;
	if (argv[5])
		philos.meals_to_eat = ft_atoi(argv[5]);
	if (philos.philo_id < table->philo_count)
	{
		philos.first_fork = &table->fork[i];
		philos.second_fork = &table->fork[i + 1];
	}
	else
	{
		philos.first_fork = &table->fork[0];
		philos.second_fork = &table->fork[i];
	}
	philos.table = table;
	return (philos);
}

t_table	*init(char **argv)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_count = ft_atoi(argv[1]);
	table->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (table->philo_count));
	if (!table->fork)
		return (free(table), NULL);
	pthread_mutex_init(&table->check_vitals, NULL);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
	table->start_time = get_time();
	table->philos = (t_philos *)malloc(sizeof(t_philos) * (table->philo_count));
	if (!table->philos)
		return (free(table->fork), free(table), NULL);
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i] = init_philos(argv, table, i);
		i++;
	}
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philos[i].philo, NULL, &routine, &table->philos[i]) != 0)
			printf("Error: pthread_create\n");
		i++;
	}
	return (table);
}
