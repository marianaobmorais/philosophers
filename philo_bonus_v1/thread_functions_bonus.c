/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:02:15 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/30 16:23:06 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	meals_check(t_philos *philos)
{
	sem_wait(philos->table->monitor_sem);
	if (philos->meals_eaten == philos->meals_to_eat)
	{
		philos->is_full = true;
		sem_post(philos->table->monitor_sem);
		sem_post(philos->table->stop_sem);
		return (true);
	}
	sem_post(philos->table->monitor_sem);
	return (false);
}

static bool	count_down(t_philos *philos)
{
	size_t	elapsed_meal_time;
	size_t	elapsed;

	sem_wait(philos->table->monitor_sem);
	elapsed_meal_time = elapsed_time(philos->last_meal_time);
	if (elapsed_meal_time > philos->die_time)
	{
		philos->is_alive = false;
		elapsed = elapsed_time(philos->table->start_time);
		printf(RED MESSAGE_DEATH DEFAULT, elapsed, philos->id);
		sem_post(philos->table->monitor_sem);
		sem_post(philos->table->stop_sem);
		return (true);
	}
	sem_post(philos->table->monitor_sem);
	return (false);
}

void	*monitoring(void *arg)
{
	t_philos	*philos;
	bool		stop_loop;

	philos = (t_philos *)arg;
	while (1)
	{
		sem_wait(philos->table->monitor_sem);
		if (!philos->is_alive)
		{
			sem_post(philos->table->monitor_sem);
			break ;
		}
		sem_post(philos->table->monitor_sem);
		stop_loop = meals_check(philos);
		if (stop_loop)
			break ;
		stop_loop = count_down(philos);
		if (stop_loop)
			break ;
		usleep(500);
	}
	return (NULL);
}

void	*stop_process(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	sem_wait(philos->table->stop_sem);
	sem_wait(philos->table->monitor_sem);
	if (!philos->is_full)
	{
		philos->is_alive = false;
		sem_post(philos->table->monitor_sem);
		sem_post(philos->table->stop_sem);
	}
	else
		sem_post(philos->table->monitor_sem);
	return (NULL);
}
