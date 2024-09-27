/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:13 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/27 11:19:18 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philos *philos)
{
	size_t	elapsed;

	if (!philos->is_alive || philos->is_full) // check if possible data race
		return ;

	sem_wait(philos->table->forks_sem);

	if (!philos->is_alive || philos->is_full) // check if possible data race
		return ;
	
	elapsed = elapsed_time(philos->table->start_time);
	printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);

	sem_wait(philos->table->forks_sem);

	if (!philos->is_alive || philos->is_full) // check if possible data race
		return ;
		
	elapsed = elapsed_time(philos->table->start_time);
	printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);
	
	if (!philos->is_alive || philos->is_full) // check if possible data race
		return ;
	
	elapsed = elapsed_time(philos->table->start_time);
	printf(MAGENTA"%zu %d is eating\n"DEFAULT, elapsed, philos->philo_id);
	philos->last_meal_time = get_time();
	usleep(philos->eat_time * 1000);

	if (!philos->is_alive || philos->is_full) // check if possible data race
		return ;
		
	philos->meals_eaten += 1;
	
	sem_post(philos->table->forks_sem);
	sem_post(philos->table->forks_sem);
}

void	sleeping(t_philos *philos)
{
	size_t	elapsed;

	if (!philos->is_alive || philos->is_full) // check if possible data race
		return ;
	elapsed = elapsed_time(philos->table->start_time);
	printf(BLUE"%zu %d is sleeping\n"DEFAULT, elapsed, philos->philo_id);
	usleep(philos->sleep_time * 1000);
}

void	thinking(t_philos *philos)
{
	size_t	elapsed;

	if (!philos->is_alive || philos->is_full) // check if possible data race
		return ;
	elapsed = elapsed_time(philos->table->start_time);
	printf(YELLOW"%zu %d is thinking\n"DEFAULT, elapsed, philos->philo_id);
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
		if (!philos->is_alive) // Check if the philosopher is still alive // check if possible data race
		{
			printf("Philosopher %d detected as dead (monitoring)\n", philos->philo_id); //
			break ;
		}
		if (philos->meals_eaten == philos->meals_to_eat) // check if possible data race
		{
			printf("Philosopher %d is full, posting stop semaphore.\n", philos->philo_id); //
			philos->is_full = true; // check if possible data race
			sem_post(philos->table->stop_sem);
			break ;
		}
		elapsed_meal_time = elapsed_time(philos->last_meal_time);  // check if possible data race
		if (elapsed_meal_time > philos->die_time)
		{
			printf("Philosopher %d died after %zu ms, posting stop semaphore.\n", philos->philo_id, elapsed_meal_time); //
			philos->is_alive = false; // check if possible data race
			sem_post(philos->table->stop_sem);
			elapsed = elapsed_time(philos->table->start_time); // check if possible data race
			printf(RED"%zu %d died\n"DEFAULT, elapsed, philos->philo_id);
			//break ;
		}
		usleep(500);
	}
	return (NULL);
}

void	*stop_process(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;

	printf("Philosopher %d waiting on stop semaphore.\n", philos->philo_id);
	sem_wait(philos->table->stop_sem);
	if (!philos->is_full) // check if possible data race
	{
		printf("Philosopher %d is not full, setting is_alive to false and posting semaphore.\n", philos->philo_id);
		philos->is_alive = false; // check if possible data race
		sem_post(philos->table->stop_sem);
	}
	return (NULL);
}

void	philo_process(t_philos *philos)
{
	//size_t	elapsed_meal_time;

	if (pthread_create(&philos->monitor_thread, NULL, &monitoring, philos) != 0)
			printf("Error: pthread_create\n");
	if (pthread_create(&philos->stop_process_thread, NULL, &stop_process, philos) != 0)
			printf("Error: pthread_create\n");
	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philos);
		if (philos->meals_eaten == philos->meals_to_eat)
		{
			printf("Philosopher %d has eaten all meals, setting is_full.\n", philos->philo_id);
			philos->is_full = true; // check if possible data race
			break ;
		}
		sleeping(philos);
		thinking(philos);
		if (!philos->is_alive) // check if possible data race
		{
			printf("Philosopher %d detected as dead in process loop about to break loop.\n", philos->philo_id);
			break ;
		}
	}
	if (pthread_join(philos->monitor_thread, NULL) != 0)
		printf("Error: pthread_join\n");
	if (pthread_join(philos->stop_process_thread, NULL) != 0)
		printf("Error: pthread_join\n");
	printf("exiting philo process id = %d\n", philos->philo_id);
	exit(0);
}
