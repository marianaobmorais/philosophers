/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:11 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/23 16:54:50 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	print_message(t_philos *philos, char c)
{
	size_t	elapsed;

	pthread_mutex_lock(&philos->table->check_vitals);
	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		if (c == 'f')
			printf(GRAY MESSAGE_FORK DEFAULT, elapsed, philos->philo_id);
		if (c == 'e')
			printf(MAGENTA_H MESSAGE_EAT DEFAULT, elapsed, philos->philo_id);
		if (c == 's')
			printf(BLUE_H MESSAGE_SLEEP DEFAULT, elapsed, philos->philo_id);
		if (c == 't')
			printf(YELLOW_H MESSAGE_THINK DEFAULT, elapsed, philos->philo_id);
		pthread_mutex_unlock(&philos->table->check_vitals);
		return (true);
	}
	pthread_mutex_unlock(&philos->table->check_vitals);
	return (false);
}

static void	unlock_forks(t_philos *philos, int count)
{
	pthread_mutex_unlock(philos->first_fork);
	if (count == 2)
		pthread_mutex_unlock(philos->second_fork);
}

void	eating(t_philos *philos)
{
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
