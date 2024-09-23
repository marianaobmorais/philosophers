/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:45:54 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/23 16:32:46 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_structs(t_table *table, t_philos *philos, int count)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->check_vitals);
	pthread_mutex_destroy(&table->check_clock);
	pthread_mutex_destroy(&table->check_meals);
	free(philos);
	free(table->fork);
	free(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (!check_args(argc, argv))
		return (1);
	table = init(argv);
	if (!table)
		return (1);
	monitoring(table);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->philos[i].philo, NULL) != 0)
			printf("Error: pthread_join\n");
		i++;
	}
	free_structs(table, table->philos, table->philo_count);
	return (0);
}
