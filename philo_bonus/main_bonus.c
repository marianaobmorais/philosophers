/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:15:02 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/24 14:58:47 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* typedef struct s_philos
{
	int			philo_id;
	size_t		die_time;
	size_t		eat_time;
	size_t		last_meal_time;
	size_t		sleep_time;
	int			meals_to_eat;
	int			meals_eaten;
	t_table		*table;
}	t_philos; */

/* typedef struct s_table
{
	int			philo_count;
	bool		all_alive;
	int			ate_all_meals;
	size_t		start_time;
	sem_t		fork;
	t_philos	*philos;
}	t_table; */

t_table	*init(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philo_count = ft_atoi(argv[1]);
	table->all_alive = true;
	table->ate_all_meals = 0;
	table->start_time = get_time();
	sem_init(&table->fork_utensil, table->philo_count, 2/* table->philo_count */); //not sure. two being the number of forks each philo needs
	//table->philos = ;
	return (table);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		fd[2];
	int		i;
	t_table	*table;
	sem_t	fork_utensil;

	if (!check_args(argc, **argv))
		return (1);
	table = init(argc, argv);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			philo_process();
		else
			main_process();
		i++;
	}
	sem_destroy(&fork_utensil);
	free(table);
	return (0);
}