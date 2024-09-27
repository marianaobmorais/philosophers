/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:15:02 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/27 10:58:51 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_struct(t_table *table)
{
	sem_close(table->forks_sem); // you should call sem_close before sem_unlink to close the semaphore handles, and then unlink them to remove them from the system.
	sem_close(table->stop_sem); 
	sem_unlink("forks_sem"); 
	sem_unlink("stop_sem");
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
	// while (i < table->philo_count - 1) // not sure why it only works with - 1
	// {
	// 	printf(DEFAULT"waiting pid\n");
	// 	waitpid(-1, NULL, 0);
	// 	i++;
	// }
	while (waitpid(-1, NULL, 0) > 0)
		printf(DEFAULT"waiting pid\n");
	free_struct(table);
	return (0);
}
