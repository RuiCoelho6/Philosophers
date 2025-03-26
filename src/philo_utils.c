/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:18:44 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/26 15:37:20 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handler(mtx, "lock");
	if (*threads == philo_nbr)
		ret = true;
	mutex_handler(mtx, "unlock");
	return (ret);
}

void	write_debug(char *status, t_philo *philo, long elapsed)
{
	if (ft_strcmp(status, "taken_first_fork") == 0
		&& !end_sim(philo->table))
		printf("%6ld philo: %d has taken the first fork [%d]\n",
			elapsed, philo->id,
			philo->first_fork->fork_id);
	if (ft_strcmp(status, "taken_second_fork") == 0
		&& !end_sim(philo->table))
		printf("%6ld philo: %d has taken the second fork [%d]\n",
			elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (ft_strcmp(status, "eating") == 0 && !end_sim(philo->table))
		printf("%6ld philo: %d is eating | meal counter: %ld\n",
			elapsed, philo->id,
			philo->meal_counter);
	else if (ft_strcmp(status, "sleeping") == 0 && !end_sim(philo->table))
		printf("%6ld philo: %d is sleeping\n", elapsed, philo->id);
	else if (ft_strcmp(status, "thinking") == 0 && !end_sim(philo->table))
		printf("%6ld philo: %d is thinking\n", elapsed, philo->id);
	else if (ft_strcmp(status, "died") == 0)
		printf("%6ld philo: %d died\n", elapsed, philo->id);
}

void	print_status(t_philo *philo, char *op, bool debug)
{
	long	elapsed;

	elapsed = get_time("millisecond") - philo->table->start_sim;
	if (philo->is_full)
		return ;
	mutex_handler(&philo->table->print_mtx, "lock");
	if (debug)
		write_debug(op, philo, elapsed);
	else
	{
		if ((ft_strcmp(op, "taken_first_fork") == 0
				|| ft_strcmp(op, "taken_second_fork") == 0)
			&& !end_sim(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (ft_strcmp(op, "eating") == 0 && !end_sim(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (ft_strcmp(op, "sleeping") == 0 && !end_sim(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (ft_strcmp(op, "thinking") == 0 && !end_sim(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (ft_strcmp(op, "died") == 0)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	mutex_handler(&philo->table->print_mtx, "unlock");
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	exit_error(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(1);
}
