/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:59:40 by irlozano          #+#    #+#             */
/*   Updated: 2025/03/02 17:59:44 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

bool	parse_fill_rules(char **argv)
{
	int		*rules_elements[4];
	int		i;

	i = 0;
	rules_elements[0] = &get_rules()->philo_nb;
	rules_elements[1] = &get_rules()->time_to_die;
	rules_elements[2] = &get_rules()->time_to_eat;
	rules_elements[3] = &get_rules()->time_to_sleep;
	while (i < 4)
	{
		if (fill_struct(rules_elements[i],
				parse_int(argv[i + 1], i + 1)) == false)
			return (false);
		i++;
	}
	if (argv[5])
	{
		if (fill_struct(&get_rules()->min_meals,
				parse_int(argv[5], 5)) == false)
			return (false);
	}
	else
		get_rules()->min_meals = -1;
	return (true);
}

int	parse_int(char *str, int arg_index)
{
	int		n;
	bool	good_arg;

	n = ft_atoi(str);
	good_arg = true;
	if (arg_index == 1)
	{
		if (n < 1 || n > 200)
			good_arg = false;
	}
	else if (n < 1 || n > INT_MAX)
		good_arg = false;
	if (good_arg == false)
	{
		write_error("🍝 Ups! Invalid argument.\n");
		return (-1);
	}
	return (n);
}

bool	fill_struct(void *dest, int src)
{
	*(int *)dest = src;
	if (src == -1)
		return (false);
	return (true);
}
