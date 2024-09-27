/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:50:25 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/27 01:08:17 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_philos *philos, t_table *table, int i, char **argv)
{
	philos->philo_id = i + 1;
	philos->is_alive = true;
	philos->is_full = false;
	philos->die_time = ft_atoi(argv[2]);
	philos->eat_time = ft_atoi(argv[3]);
	philos->last_meal_time = table->start_time;
	philos->sleep_time = ft_atoi(argv[4]);
	philos->meals_to_eat = -1;
	if (argv[5])
		philos->meals_to_eat = ft_atoi(argv[5]);
	philos->meals_eaten = 0;
	philos->table = table;
}

t_table	*init(char **argv)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_count = ft_atoi(argv[1]);
	table->start_time = get_time();

	//semaphores open
	sem_unlink("forks_sem");
	table->forks_sem = sem_open("forks_sem", O_CREAT, 0644, table->philo_count);
	if (table->forks_sem == SEM_FAILED)
		return (free(table), NULL);
	sem_unlink("stop_sem");
	table->stop_sem = sem_open("stop_sem", O_CREAT, 0644, 0);
	if (table->stop_sem == SEM_FAILED)
		return (free(table), NULL);
	sem_unlink("is_full_sem");
	table->is_full_sem = sem_open("is_full_sem", O_CREAT, 0644, 0);
	if (table->is_full_sem == SEM_FAILED)
		return (free(table), NULL);

	table->philos = (t_philos *)malloc(sizeof(t_philos) * table->philo_count);
	if (!table->philos)
		return (free(table), NULL);
	i = 0;
	while (i < table->philo_count)
	{
		init_philos(&table->philos[i], table, i, argv);
		i++;
	}
	return (table);
}
