/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:15:02 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/29 21:41:34 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_structs(t_table *table, t_philos *philos)
{
	if (philos)
		free(philos);
	if (table)
	{
		sem_close(table->forks_sem);
		sem_close(table->stop_sem);
		sem_close(table->monitor_sem);
		sem_close(table->death_sem); // not sure
		sem_unlink("forks_sem");
		sem_unlink("stop_sem");
		sem_unlink("monitor_sem");
		sem_unlink("death_sem"); // not sure
		free(table);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_table	*table;

	if (!check_args(argc, argv))
		return (1);
	table = init(argv);
	if (!table)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid== -1)
			return (1);
		if (table->philos[i].pid == 0)
			philo_process(&table->philos[i]);
		i++;
	}

	//wait for all philos to be full or one philo to be dead
	i = 0;
	while (i < table->philo_count)
	{
		sem_wait(table->stop_sem);
		i++;
	}

	//release all forks? do I need this?
	i = 0;
	while (i < table->philo_count)
	{
		sem_post(table->forks_sem);
		i++;
	}
	
	//kill all the processes
	i = 0;
	while (i < table->philo_count)
	{
		kill(table->philos[i].pid, SIGTERM/* SIGKILL */);
		i++;
	}
	
	//wait for all child processes
	int status;
	i = 0;
	while (i < table->philo_count)
	{ 
		waitpid(table->philos[i].pid, &status, 0);
		i++;
	}
	// int status;
	// while (waitpid(ALL_CHILD, &status, 0) > 0)
	// 	;
	free_structs(table, table->philos);
	return (0);
}
