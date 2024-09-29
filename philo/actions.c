/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:11 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/29 21:23:26 by marianamora      ###   ########.fr       */
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
	if (!if_alive_print_message(philos, 0)) // divide this function between is alive and print message
		return ;
	pthread_mutex_lock(philos->first_fork);
	if (!if_alive_print_message(philos, 'f'))
		return (unlock_forks(philos, 1));
	if (philos->second_fork == philos->first_fork)
		return (unlock_forks(philos, 1));
	pthread_mutex_lock(philos->second_fork);
	if (!if_alive_print_message(philos, 'f'))
		return (unlock_forks(philos, 2));
	if (!if_alive_print_message(philos, 'e'))
		return (unlock_forks(philos, 2));
	pthread_mutex_lock(&philos->table->check_clock);
	philos->last_meal_time = get_time();
	pthread_mutex_unlock(&philos->table->check_clock);
	ft_wait(philos, philos->eat_time);
	if (!if_alive_print_message(philos, 0))
		return (unlock_forks(philos, 2));
	philos->meals_eaten += 1;
	unlock_forks(philos, 2);
}

void	sleeping(t_philos *philos)
{
	if (if_alive_print_message(philos, 's'))
		ft_wait(philos, philos->sleep_time);
}

void	thinking(t_philos *philos)
{
	if (if_alive_print_message(philos, 't'))
		return ;
}
