/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:17:48 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/05 19:38:41 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	dinner_simulation(void *data)
{
	t_philo	*philo;
	bool	end_sim;

	end_sim = get_bool_mtx(&philo->table->table_mtx, &philo->table->end_sim);
	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!end_sim)
	{
		if(philo->is_full)
			break ;
		end_sim = get_bool_mtx(&philo->table->table_mtx, &philo->table->end_sim);
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	if (table->limit_of_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;
	else
	{
		while(++i < table->philo_nbr)
			thread_handler(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE);
	}
	table->start_sim = get_time(MILLISECOND);
	set_bool_mtx(&table->table_mtx, &table->all_threads_ready, true);
	i = -1;
	while(++i < table->philo_nbr)
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
}