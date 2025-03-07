/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:27:26 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/07 12:41:58 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* 
 * Even/Odd fork assignments
 */
void	start_getting_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}

/* 	int			id;
	pthread_t	thread_id;
	long		meal_counter;
	bool		is_full;
	long		last_meal_timer;
	t_fork		right_fork;
	t_fork		left_fork;
	t_table		*table;
 */
void	init_philo_array(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->is_full = false;
		philo->meal_counter = 0;
		philo->table = table;
		mutex_handler(&philo->philo_mtx, INIT);
		start_getting_forks(philo, table->forks, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready = false;
	table->threads_running = 0;
	table->philos = malloc(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		exit_error("Philos malloc failed\n");
	table->forks = malloc(table->philo_nbr * sizeof(t_fork));
	if (table->forks == NULL)
		exit_error("Forks malloc failed\n");
	while(++i < table->philo_nbr)
	{
		mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	mutex_handler(&table->table_mtx, INIT);
	mutex_handler(&table->print_mtx, INIT);
	init_philo_array(table);
}
