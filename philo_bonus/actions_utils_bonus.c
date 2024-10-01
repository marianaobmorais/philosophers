/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:27:28 by mariaoli          #+#    #+#             */
/*   Updated: 2024/10/01 18:28:28 by mariaoli         ###   ########.fr       */
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
		usleep(100);
	}
}

void	print_message(t_philos *philos, int c)
{
	size_t	elapsed;

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
	sem_post(philos->table->monitor_sem);
}
