/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:45:54 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/16 20:10:22 by mariaoli         ###   ########.fr       */
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

void	init_table(t_table *table)
{
	table->num_of_philo = -1;
	table->philo = NULL;
}

void	init_philo(t_philo *philo)
{
	//philo->person = NULL;
	philo->time_to_die = -1;
	philo->time_to_eat = -1;
	philo->time_to_sleep = -1;
	philo->num_of_meals = -1;
	//philo->fork = NULL;
}

t_table	*parse_argv(char **argv)
{
	(void)argv;
	return (NULL); //placeholder
// 	t_table *table;
// 	int		i;

// 	table = (t_table *)malloc(sizeof(t_table));
// 	if (!table)
// 		return (printf("Error: malloc\n"), NULL);
// 	init_table(table);
// 	table->num_of_philo = ft_atoi(argv[1]);
// 	table->time_to_die = ft_atoi(argv[2]);
// 	table->time_to_eat = ft_atoi(argv[3]);
// 	table->time_to_sleep = ft_atoi(argv[4]);
// 	if (argv[5])
// 		table->num_of_meals = ft_atoi(argv[5]);
// 	table->philo->person = (pthread_t *)malloc(sizeof(pthread_t) * (table->num_of_philo));
// 	if (!table->philo)
// 		return (NULL);
// 	i = 0;
// 	while (i < table->num_of_philo) // where do I join?
// 	{
// 		if (pthread_create(&table->philo->person[i], NULL, &routine, NULL) != 0)
// 			printf("Error: pthread_create\n");
// 		i++;
// 	}
// 	i = 0;
// 	while (i < table->num_of_philo) // where do I join?
// 	{
// 		if (pthread_join(table->philo->person[i], NULL) != 0)
// 			printf("Error: pthread_join\n");
// 		i++;
// 	}
// /* 	while (i < table->num_of_philo) // need to destroy it later
// 	{
// 		pthread_mutex_init(&table->fork[i], NULL);
// 		i++;
// 	} */
// 	return (table);
}


/* ALLOWED: memset, printf, malloc, free, write,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock */

int	main(int argc, char **argv)
{
	t_table	*table;
	
	if (!check_args(argc, argv))
		return (1);
	table = parse_argv(argv);
	if (!table)
		return (1);
	
	free(table);
	return (0);
}
