/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:13 by marianamora       #+#    #+#             */
/*   Updated: 2024/10/01 17:21:40 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// bool	is_alive(t_philos *philos)
// {
// 	size_t	elapsed_meal_time;
// 	size_t	elapsed;

// 	sem_wait(philos->table->monitor_sem);
// 	elapsed_meal_time = elapsed_time(philos->last_meal_time);
// 	if (elapsed_meal_time > philos->die_time && philos->is_alive)
// 	{
// 		philos->is_alive = false;
// 		elapsed = elapsed_time(philos->table->start_time);
// 		printf(RED MESSAGE_DEATH DEFAULT, elapsed, philos->id);
// 		sem_post(philos->table->monitor_sem);
// 		return (false);
// 	}
// 	sem_post(philos->table->monitor_sem);
// 	return (true);
// }

void	*monitoring(void *arg)
{
	size_t		elapsed_meal_time;
	size_t		elapsed;
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		sem_wait(philos->table->monitor_sem);//
		elapsed_meal_time = elapsed_time(philos->last_meal_time);
		if (elapsed_meal_time >philos->die_time && philos->is_alive)
		{
			philos->is_alive = false;
			sem_post(philos->table->monitor_sem);//
			elapsed = elapsed_time(philos->table->start_time);
			printf(RED MESSAGE_DEATH DEFAULT, elapsed, philos->id);
			break ;
		}
		sem_post(philos->table->monitor_sem);//
		usleep(500);
	}
	return (NULL);
}

void	philo_process(t_philos *philos)
{
	int	i;

	if (pthread_create(&philos->monitor_thread, NULL, &monitoring, philos) != 0)
		printf("Error: pthread_create\n");

	if (philos->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (!eating(philos))
			break ;
		if (philos->meals_eaten == philos->meals_to_eat)
			sem_post(philos->table->stop_sem);
		if (!sleeping(philos))
			break ;
		if (!thinking(philos))
			break ;
		usleep(500);
	}

	printf("about to join thread philo %d", philos->id); // why isn't the thread joining?
	
	if (pthread_join(philos->monitor_thread, NULL) != 0)
		printf("Error: pthread_join\n");

	i = 0;
	while (i < philos->table->philo_count)
	{
		sem_post(philos->table->stop_sem);
		i++;
	}
	free_table(philos->table);
	exit(0);
}
