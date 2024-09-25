/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:24:16 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/23 18:34:52 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->check_vitals, NULL);
	pthread_mutex_init(&table->check_clock, NULL);
	pthread_mutex_init(&table->check_meals, NULL);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
}

static t_philos	philos_iter(char **argv, t_table *table, int i)
{
	t_philos	philos;

	philos.philo_id = i + 1;
	philos.die_time = ft_atoi(argv[2]);
	philos.eat_time = ft_atoi(argv[3]);
	philos.last_meal_time = table->start_time;
	philos.sleep_time = ft_atoi(argv[4]);
	philos.meals_to_eat = -1;
	philos.meals_eaten = 0;
	if (argv[5])
		philos.meals_to_eat = ft_atoi(argv[5]);
	philos.table = table;
	return (philos);
}

static void	init_philos(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i] = philos_iter(argv, table, i);
		i++;
	}
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philos[i].philo, NULL,
				&routine, &table->philos[i]) != 0)
			printf("Error: pthread_create\n");
		i++;
	}
}

t_table	*init(char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_count = ft_atoi(argv[1]);
	table->all_alive = true;
	table->ate_all_meals = 0;
	table->start_time = get_time();
	table->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (table->philo_count));
	if (!table->fork)
		return (free(table), NULL);
	table->philos = (t_philos *)malloc(sizeof(t_philos)
			* (table->philo_count));
	if (!table->philos)
		return (free(table->fork), free(table), NULL);
	init_mutexes(table);
	init_philos(table, argv);
	return (table);
}
