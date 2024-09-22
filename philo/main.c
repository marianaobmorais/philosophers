/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:45:54 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/22 20:44:57 by mariaoli         ###   ########.fr       */
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

bool	meal_count(t_table *table)
{
	pthread_mutex_lock(&table->check_meals);
	if (table->ate_all_meals == table->philo_count)
	{
		pthread_mutex_unlock(&table->check_meals);
		return (true);
	}
	pthread_mutex_unlock(&table->check_meals);
	return (false);
}

bool	count_down(t_table *table, int i)
{
	size_t	elapsed_meal_time;
	size_t	elapsed;

	pthread_mutex_lock(&table->check_clock);
	elapsed_meal_time = elapsed_time(table->philos[i].last_meal_time);
	if (elapsed_meal_time > table->philos[i].die_time)
	{
		pthread_mutex_lock(&table->check_vitals);
		table->all_alive = false;
		elapsed = elapsed_time(table->start_time);
		printf(YELLOW_H"%zu "DEFAULT"%d "RED"died\n"DEFAULT, elapsed, table->philos[i].philo_id);
		pthread_mutex_unlock(&table->check_vitals);
		pthread_mutex_unlock(&table->check_clock);
		return (true);
	}
	pthread_mutex_unlock(&table->check_clock);
	return (false);
}

void	monitoring(t_table *table)
{
	bool	stop_loop;
	int		i;

	stop_loop = false;
	while (1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			stop_loop = meal_count(table);
			if (stop_loop)
				break;
			stop_loop = count_down(table, i);
			if (stop_loop)
				break;
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
