/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:45:54 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/21 16:02:11 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_structs(t_table *table, t_philos *philos, int count)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < count)
	{
		//free(philos->table->fork[i]);
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->check_vitals);
	free(philos);
}

void	monitoring(t_table *table)
{
	size_t	elapsed_meal_time;
	size_t	elapsed;
	int		i;

	while (1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			//mutex
			elapsed_meal_time = elapsed_time(table->philos[i].last_meal_time);//
			if (elapsed_meal_time > table->philos[i].die_time)
			{
				//mutex
				table->philos[i].is_alive = false; //
				elapsed = elapsed_time(table->start_time);
				printf(YELLOW"%zu "DEFAULT"%d "RED"died\n"DEFAULT, elapsed, table->philos[i].philo_id);
				break;
			}
			i++;
		}
		if (!table->philos[i].is_alive)
			break;
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (!check_args(argc, argv))
		return (1);
	table = init(argv);
	if (!table)
		return (1);
	//monitoring(table);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->philos[i].philo, NULL) != 0)
			printf("Error: pthread_join\n");
		i++;
	}
	free_structs(table, table->philos, table->philo_count);
	free(table);
	return (0);
}
