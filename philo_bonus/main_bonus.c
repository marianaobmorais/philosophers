/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:15:02 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/27 14:36:25 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_struct(t_table *table, t_philos *philos)
{
	sem_close(table->forks_sem);
	sem_close(table->stop_sem);
	sem_close(table->monitor_sem);
	sem_unlink("forks_sem"); 
	sem_unlink("stop_sem");
	sem_unlink("monitor_sem");
	free(philos);
	free(table);
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;
	t_table	*table;

	if (!check_args(argc, argv))
		return (1);
	table = init(argv);
	if (!table)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			philo_process(&table->philos[i]);
		i++;
	}
	i = 0;
	while (waitpid(ALL_CHILD, NULL, 0) > 0)
		;
	free_struct(table, table->philos);
	return (0);
}
