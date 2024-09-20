/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:57:58 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/20 16:32:43 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philos *philos, size_t elapsed_meal_time)
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
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	size_t			elapsed;
	size_t			elapsed_meal_time;

	if (philos->philo_id < philos->next->philo_id)
	{
		first_fork = philos->fork;
		second_fork = philos->next->fork;
	}
	else
	{
		first_fork = philos->next->fork;
		second_fork = philos->fork;
	}
	elapsed_meal_time = elapsed_time(philos->last_meal_time);
	if (is_alive(philos, elapsed_meal_time))
	{
		if (pthread_mutex_lock(&first_fork))
			printf("Error: pthread_mutex_lock failed for philo %d\n", philos->philo_id);
		elapsed = elapsed_time(philos->table->start_time);
		printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"has taken a fork\n"DEFAULT, elapsed, philos->philo_id);
		if (is_alive(philos, elapsed_meal_time))
		{
			if (pthread_mutex_lock(&second_fork))
				printf("Error: pthread_mutex_lock failed for philo %d\n", philos->philo_id);
			elapsed = elapsed_time(philos->table->start_time);
			printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"has taken a fork\n"DEFAULT, elapsed, philos->philo_id);
			
			elapsed = elapsed_time(philos->table->start_time);
			printf(YELLOW"%zu "DEFAULT"%d "BLUE_B"is eating\n"DEFAULT, elapsed, philos->philo_id);
			philos->last_meal_time = get_time();
			usleep(philos->eat_time * 1000);
			if (pthread_mutex_unlock(&first_fork))
				printf("Error: pthread_mutex_unlock failed for philo %d\n", philos->philo_id);
			if (pthread_mutex_unlock(&second_fork))
				printf("Error: pthread_mutex_unlock failed for philo %d\n", philos->philo_id);
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
	while (1) // or meal_count
	{
		eating(philos);
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}
