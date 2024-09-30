/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:56:14 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/30 16:23:06 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static bool	meal_count(t_table *table)
// {
// 	if (table->ate_all_meals == table->philo_count)
// 		return (true);
// 	return (false);
// }

// static bool	count_down(t_table *table, int i)
// {
// 	size_t	elapsed_meal_time;
// 	size_t	elapsed;

// 	elapsed_meal_time = elapsed_time(table->philos[i].last_meal_time);
// 	if (elapsed_meal_time > table->philos[i].die_time)
// 	{
// 		sem_wait(table->all_alive); //
// 		elapsed = elapsed_time(table->start_time);
// 		printf(RED"%zu %d died\n"DEFAULT, elapsed, table->philos[i].id);
// 		kill(0, SIGKILL); // kill processes?
// 		//sem_post(table->all_alive); //
// 		return (true);
// 	}
// 	return (false);
// }

// void	monitoring(t_table *table)
// {
// 	bool	stop_loop;
// 	int		i;

// 	stop_loop = false;
// 	while (1)
// 	{
// 		//printf("monitoring loop()\n"); //
// 		i = 0;
// 		while (i < table->philo_count)
// 		{
// 			stop_loop = meal_count(table);
// 			if (stop_loop)
// 				break ;
// 			stop_loop = count_down(table, i);
// 			if (stop_loop)
// 				break ;
// 			i++;
// 		}
// 		if (stop_loop)
// 			break ;
// 		usleep(500);
// 	}
// 	printf(GREEN"Monitoring exiting...\n"DEFAULT); //
// 	exit(0);
// }
