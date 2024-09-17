/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:45:54 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/17 17:24:53 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *ptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ptr[i] == 32 || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ptr[i] != '\0' && (ptr[i] >= 48 && ptr[i] <= 57))
	{
		res = res * 10 + (ptr[i] - 48);
		i++;
	}
	return (res * sign);
}

void	*routine(/* void *arg */)
{
	printf("timestamp_in_ms X has taken a fork\n");
	printf("timestamp_in_ms X has taken a fork\n");
	printf("timestamp_in_ms X is eating\n");
	printf("timestamp_in_ms X is sleeping\n");
	printf("timestamp_in_ms X is thinking\n");
	printf("timestamp_in_ms X died\n");
	return (NULL);
}

t_philos	init_philos(char **argv, t_table *table, int id)
{
	t_philos	philos;

	if (pthread_create(&philos.philo, NULL, &routine, NULL) != 0)
		printf("Error: pthread_create\n");
	philos.philo_id = id;
	philos.die_time = ft_atoi(argv[2]); // or is_alive?
	philos.eat_time = ft_atoi(argv[3]);
	philos.sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		philos.meals_count = ft_atoi(argv[5]);
	pthread_mutex_init(&philos.fork, NULL);
	philos.table = table;
	return (philos);
}

t_table	*init(char **argv)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_count = ft_atoi(argv[1]);
	table->philos = (t_philos *)malloc(sizeof(t_philos) * (table->philo_count));
	if (!table->philos)
		return (NULL);
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i] = init_philos(argv, table, i + 1);
		table->philos[i].next = &table->philos[i + 1];
		i++;
	}
	i--;
	table->philos[i].next = &table->philos[0];
	return (table);
}

/* ALLOWED: memset, printf, malloc, free, write,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

void	free_structs(t_philos *philos, int count)
{
	int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
	free(philos);
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
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->philos[i].philo, NULL) != 0)
			printf("Error: pthread_join\n");
		i++;
	}
	i = 0;
	free_structs(table->philos, table->philo_count);
	free(table);
	return (0);
}
