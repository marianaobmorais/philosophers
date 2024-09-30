/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:50:33 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/30 16:23:06 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_message(t_philos *philos, int c)
{
	size_t	elapsed;

	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive && !philos->is_full)
	{
		elapsed = elapsed_time(philos->table->start_time);
		if (c == 'f')
			printf(GRAY MESSAGE_FORK DEFAULT, elapsed, philos->id);
		if (c == 'e')
			printf(MAGENTA MESSAGE_EAT DEFAULT, elapsed, philos->id);
	}
	sem_post(philos->table->monitor_sem);
}

void	eating(t_philos *philos)
{
	sem_wait(philos->table->forks_sem);
	print_message(philos, 'f');
	if (philos->table->philo_count == 1)
	{
		sem_post(philos->table->forks_sem);
		return ;
	}
	sem_wait(philos->table->forks_sem);
	print_message(philos, 'f');
	print_message(philos, 'e');
	sem_wait(philos->table->monitor_sem);
	philos->last_meal_time = get_time();
	sem_post(philos->table->monitor_sem);
	usleep(philos->eat_time * 1000);
	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive && !philos->is_full)
		philos->meals_eaten += 1;
	sem_post(philos->table->monitor_sem);
	sem_post(philos->table->forks_sem);
	sem_post(philos->table->forks_sem);
}

void	sleeping(t_philos *philos)
{
	size_t	elapsed;

	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive && !philos->is_full)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(BLUE MESSAGE_SLEEP DEFAULT, elapsed, philos->id);
		sem_post(philos->table->monitor_sem);
		usleep(philos->sleep_time * 1000);
	}
	else
		sem_post(philos->table->monitor_sem);
}

void	thinking(t_philos *philos)
{
	size_t	elapsed;

	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive && !philos->is_full)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(YELLOW MESSAGE_THINK DEFAULT, elapsed, philos->id);
	}
	sem_post(philos->table->monitor_sem);
}
