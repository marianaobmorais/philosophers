/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:57:58 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/23 16:54:04 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	meal_check(t_philos *philos)
{
	if (philos->meals_eaten == philos->meals_to_eat)
	{
		pthread_mutex_lock(&philos->table->check_meals);
		philos->table->ate_all_meals += 1;
		pthread_mutex_unlock(&philos->table->check_meals);
		return (true);
	}
	return (false);
}

static bool	death_check(t_philos *philos)
{
	pthread_mutex_lock(&philos->table->check_vitals);
	if (!philos->table->all_alive)
	{
		pthread_mutex_unlock(&philos->table->check_vitals);
		return (true);
	}
	pthread_mutex_unlock(&philos->table->check_vitals);
	return (false);
}

void	*routine(void *arg)
{
	t_philos	*philos;
	bool		stop_loop;

	philos = (t_philos *)arg;
	stop_loop = false;
	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philos);
		if (philos->second_fork == philos->first_fork)//
			break ;//
		stop_loop = meal_check(philos);
		if (stop_loop)
			break ;
		sleeping(philos);
		thinking(philos);
		stop_loop = death_check(philos);
		if (stop_loop)
			break ;
	}
	return (NULL);
}
