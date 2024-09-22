/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:45:54 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/22 20:09:30 by mariaoli         ###   ########.fr       */
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
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->check_vitals);
	pthread_mutex_destroy(&table->check_clock);
	pthread_mutex_destroy(&table->check_meals);
	free(philos);
	free(table->fork);
	//free(table); // if I uncomment this, I get: free(): double free detected in tcache 2. zsh: IOT instruction (core dumped)  ./philo 3 300 100 100
}

void	monitoring(t_table *table)
{
	size_t	elapsed_meal_time;
	size_t	elapsed;
	bool	stop_loop;
	int		i;

	stop_loop = false;
	while (1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			pthread_mutex_lock(&table->check_meals);
			if (table->ate_all_meals == table->philo_count)
			{
				stop_loop = true;
				pthread_mutex_unlock(&table->check_meals);	
				break;
			}
			pthread_mutex_unlock(&table->check_meals);	
			pthread_mutex_lock(&table->check_clock);
			elapsed_meal_time = elapsed_time(table->philos[i].last_meal_time);
			pthread_mutex_unlock(&table->check_clock);
			if (elapsed_meal_time > table->philos[i].die_time)
			{
				pthread_mutex_lock(&table->check_vitals);
				table->all_alive = false;
				elapsed = elapsed_time(table->start_time);
				printf(YELLOW_H"%zu "DEFAULT"%d "RED"died\n"DEFAULT, elapsed, table->philos[i].philo_id);
				pthread_mutex_unlock(&table->check_vitals);
				stop_loop = true;
				break;
			}
			i++;
		}
		if (stop_loop)
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
	monitoring(table);
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
