/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:21:05 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/27 11:48:35 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

long	validate_and_get_sign(char **str)
{
	long	sign;

	if (!(*str) || **str == '\0')
		exit_error("Input is empty");
	sign = 1;
	while (is_space(**str))
		(*str)++;
	while (**str == '+' || **str == '-')
	{
		if (**str == '-' && sign == 1)
			sign = -1;
		else if (**str == '-' && sign == -1)
			sign = 1;
		(*str)++;
	}
	if (sign == -1)
		exit_error("Negative numbers are not allowed\n");
	return (sign);
}

long	ft_atol(char *str)
{
	long	result;
	long	sign;

	sign = validate_and_get_sign(&str);
	result = 0;
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			exit_error("Number bigger than INT_MAX\n");
		str++;
	}
	if (!is_digit(*str) && *str != '\0')
		exit_error("Invalid input format\n");
	return (result);
}

/*
 *  Convert time from miliseconds (given by the user)
 *  to microseconds to use in USLEEP function
 * 
 *  Check if timestamp is larger than the minimum allowed
*/
void	check_and_parse(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		exit_error("Timestamps must be larger than 60ms\n");
	if (av[5])
		table->limit_of_meals = ft_atol(av[5]);
	else
		table->limit_of_meals = -1;
}
