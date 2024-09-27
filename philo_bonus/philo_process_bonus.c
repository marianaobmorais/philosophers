/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:54:13 by marianamora       #+#    #+#             */
/*   Updated: 2024/09/27 10:22:01 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitoring(void *arg)
{
	t_philos	*philos;
	size_t		elapsed_meal_time;
	size_t		elapsed;

	philos = (t_philos *)arg;
	while (1)
	{
		if (!philos->is_alive)
			break ;
		if (philos->meals_eaten == philos->meals_to_eat) //(philos->is_full)
		{
			philos->is_full = true;
			//printf("Philo id = %d is full\n", philos->philo_id); //
			sem_post(philos->table->stop_sem);
			break ;
		}
		elapsed_meal_time = elapsed_time(philos->last_meal_time);
		if (elapsed_meal_time > philos->die_time)
		{
			philos->is_alive = false;
			sem_post(philos->table->stop_sem);
			elapsed = elapsed_time(philos->table->start_time);
			printf(RED"%zu %d died\n"DEFAULT, elapsed, philos->philo_id);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

void	*stop_process(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;

	sem_wait(philos->table->stop_sem);
	if (!philos->is_full)
	{
		//printf("philo id  %d is dead\n", philos->philo_id); //
		philos->is_alive = false;
		sem_post(philos->table->stop_sem);
	}
	return (NULL);
}

//-------------------//

void	eating(t_philos *philos)
{
	size_t	elapsed;

	if (!philos->is_alive || philos->is_full)
		return ;

	sem_wait(philos->table->forks_sem);

	if (!philos->is_alive || philos->is_full)
		return ;
	
	elapsed = elapsed_time(philos->table->start_time);
	printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);

	sem_wait(philos->table->forks_sem);

	if (!philos->is_alive || philos->is_full)
		return ;
		
	elapsed = elapsed_time(philos->table->start_time);
	printf(GRAY"%zu %d got a fork\n"DEFAULT, elapsed, philos->philo_id);
	
	if (!philos->is_alive || philos->is_full)
		return ;
	
	elapsed = elapsed_time(philos->table->start_time);
	printf(MAGENTA"%zu %d is eating\n"DEFAULT, elapsed, philos->philo_id);
	philos->last_meal_time = get_time();
	usleep(philos->eat_time * 1000);

	if (!philos->is_alive || philos->is_full)
		return ;
		
	philos->meals_eaten += 1;
	
	sem_post(philos->table->forks_sem);
	sem_post(philos->table->forks_sem);
}

void	sleeping(t_philos *philos)
{
	size_t	elapsed;

	if (!philos->is_alive || philos->is_full)
		return ;
	elapsed = elapsed_time(philos->table->start_time);
	printf(BLUE"%zu %d is sleeping\n"DEFAULT, elapsed, philos->philo_id);
	usleep(philos->sleep_time * 1000);
}

void	thinking(t_philos *philos)
{
	size_t	elapsed;

	if (!philos->is_alive || philos->is_full)
		return ;
	elapsed = elapsed_time(philos->table->start_time);
	printf(YELLOW"%zu %d is thinking\n"DEFAULT, elapsed, philos->philo_id);
}

//---------------------------------------//

//works with determined food argv[5]

// void	*monitoring(void *arg)
// {
// 	t_philos	*philos;
// 	size_t		elapsed_meal_time;
// 	size_t		elapsed;

// 	philos = (t_philos *)arg;
// 	while (1)
// 	{
// 		// if (!philos->is_alive)
// 		// 	break ;
// 		if (philos->meals_eaten == philos->meals_to_eat)
// 		{
// 			philos->is_full = true;
// 			//printf("Philo id = %d is full\n", philos->philo_id);
// 			sem_post(philos->table->stop_sem);
// 			break ;
// 		}
// 		elapsed_meal_time = elapsed_time(philos->last_meal_time);
// 		if (elapsed_meal_time > philos->die_time /* || !philos->is_alive */)
// 		{
// 			philos->is_alive = false;
// 			sem_post(philos->table->stop_sem);
// 			//sem_post(philos->table->is_full_sem);// is alive actually
// 			elapsed = elapsed_time(philos->table->start_time);
// 			printf(RED"%zu %d died\n"DEFAULT, elapsed, philos->philo_id);
// 			break ;
// 		}
// 		usleep(500);
// 	}
// 	return (NULL);
// }

// void	*philo_death(void *arg)
// {
// 	t_philos	*philos;

// 	philos = (t_philos *)arg;

// 	sem_wait(philos->table->stop_sem);

// 	if (!philos->is_alive)
// 	{
// 		printf("!philos->is_alive id = %d\n", philos->philo_id);
// 		philos->is_alive = false; // when I change it here, does it change in every process in which this thread is called?
// 		sem_post(philos->table->stop_sem);
// 	}
// 	return (NULL);
// }

//---------------------------------------------------//

// void	*monitoring(void *arg)
// {
// 	t_philos	*philos;
// 	size_t		elapsed_meal_time;
// 	size_t		elapsed;

// 	philos = (t_philos *)arg;
// 	while (1)
// 	{
// 		//if (!philos->is_alive)
// 		//	break ;
// 		if (philos->is_full)
// 		{
// 			printf("Philo id = %d is full\n", philos->philo_id);
// 			sem_post(philos->table->stop_sem); //
// 			sem_post(philos->table->is_full_sem); //
// 			break ;
// 		}
// 		elapsed_meal_time = elapsed_time(philos->last_meal_time);
// 		if (elapsed_meal_time > philos->die_time)
// 		{
// 			philos->is_alive = false;
// 			sem_post(philos->table->stop_sem);
// 			elapsed = elapsed_time(philos->table->start_time);
// 			printf(RED"%zu %d died\n"DEFAULT, elapsed, philos->philo_id);
// 			break ;
// 		}
// 		usleep(500);
// 	}
// 	return (NULL);
// }

// void *philo_death(void *arg)
// {
// 	t_philos	*philos;
// 	int		i;

// 	philos = (t_philos *)arg;
// 	while (1)
// 	{
// 		sem_wait(philos->table->stop_sem);
// 		if (!philos->is_alive)
// 		{
// 			//sem_post(philos->table->stop_sem);
// 			break;
// 		}
// 		//wait for all philosophers to be full
// 		if (philos->is_full)
// 		{
// 			i = 0;
// 			while (i < philos->table->philo_count)
// 			{
// 				printf("semaphore waiting id = %d\n", philos->philo_id);
// 				sem_wait(philos->table->is_full_sem);
// 				printf("semaphore waiting done id = %d\n", philos->philo_id);
// 				i++;
// 			}
// 			if (i == philos->table->philo_count)
// 			{
// 				printf("exit loop id = %d\n", philos->philo_id);
// 				break;
// 			}
// 		}
// 		sem_post(philos->table->stop_sem); // not sure
// 		usleep(500);
// 	}
// 	return (NULL);
// }

void	philo_process(t_philos *philos)
{
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
			philos->is_full = true;
			break ;
		}
		sleeping(philos);
		thinking(philos);
		if (!philos->is_alive)
			break ;
	}
	if (pthread_join(philos->monitor_thread, NULL) != 0)
		printf("Error: pthread_join\n");
	if (pthread_join(philos->stop_process_thread, NULL) != 0)
		printf("Error: pthread_join\n");
	exit(0);
}
