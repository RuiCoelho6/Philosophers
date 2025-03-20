/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:18:44 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/20 13:21:33 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool_mtx(&table->table_mtx, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handler(mtx, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	mutex_handler(mtx, UNLOCK);
	return (ret);
}

void	write_debug(t_status status, t_philo *philo, long elapsed)
{
	if (status == TAKEN_FIRST_FORK && !end_sim(philo->table))
		printf("%6ld philo: %d has taken the first fork [%d]\n",
			elapsed, philo->id,
			philo->first_fork->fork_id);
	if (status == TAKEN_SECOND_FORK && !end_sim(philo->table))
		printf("%6ld philo: %d has taken the second fork [%d]\n",
			elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (status == EATING && !end_sim(philo->table))
		printf("%6ld philo: %d is eating | meal counter: %ld\n",
			elapsed, philo->id,
			philo->meal_counter);
	else if (status == SLEEPING && !end_sim(philo->table))
		printf("%6ld philo: %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !end_sim(philo->table))
		printf("%6ld philo: %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%6ld philo: %d died\n", elapsed, philo->id);
}

void	print_status(t_philo *philo, t_status op, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_sim;
	if (philo->is_full)
		return ;
	mutex_handler(&philo->table->print_mtx, LOCK);
	if (debug)
		write_debug(op, philo, elapsed);
	else
	{
		if ((op == TAKEN_FIRST_FORK || op == TAKEN_SECOND_FORK)
			&& !end_sim(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (op == EATING && !end_sim(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (op == SLEEPING && !end_sim(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (op == THINKING && !end_sim(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (op == DIED)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	mutex_handler(&philo->table->print_mtx, UNLOCK);
}

void	exit_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}
