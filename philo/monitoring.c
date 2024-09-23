/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:39:43 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/23 16:24:29 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	meal_count(t_table *table)
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

static bool	count_down(t_table *table, int i)
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
		printf(RED MESSAGE_DEATH DEFAULT, elapsed, table->philos[i].philo_id);
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
				break ;
			stop_loop = count_down(table, i);
			if (stop_loop)
				break ;
			i++;
		}
		if (stop_loop)
			break ;
	}
}
