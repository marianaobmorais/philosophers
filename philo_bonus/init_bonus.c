/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:50:25 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/26 14:09:50 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_philos *philos, t_table *table, int i, char **argv)
{
	philos->philo_id = i + 1;
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
	table->ate_all_meals = 0;
	table->start_time = get_time();

	//semaphores open
	sem_unlink("all_alive_sem");
	table->all_alive = sem_open("all_alive_sem", O_CREAT, 0644, 1);
	if (table->all_alive == SEM_FAILED)
		return (free(table), NULL);
	sem_unlink("forks_sem");
	table->forks = sem_open("forks_sem", O_CREAT, 0644, table->philo_count);
	if (table->forks == SEM_FAILED)
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
	//printf(GREEN"table init succesful\n"DEFAULT);
	return (table);
}
