/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:15:53 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/28 15:22:52 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_threads(t_philos *philos)
{
	if (pthread_create(&philos->monitor_thread, NULL,
			&monitoring, philos) != 0)
		printf("Error: pthread_create\n");
	// if (pthread_create(&philos->stop_process_thread, NULL,
	// 		&stop_process, philos) != 0)
	// 	printf("Error: pthread_create\n");
}

void	join_threads(t_philos *philos)
{
	if (pthread_join(philos->monitor_thread, NULL) != 0)
		printf("Error: pthread_join\n");
	// if (pthread_join(philos->stop_process_thread, NULL) != 0)
	// 	printf("Error: pthread_join\n");
}
