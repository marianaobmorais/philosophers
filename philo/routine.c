/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:57:58 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/22 19:58:00 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(t_philos *philos, char c)
{
	size_t	elapsed;

	pthread_mutex_lock(&philos->table->check_vitals);
	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		if (c == 'f')
			printf(YELLOW_H"%zu "DEFAULT"%d "MAGENTA_H"has taken a fork\n"DEFAULT, elapsed, philos->philo_id);
		if (c == 'e')
			printf(YELLOW_H"%zu "DEFAULT"%d "MAGENTA_H"is eating\n"DEFAULT, elapsed, philos->philo_id);
		if (c == 's')
			printf(YELLOW_H"%zu "DEFAULT"%d "MAGENTA_H"is sleeping\n"DEFAULT, elapsed, philos->philo_id);
		if (c == 't')
			printf(YELLOW_H"%zu "DEFAULT"%d "MAGENTA_H"is thinking\n"DEFAULT, elapsed, philos->philo_id);
		pthread_mutex_unlock(&philos->table->check_vitals);
		return (true);
	}
	pthread_mutex_unlock(&philos->table->check_vitals);
	return (false);
}

void	eating(t_philos *philos)
{
	if (!is_alive(philos, 0))
		return ;
	pthread_mutex_lock(philos->first_fork);
	if (!is_alive(philos, 'f'))
	{
		pthread_mutex_unlock(philos->first_fork);
		return ;
	}
	pthread_mutex_lock(philos->second_fork);
	if (!is_alive(philos, 'f'))
	{
		pthread_mutex_unlock(philos->first_fork);
		pthread_mutex_unlock(philos->second_fork);
		return ;
	}
	if (!is_alive(philos, 'e'))
	{
		pthread_mutex_unlock(philos->first_fork);
		pthread_mutex_unlock(philos->second_fork);
		return ;
	}
	pthread_mutex_lock(&philos->table->check_clock);
	philos->last_meal_time = get_time();
	pthread_mutex_unlock(&philos->table->check_clock);
	usleep(philos->eat_time * 1000);
	if (!is_alive(philos, 0))
	{
		pthread_mutex_unlock(philos->first_fork);
		pthread_mutex_unlock(philos->second_fork);
		return ;
	}
	philos->meals_eaten += 1;
	pthread_mutex_unlock(philos->first_fork);
	pthread_mutex_unlock(philos->second_fork);
}

void	sleeping(t_philos *philos)
{
	if (!is_alive(philos, 's'))
		return ;
	else
		usleep(philos->sleep_time * 1000);
}

void	thinking(t_philos *philos)
{
	if (!is_alive(philos, 't'))
		return ;
}

void	*routine(void *arg)
{
	t_philos	*philos = (t_philos *)arg;

	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philos);
		if (philos->meals_eaten == philos->meals_to_eat)
		{
			pthread_mutex_lock(&philos->table->check_meals);
			philos->table->ate_all_meals += 1;
			pthread_mutex_unlock(&philos->table->check_meals);
			break ;
		}
		sleeping(philos);
		thinking(philos);
		pthread_mutex_lock(&philos->table->check_vitals);
		if (!philos->table->all_alive)
		{
			pthread_mutex_unlock(&philos->table->check_vitals);
			break ;
		}
		pthread_mutex_unlock(&philos->table->check_vitals);
	}
	return (NULL);
}
