/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:14:59 by mariaoli          #+#    #+#             */
/*   Updated: 2024/09/16 17:45:45 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static long	ft_atol(char *ptr)
{
	int		i;
	long	sign;
	long	res;

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

static int	ft_isint(char **argv)
{
	int		i;
	long	tmp;

	i = 1;
	while (argv[i])
	{
		tmp = ft_atol(argv[i]);
		if (tmp < 1 || tmp > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

// do I accept long or just int?
// check if is positive or negative -> is_digit already checks it
int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of arguments"), 0);
	if (!ft_isdigit(argv))
		return (printf("Arguments should only contain digits"), 0);
	if (!ft_isint(argv))
		return (printf("Argument values must be between 1 and INT_MAX"), 0); // check this later
	return (1);
}