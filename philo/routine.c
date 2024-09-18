/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:57:58 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/18 19:19:57 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philos *philos)
{
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	size_t			elapsed;

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
	if (pthread_mutex_lock(&first_fork))
		printf("Error: pthread_mutex_lock failed for philo %d\n", philos->philo_id);
	elapsed = elapsed_time(philos->table->start_time);
	printf("%zu %d has taken a fork\n", elapsed, philos->philo_id);
	if (pthread_mutex_lock(&second_fork))
		printf("Error: pthread_mutex_lock failed for philo %d\n", philos->philo_id);
	elapsed = elapsed_time(philos->table->start_time);
	printf("%zu %d has taken a fork\n", elapsed, philos->philo_id);
	elapsed = elapsed_time(philos->table->start_time);
	printf("%zu %d is eating\n", elapsed, philos->philo_id);
	usleep(philos->eat_time * 1000);
	if (pthread_mutex_unlock(&first_fork))
		printf("Error: pthread_mutex_unlock failed for philo %d\n", philos->philo_id);
	if (pthread_mutex_unlock(&second_fork))
		printf("Error: pthread_mutex_unlock failed for philo %d\n", philos->philo_id);
}

void	sleep(t_philos *philos)
{
	size_t			elapsed;

	elapsed = elapsed_time(philos->table->start_time);
	printf("%zu %d is sleeping\n", elapsed, philos->philo_id);
	usleep(philos->sleep_time * 1000);
}

void	*routine(void *arg)
{
	t_philos	*philos = (t_philos *)arg;
	size_t		elapsed;
	//int		count_down;
	//bool		has_eaten;
	
	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1) // or meal_count
	{
		eat(philos);
		sleep(philos);
		
		elapsed = elapsed_time(philos->table->start_time);
		printf("%zu %d is thinking\n", elapsed, philos->philo_id);
		// elapsed = elapsed_time(philos->table->start_time);
		// printf("%zu %d died\n", elapsed, philos->philo_id);
	}
	return (NULL);
}
