/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:15:53 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/27 16:02:38 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_threads(t_philos *philos)
{
	if (pthread_create(&philos->monitor_thread, NULL,
			&monitoring, philos) != 0)
		printf("Error: pthread_create\n");
	if (pthread_create(&philos->stop_process_thread, NULL,
			&stop_process, philos) != 0)
		printf("Error: pthread_create\n");
}

void	join_threads(t_philos *philos)
{
	if (pthread_join(philos->monitor_thread, NULL) != 0)
		printf("Error: pthread_join\n");
	if (pthread_join(philos->stop_process_thread, NULL) != 0)
		printf("Error: pthread_join\n");
}
