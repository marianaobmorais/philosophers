/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:50:33 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/29 13:35:10 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_message(t_philos *philos, int c)
{
	size_t	elapsed;

	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		if (c == 'f')
			printf(GRAY MESSAGE_FORK DEFAULT, elapsed, philos->philo_id);
		if (c == 'e')
			printf(MAGENTA MESSAGE_EAT DEFAULT, elapsed, philos->philo_id);
		if (c == 's')
			printf(BLUE MESSAGE_SLEEP DEFAULT, elapsed, philos->philo_id);
		if (c == 't')
			printf(YELLOW MESSAGE_THINK DEFAULT, elapsed, philos->philo_id);
	}
	sem_post(philos->table->monitor_sem);
}

bool	eating(t_philos *philos)
{
	sem_wait(philos->table->forks_sem);
	if (!is_alive(philos))
	{
		sem_post(philos->table->forks_sem);
		return (false);
	}
	print_message(philos, 'f');
		
	sem_wait(philos->table->forks_sem);
	if (!is_alive(philos))
	{
		sem_post(philos->table->forks_sem);
		sem_post(philos->table->forks_sem);
		return (false);
	}
	print_message(philos, 'f');
	print_message(philos, 'e');
	sem_wait(philos->table->monitor_sem);
	philos->last_meal_time = get_time();
	sem_post(philos->table->monitor_sem);

	
	usleep(philos->eat_time * 1000); // change this

	if (!is_alive(philos))
	{
		sem_post(philos->table->forks_sem);
		sem_post(philos->table->forks_sem);
		return (false);
	}

	sem_wait(philos->table->monitor_sem);
	philos->meals_eaten += 1;
	sem_post(philos->table->monitor_sem);

	sem_post(philos->table->forks_sem);
	sem_post(philos->table->forks_sem);
	return (true);
}

bool	sleeping(t_philos *philos)
{
	if (is_alive(philos))
	{
		print_message(philos, 's');
		usleep(philos->sleep_time * 1000); // change this
		return (true);
	}
	return (false);
}

bool	thinking(t_philos *philos)
{
	if (is_alive(philos))
	{
		print_message(philos, 't');
		return (true);
	}
	return (false);
}
