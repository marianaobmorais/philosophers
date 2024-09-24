/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:15:02 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/24 19:33:05 by mariaoli         ###   ########.fr       */
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
	table->available = sem_open("/available_sem", O_CREAT, 0644, table->philo_count);
	//if (table->available == -1)
	//	return (free(table), NULL);
	table->unavailable = sem_open("/unavailable_sem", O_CREAT, 0644, 0);
	//if (table->unavailable == -1)
	//	return (sem_unlink("/available_sem"), free(table), NULL);
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

void	philo_process(t_philos *philos)
{
	size_t	elapsed;

	if (philos->philo_id % 2 == 0)
		usleep(500);

	sem_wait(philos->table->available);
	elapsed = elapsed_time(philos->table->start_time);
	printf("%zu %d got first fork\n", elapsed, philos->philo_id); // change sentence
	
	sem_wait(philos->table->available);
	elapsed = elapsed_time(philos->table->start_time);
	printf("%zu %d got second fork\n", elapsed, philos->philo_id); // change sentence
	elapsed = elapsed_time(philos->table->start_time);
	printf("%zu %d is eating\n", elapsed, philos->philo_id);
	usleep(philos->eat_time * 1000);

	sem_post(philos->table->unavailable);
	sem_post(philos->table->unavailable);
}

void	main_process()
{
	
	printf("main_process\n");
	return ;
}

void	free_struct(t_table *table)
{
	sem_close(table->available); // you should call sem_close before sem_unlink to close the semaphore handles, and then unlink them to remove them from the system.
	sem_close(table->unavailable);
	sem_unlink("/available_sem"); 
	sem_unlink("/unavailable_sem");
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
			main_process(); // monitoring?
		i++;
	}
	free_struct(table);
	return (0);
}
