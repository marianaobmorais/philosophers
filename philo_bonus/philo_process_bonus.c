/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:13 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/27 15:54:54 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	stop_loop(t_philos *philos)
{
	if (philos->table->philo_count == 1)
		return (true);
	if (philos->meals_eaten == philos->meals_to_eat)
	{
		sem_wait(philos->table->monitor_sem);
		philos->is_full = true;
		sem_post(philos->table->monitor_sem);
		return (true);
	}
	return (false);
}

void	philo_process(t_philos *philos)
{
	create_threads(philos);
	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philos);
		if (stop_loop(philos))
			break ;
		sleeping(philos);
		thinking(philos);
		sem_wait(philos->table->monitor_sem);
		if (!philos->is_alive)
		{
			sem_post(philos->table->monitor_sem);
			break ;
		}
		sem_post(philos->table->monitor_sem);
		usleep(500);
	}
	join_threads(philos);
	exit(0);
}
