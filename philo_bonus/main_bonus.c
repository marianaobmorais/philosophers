/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:15:02 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/25 01:43:36 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_philos *philos, t_table *table, int i, char **argv)
{
	philos->philo_id = i + 1;
	philos->die_time = ft_atoi(argv[2]);
	philos->eat_time = ft_atoi(argv[3]);
	philos->last_meal_time = table->start_time;
	philos->sleep_time = ft_atoi(argv[4]);
	philos->meals_to_eat = -1;
	if (argv[5])
		philos->meals_to_eat = ft_atoi(argv[5]);
	philos->meals_eaten = 0;
	philos->table = table;
}

t_table	*init(int argc, char **argv)
{
	(void)argc;
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_count = ft_atoi(argv[1]);
	table->all_alive = true;
	table->ate_all_meals = 0;
	table->start_time = get_time();
	table->forks = sem_open("/available_sem", O_CREAT, 0644, table->philo_count);
	//if (table->available == -1)
	//	return (free(table), NULL);
	table->philos = (t_philos *)malloc(sizeof(t_philos) * table->philo_count);
	if (!table->philos)
		return (free(table), NULL);
	i = 0;
	while (i < table->philo_count)
	{
		init_philos(&table->philos[i], table, i, argv);
		i++;
	}
	return (table);
}

void	eating(t_philos *philos)
{
	size_t	elapsed;

	sem_wait(philos->table->forks);
	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(GRAY"%zu %d got first fork\n"DEFAULT, elapsed, philos->philo_id); // change sentence
	}

	if (philos->table->philo_count == 1)
		return ;

	sem_wait(philos->table->forks);
	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(GRAY"%zu %d got second fork\n"DEFAULT, elapsed, philos->philo_id); // change sentence
	}
	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(MAGENTA"%zu %d is eating\n"DEFAULT, elapsed, philos->philo_id);
		philos->last_meal_time = get_time();
	}
	usleep(philos->eat_time * 1000);
	if (philos->table->all_alive)
		philos->meals_eaten += 1;
	sem_post(philos->table->forks);
	sem_post(philos->table->forks);
}

void	sleeping(t_philos *philos)
{
	size_t	elapsed;

	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(BLUE"%zu %d is sleeping\n"DEFAULT, elapsed, philos->philo_id);
		usleep(philos->sleep_time * 1000);
	}
}

void	thinking(t_philos *philos)
{
	size_t	elapsed;

	if (philos->table->all_alive)
	{
		elapsed = elapsed_time(philos->table->start_time);
		printf(YELLOW"%zu %d is thinking\n"DEFAULT, elapsed, philos->philo_id);
	}
}

void	philo_process(t_philos *philos)
{
	if (philos->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philos);
		if (philos->meals_eaten == philos->meals_to_eat)
		{
			philos->table->ate_all_meals += 1;
			break ;
		}
		if (!philos->table->all_alive)
			break ;
		sleeping(philos);
		thinking(philos);
	}
	exit(0);
}

static bool	meal_count(t_table *table)
{
	if (table->ate_all_meals == table->philo_count)
		return (true);
	return (false);
}

static bool	count_down(t_table *table, int i)
{
	size_t	elapsed_meal_time;
	size_t	elapsed;

	elapsed_meal_time = elapsed_time(table->philos[i].last_meal_time);
	if (elapsed_meal_time > table->philos[i].die_time)
	{
		table->all_alive = false;
		elapsed = elapsed_time(table->start_time);
		printf(RED"%zu %d died\n"DEFAULT, elapsed, table->philos[i].philo_id);
		return (true);
	}
	return (false);
}

void	monitoring(t_table *table)
{
	printf("monitoring\n");

	bool	stop_loop;
	int		i;

	stop_loop = false;
	while (1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			stop_loop = meal_count(table);
			if (stop_loop)
				break ;
			stop_loop = count_down(table, i);
			if (stop_loop)
				break ;
			i++;
		}
		if (stop_loop)
			break ;
	}
	exit(0);
}

void	free_struct(t_table *table)
{
	sem_close(table->forks); // you should call sem_close before sem_unlink to close the semaphore handles, and then unlink them to remove them from the system.
	sem_unlink("/available_sem"); 
	free(table);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	//int		fd[2];
	int		i;
	t_table	*table;

	if (!check_args(argc, argv))
		return (1);
	table = init(argc, argv);
	if (!table)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		//if (pipe(fd) == -1) // maybe I should use it for monitoring?
		//	return (1);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			philo_process(&table->philos[i]);
		else
			monitoring(table); // monitoring?
		i++;
	}
	free_struct(table);
	return (0);
}
