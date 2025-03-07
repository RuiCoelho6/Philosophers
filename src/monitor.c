/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:36:40 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/07 14:09:21 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_die;

	if (get_bool_mtx(&philo->philo_mtx, &philo->is_full))
		return(false);
	elapsed = get_time(MILLISECOND) - get_long_mtx(&philo->philo_mtx, &philo->last_meal_timer);
	t_die = philo->table->time_to_die / 1000 ;
	if (elapsed > t_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	bool	end_sim;
	int		i;

	i = -1;
	table = (t_table *) data;
	end_sim = get_bool_mtx(&table->table_mtx, &table->end_sim);
	while (!all_threads_running(&table->table_mtx, &table->threads_running,
				table->philo_nbr))
		;
	while(!end_sim)
	{
		i = -1;
		while(++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i) && !end_sim)
			{
				set_bool_mtx(&table->table_mtx, &table->end_sim, true);
				print_status(table->philos + i, DIED, DEBUG_MODE);
			}
		}
		end_sim = get_bool_mtx(&table->table_mtx, &table->end_sim);
	}
	return(NULL);
}
