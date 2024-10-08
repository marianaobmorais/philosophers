/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:40:07 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/30 16:23:06 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(t_philos *philos, size_t interval)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < interval)
	{
		pthread_mutex_lock(&philos->table->check_vitals);
		if (!philos->table->all_alive)
		{
			pthread_mutex_unlock(&philos->table->check_vitals);
			break ;
		}
		pthread_mutex_unlock(&philos->table->check_vitals);
		usleep(500);
	}
}

bool	if_alive_print_message(t_philos *philos, char c)
{
	size_t	elapsed;

	pthread_mutex_lock(&philos->table->check_vitals);
	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		if (c == 'f')
			printf(GRAY MESSAGE_FORK DEFAULT, elapsed, philos->id);
		if (c == 'e')
			printf(MAGENTA_H MESSAGE_EAT DEFAULT, elapsed, philos->id);
		if (c == 's')
			printf(BLUE_H MESSAGE_SLEEP DEFAULT, elapsed, philos->id);
		if (c == 't')
			printf(YELLOW_H MESSAGE_THINK DEFAULT, elapsed, philos->id);
		pthread_mutex_unlock(&philos->table->check_vitals);
		return (true);
	}
	pthread_mutex_unlock(&philos->table->check_vitals);
	return (false);
}
