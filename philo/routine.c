/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:57:58 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/20 18:56:14 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philos *philos, size_t elapsed_meal_time) // not sure if I need this function. Will work on monitoring and come back to it
{
	size_t	elapsed;

	if (philos->is_alive == false)
		return (0);
	else
	{
		if (elapsed_meal_time > philos->die_time)
		{
			philos->is_alive = false;
			elapsed = elapsed_time(philos->table->start_time);
			printf(YELLOW"%zu "DEFAULT"%d "RED"died\n"DEFAULT, elapsed, philos->philo_id);
			return (0);
		}
		return (1);
	}
}

void	eating(t_philos *philos)
{
	size_t			elapsed;
	size_t			elapsed_meal_time;

	elapsed_meal_time = elapsed_time(philos->last_meal_time);
	if (is_alive(philos, elapsed_meal_time))
	{
		pthread_mutex_lock(philos->first_fork);
		elapsed = elapsed_time(philos->table->start_time);
		printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"has taken a fork\n"DEFAULT, elapsed, philos->philo_id);
		if (is_alive(philos, elapsed_meal_time))
		{
			pthread_mutex_lock(philos->second_fork);
			elapsed = elapsed_time(philos->table->start_time);
			printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"has taken a fork\n"DEFAULT, elapsed, philos->philo_id);
			elapsed = elapsed_time(philos->table->start_time);
			printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"is eating\n"DEFAULT, elapsed, philos->philo_id);
			philos->last_meal_time = get_time();
			usleep(philos->eat_time * 1000);
			philos->meals_eaten += 1;
			pthread_mutex_unlock(philos->first_fork);
			pthread_mutex_unlock(philos->second_fork);
		}
	}
}

void	sleeping(t_philos *philos)
{
	size_t	elapsed;
	size_t	elapsed_meal_time;

	elapsed_meal_time = elapsed_time(philos->last_meal_time);
	if (is_alive(philos, elapsed_meal_time))
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"is sleeping\n"DEFAULT, elapsed, philos->philo_id);
		usleep(philos->sleep_time * 1000);
	}
}

void	thinking(t_philos *philos)
{
	size_t	elapsed;
	size_t	elapsed_meal_time;

	elapsed_meal_time = elapsed_time(philos->last_meal_time);
	if (is_alive(philos, elapsed_meal_time))
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"is thinking\n"DEFAULT, elapsed, philos->philo_id);
	}
}

void	*routine(void *arg)
{
	t_philos	*philos = (t_philos *)arg;

	if (philos->philo_id % 2 == 0)
		usleep(500); // enough time?
	while (1)
	{
		eating(philos);
		if (philos->meals_eaten == philos->meals_to_eat)
			break;
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}
