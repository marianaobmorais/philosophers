/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:13 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/25 23:37:34 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philos *philos)
{
	size_t	elapsed;

	sem_wait(philos->table->forks);

	//sem_wait(philos->table->all_alive);
	elapsed = elapsed_time(philos->table->start_time);
	printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);
	//sem_post(philos->table->all_alive);

	sem_wait(philos->table->forks);

	//sem_wait(philos->table->all_alive);
	elapsed = elapsed_time(philos->table->start_time);
	printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);
	//sem_post(philos->table->all_alive);

	
	//sem_wait(philos->table->all_alive);
	elapsed = elapsed_time(philos->table->start_time);
	printf(MAGENTA"%zu %d is eating\n"DEFAULT, elapsed, philos->philo_id);
	philos->last_meal_time = get_time();
	//sem_post(philos->table->all_alive);
	
	usleep(philos->eat_time * 1000);
	
	//sem_wait(philos->table->all_alive);
	philos->meals_eaten += 1;
	//sem_post(philos->table->all_alive);
	
	sem_post(philos->table->forks);
	sem_post(philos->table->forks);
}

void	sleeping(t_philos *philos)
{
	size_t	elapsed;

	//sem_wait(philos->table->all_alive);
	elapsed = elapsed_time(philos->table->start_time);
	printf(BLUE"%zu %d is sleeping\n"DEFAULT, elapsed, philos->philo_id);
	usleep(philos->sleep_time * 1000);
	//sem_post(philos->table->all_alive);
}

void	thinking(t_philos *philos)
{
	size_t	elapsed;

	//sem_wait(philos->table->all_alive);
	elapsed = elapsed_time(philos->table->start_time);
	printf(YELLOW"%zu %d is thinking\n"DEFAULT, elapsed, philos->philo_id);
	//sem_post(philos->table->all_alive);
}

void	philo_process(t_philos *philos)
{
	//printf(BLUE"philo_process() id = %d\n"DEFAULT, philos->philo_id); //
	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		//printf("philo_process() loop id = %d\n", philos->philo_id); //
		eating(philos);
		if (philos->meals_eaten == philos->meals_to_eat)
		{
			philos->table->ate_all_meals += 1;
			break ;
		}
		// if (!philos->table->all_alive)
		// 	break ;
		sleeping(philos);
		thinking(philos);
	}
	printf(GREEN"Philosopher %d exiting...\n"DEFAULT, philos->philo_id); //
	exit(0);
}
