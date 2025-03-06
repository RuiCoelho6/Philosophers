/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_eat_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:53:50 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/06 15:51:50 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_usleep(long usec, t_table *table)
{
	long	start_sim_time;
	long	elapsed_time;
	long	remaining_time;

	start_sim_time = get_time(MICROSECOND);
	while(get_time(MICROSECOND) - start_sim_time < usec)
	{
		if(get_bool_mtx(&table->table_mtx, &table->end_sim))
			break ;
		elapsed_time = get_time(MICROSECOND) - start_sim_time;
		remaining_time = usec - elapsed_time;
		if(remaining_time > 1000)
			usleep(remaining_time / 2);
		else
			while(get_time(MICROSECOND) - start_sim_time < usec)
				;
	}
}

void	eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	print_status(philo, TAKEN_FIRST_FORK, DEBUG_MODE);
	mutex_handler(&philo->second_fork->fork, LOCK);
	print_status(philo, TAKEN_SECOND_FORK, DEBUG_MODE);
	set_long_mtx(&philo->philo_mtx, &philo->last_meal_timer, get_time(MILLISECOND));
	philo->meal_counter++;
	print_status(philo, EATING, DEBUG_MODE);
	my_usleep(philo->table->time_to_eat, philo->table);
	if(philo->table->limit_of_meals > 0
		&& philo->meal_counter == philo->table->limit_of_meals)
		set_bool_mtx(&philo->philo_mtx, &philo->is_full, true);
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->second_fork->fork, UNLOCK);
}

void	think(t_philo *philo)
{
	print_status(philo, THINKING, DEBUG_MODE);
}
