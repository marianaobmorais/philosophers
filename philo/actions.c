/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:11 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/23 18:39:54 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_forks(t_philos *philos, int count)
{
	pthread_mutex_unlock(philos->first_fork);
	if (count == 2)
		pthread_mutex_unlock(philos->second_fork);
}

static void	fork_order(t_philos *philos, int i)
{
	if (philos->philo_id % 2 == 1)
	{
		if (philos->philo_id == philos->table->philo_count)
		{
			philos->first_fork = &philos->table->fork[i];
			philos->second_fork = &philos->table->fork[0];
		}
		else
		{
			philos->first_fork = &philos->table->fork[i];
			philos->second_fork = &philos->table->fork[i + 1];
		}
		return ;
	}
	if (philos->philo_id == philos->table->philo_count)
	{
		philos->first_fork = &philos->table->fork[0];
		philos->second_fork = &philos->table->fork[i];
	}
	else
	{
		philos->first_fork = &philos->table->fork[i + 1];
		philos->second_fork = &philos->table->fork[i];
	}
}

void	eating(t_philos *philos)
{
	fork_order(philos, philos->philo_id - 1);
	if (!print_message(philos, 0))
		return ;
	pthread_mutex_lock(philos->first_fork);
	if (!print_message(philos, 'f'))
		return (unlock_forks(philos, 1));
	if (philos->second_fork == philos->first_fork)
		return (unlock_forks(philos, 1));
	pthread_mutex_lock(philos->second_fork);
	if (!print_message(philos, 'f'))
		return (unlock_forks(philos, 2));
	if (!print_message(philos, 'e'))
		return (unlock_forks(philos, 2));
	pthread_mutex_lock(&philos->table->check_clock);
	philos->last_meal_time = get_time();
	pthread_mutex_unlock(&philos->table->check_clock);
	usleep(philos->eat_time * 1000);
	if (!print_message(philos, 0))
		return (unlock_forks(philos, 2));
	philos->meals_eaten += 1;
	unlock_forks(philos, 2);
}

void	sleeping(t_philos *philos)
{
	if (print_message(philos, 's'))
		usleep(philos->sleep_time * 1000);
}

void	thinking(t_philos *philos)
{
	if (print_message(philos, 't'))
		return ;
}
