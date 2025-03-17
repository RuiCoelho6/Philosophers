/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:17:48 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/17 13:02:52 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	think(t_philo *philo)
{
	print_status(philo, THINKING, DEBUG_MODE);
}

static void	eat(t_philo *philo)
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

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_all_threads(philo->table);
	set_long_mtx(&philo->philo_mtx, &philo->last_meal_timer, get_time(MILLISECOND));
	increase_long_mtx(&philo->table->table_mtx, &philo->table->threads_running);
	print_status(philo, TAKEN_FIRST_FORK, DEBUG_MODE);
	while(!end_sim(philo->table))
		usleep(200);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long_mtx(&philo->philo_mtx, &philo->last_meal_timer,
			get_time(MILLISECOND));
	increase_long_mtx(&philo->table->table_mtx,
		&philo->table->threads_running);
	while (!end_sim(philo->table))
	{
		if(philo->is_full)
			break ;
		eat(philo);
		print_status(philo, SLEEPING, DEBUG_MODE);
		my_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	if (table->limit_of_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		thread_handler(&table->philos[0].thread_id, lone_philo,
			&table->philos[0], CREATE);
	else
	{
		while(++i < table->philo_nbr)
			thread_handler(&table->philos[i].thread_id,
				dinner_simulation, &table->philos[i], CREATE);
	}
	thread_handler(&table->monitor, monitor_dinner, table, CREATE);
	table->start_sim = get_time(MILLISECOND);
	set_bool_mtx(&table->table_mtx, &table->all_threads_ready, true);
	i = -1;
	while(++i < table->philo_nbr)
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool_mtx(&table->table_mtx, &table->end_sim, true);
	thread_handler(&table->monitor, NULL, NULL, JOIN);
}