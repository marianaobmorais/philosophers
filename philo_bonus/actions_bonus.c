/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:50:33 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/30 19:11:50 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_wait(t_philos *philos, size_t interval)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < interval)
	{
		sem_wait(philos->table->monitor_sem);
		if (!philos->is_alive)
		{
			sem_post(philos->table->monitor_sem);
			break ;
		}
		sem_post(philos->table->monitor_sem);
		usleep(500); // reduce to 100?
	}
}

static void	print_message(t_philos *philos, int c)
{
	size_t	elapsed;

	//printf(GREEN"print message function\n" DEFAULT);
	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		if (c == 'f')
			printf(GRAY MESSAGE_FORK DEFAULT, elapsed, philos->id);
		if (c == 'e')
			printf(MAGENTA MESSAGE_EAT DEFAULT, elapsed, philos->id);
		if (c == 's')
			printf(BLUE MESSAGE_SLEEP DEFAULT, elapsed, philos->id);
		if (c == 't')
			printf(YELLOW MESSAGE_THINK DEFAULT, elapsed, philos->id);
	}
	//printf(GREEN"returning from print message\n" DEFAULT);
	sem_post(philos->table->monitor_sem);
}

bool	eating(t_philos *philos)
{
	size_t	elapsed;

	sem_wait(philos->table->forks_sem);

	sem_wait(philos->table->monitor_sem);
	if (!philos->is_alive)
	{
		sem_post(philos->table->monitor_sem);
		sem_post(philos->table->forks_sem);
		return (false);
	}
	sem_post(philos->table->monitor_sem);

	print_message(philos, 'f');
	if (philos->table->philo_count == 1)
	{
		ft_wait(philos, philos->die_time);
		elapsed = elapsed_time(philos->table->start_time);
		printf(RED MESSAGE_DEATH DEFAULT, elapsed, philos->id);
		return (false);
	}

	sem_wait(philos->table->forks_sem);

	sem_wait(philos->table->monitor_sem);
	if (!philos->is_alive)
	{
		sem_post(philos->table->monitor_sem);
		sem_post(philos->table->forks_sem);
		sem_post(philos->table->forks_sem);
		return (false);
	}
	sem_post(philos->table->monitor_sem);

	print_message(philos, 'f');
	print_message(philos, 'e');
	sem_wait(philos->table->monitor_sem);
	philos->last_meal_time = get_time();
	sem_post(philos->table->monitor_sem);

	ft_wait(philos, philos->eat_time);

	sem_wait(philos->table->monitor_sem);
	if (!philos->is_alive)
	{
		sem_post(philos->table->monitor_sem);
		sem_post(philos->table->forks_sem);
		sem_post(philos->table->forks_sem);
		return (false);
	}
	sem_post(philos->table->monitor_sem);

	
	sem_wait(philos->table->monitor_sem);
	philos->meals_eaten += 1;
	sem_post(philos->table->monitor_sem);

	sem_post(philos->table->forks_sem);
	sem_post(philos->table->forks_sem);
	
	printf("exiting eating philo %d\n", philos->id);
	return (true);
}

bool	sleeping(t_philos *philos)
{
	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive)
	{
		print_message(philos, 's');
		ft_wait(philos, philos->sleep_time);
		sem_post(philos->table->monitor_sem);
		return (true);
	}
	sem_post(philos->table->monitor_sem);
	return (false);
}

bool	thinking(t_philos *philos)
{
	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive)
	{
		sem_post(philos->table->monitor_sem);
		print_message(philos, 't');
		return (true);
	}
	sem_post(philos->table->monitor_sem);
	return (false);
}
