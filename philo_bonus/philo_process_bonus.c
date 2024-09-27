/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:13 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/27 15:12:40 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philos *philos)
{
	size_t	elapsed;

	sem_wait(philos->table->forks_sem);

	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive && !philos->is_full)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);
	}
	sem_post(philos->table->monitor_sem);

	if (philos->table->philo_count == 1)
	{
		sem_post(philos->table->forks_sem);
		return ;
	}

	sem_wait(philos->table->forks_sem);

	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive && !philos->is_full)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);
	}
	sem_post(philos->table->monitor_sem);

	sem_wait(philos->table->monitor_sem);
	if (philos->is_alive && !philos->is_full)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(MAGENTA"%zu %d is eating\n"DEFAULT, elapsed, philos->philo_id);
	}
	sem_post(philos->table->monitor_sem);


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
	if (philos->is_alive && !philos->is_full) // check if possible data race
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(BLUE"%zu %d is sleeping\n"DEFAULT, elapsed, philos->philo_id);
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
	if (philos->is_alive && !philos->is_full) // check if possible data race
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(YELLOW"%zu %d is thinking\n"DEFAULT, elapsed, philos->philo_id);
		//sem_post(philos->table->monitor_sem);
	}
	sem_post(philos->table->monitor_sem);
}

//-------------------//

void	*monitoring(void *arg)
{
	t_philos	*philos;
	size_t		elapsed_meal_time;
	size_t		elapsed;

	philos = (t_philos *)arg;
	while (1)
	{
		sem_wait(philos->table->monitor_sem);
		if (!philos->is_alive) // Check if the philosopher is still alive // check if possible data race
		{
			sem_post(philos->table->monitor_sem);
			//printf("Philosopher %d detected as dead (monitoring)\n", philos->philo_id); //
			break ;
		}
		sem_post(philos->table->monitor_sem);

		sem_wait(philos->table->monitor_sem);
		if (philos->meals_eaten == philos->meals_to_eat) // check if possible data race
		{
			//printf(DEFAULT"Philosopher %d is full, posting stop semaphore.\n", philos->philo_id); //
			philos->is_full = true; // check if possible data race
			sem_post(philos->table->monitor_sem);
			sem_post(philos->table->stop_sem);
			break ;
		}
		sem_post(philos->table->monitor_sem);

		sem_wait(philos->table->monitor_sem);
		elapsed_meal_time = elapsed_time(philos->last_meal_time);  // check if possible data race
		if (elapsed_meal_time > philos->die_time)
		{
			//printf("Philosopher %d died after %zu ms, posting stop semaphore.\n", philos->philo_id, elapsed_meal_time); //
			
			philos->is_alive = false; // check if possible data race
			
			elapsed = elapsed_time(philos->table->start_time); // check if possible data race
			printf(RED"%zu %d died\n"DEFAULT, elapsed, philos->philo_id); // not sure if it is necessary, probably is
			sem_post(philos->table->monitor_sem);
			sem_post(philos->table->stop_sem);
			break ;
		}
		sem_post(philos->table->monitor_sem);
		usleep(500);
	}
	return (NULL);
}

void	*stop_process(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;

	//printf("Philosopher %d waiting on stop semaphore.\n", philos->philo_id);
	sem_wait(philos->table->stop_sem);
	
	sem_wait(philos->table->monitor_sem);
	if (!philos->is_full) // check if possible data race
	{
		//printf("Philosopher %d is not full, setting is_alive to false and posting semaphore.\n", philos->philo_id);
		philos->is_alive = false; // check if possible data race
		sem_post(philos->table->monitor_sem);
		sem_post(philos->table->stop_sem);
	}
	else
		sem_post(philos->table->monitor_sem);
	return (NULL);
}

void	create_threads(t_philos *philos)
{
	if (pthread_create(&philos->monitor_thread, NULL, &monitoring, philos) != 0)
			printf("Error: pthread_create\n");
	if (pthread_create(&philos->stop_process_thread, NULL, &stop_process, philos) != 0)
			printf("Error: pthread_create\n");
}

void	join_threads(t_philos *philos)
{
	if (pthread_join(philos->monitor_thread, NULL) != 0)
		printf("Error: pthread_join\n");
	if (pthread_join(philos->stop_process_thread, NULL) != 0)
		printf("Error: pthread_join\n");
}

void	philo_process(t_philos *philos)
{
	create_threads(philos);
	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philos);
		if (philos->table->philo_count == 1)
			break ;
		if (philos->meals_eaten == philos->meals_to_eat)
		{
			//printf("Philosopher %d has eaten all meals, setting is_full.\n", philos->philo_id);
			sem_wait(philos->table->monitor_sem);
			philos->is_full = true; // check if possible data race
			sem_post(philos->table->monitor_sem);
			break ;
		}
		sleeping(philos);
		thinking(philos);
		sem_wait(philos->table->monitor_sem);
		if (!philos->is_alive) // check if possible data race
		{
			sem_post(philos->table->monitor_sem);
			//printf(RED"Philosopher %d detected as dead in process loop about to break loop.\n"DEFAULT, philos->philo_id);
			break ;
		}
		sem_post(philos->table->monitor_sem);
		//usleep(500);
	}
	join_threads(philos);
	exit(0);
}
