/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:13 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/29 13:36:29 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_alive(t_philos *philos)
{
	size_t	elapsed_meal_time;
	size_t	elapsed;

	sem_wait(philos->table->monitor_sem);
	elapsed_meal_time = elapsed_time(philos->last_meal_time);
	if (elapsed_meal_time > philos->die_time && philos->is_alive)
	{
		philos->is_alive = false;
		elapsed = elapsed_time(philos->table->start_time);
		printf(RED MESSAGE_DEATH DEFAULT, elapsed, philos->philo_id);
		sem_post(philos->table->monitor_sem);
		return (false);
	}
	sem_post(philos->table->monitor_sem);
	return (true);
}

void	philo_process(t_philos *philos)
{
	int	i;

	if (philos->philo_id % 2 == 0)
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
	i = 0;
	while (i < philos->table->philo_count)
	{
		sem_post(philos->table->stop_sem);
		i++;
	}
	exit(0);
}


// void	philo_process(t_philos *philos)
// {
// 	bool	keep_loop;

// 	if (philos->philo_id % 2 == 0)
// 		usleep(500);
// 	while (1)
// 	{
// 		//printf(GREEN"philo %d process loop\n"DEFAULT, philos->philo_id);
// 		keep_loop = is_alive(philos);
// 		printf("philo %d keep loop == %d\n", philos->philo_id, keep_loop);
// 		if (!keep_loop) // don't know why it is not working
// 		{
// 			//printf(RED"philo %d not alive break loop\n"DEFAULT, philos->philo_id);
// 			break ;
// 		}
// 		eating(philos);
// 		if (philos->meals_eaten == philos->meals_to_eat)
// 			sem_post(philos->table->stop_sem);
// 		sleeping(philos);
// 		thinking(philos);
// 		usleep(500);
// 	}
// 	int i = 0;
// 	while (i < philos->table->philo_count) // proceed to kill processes
// 	{
// 		sem_post(philos->table->stop_sem);
// 		i++;
// 	}
// 	exit(0);
// }
