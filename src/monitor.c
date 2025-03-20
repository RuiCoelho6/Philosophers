/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:36:40 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/20 13:15:39 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_die;

	if (get_bool_mtx(&philo->philo_mtx, &philo->is_full))
		return (false);
	elapsed = get_time(MILLISECOND) - get_long_mtx(&philo->philo_mtx,
			&philo->last_meal_timer);
	t_die = philo->table->time_to_die / 1000;
	if (elapsed > t_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	i = -1;
	table = (t_table *) data;
	while (!all_threads_running(&table->table_mtx, &table->threads_running,
			table->philo_nbr))
		;
	while (!end_sim(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i))
			{
				set_bool_mtx(&table->table_mtx, &table->end_sim, true);
				print_status(table->philos + i, DIED, DEBUG_MODE);
				break ;
			}
		}
	}
	return (NULL);
}
