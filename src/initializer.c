/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:27:26 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/05 14:17:26 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_fork_array(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->forks[i].fork_id = i;
		mutex_handler(&table->forks[i].fork, INIT);
	}
}

/* 
 * Even/Odd fork assignments
 */
void	start_getting_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[position];
		philo->right_fork = &forks[(position + philo_nbr + 1) % philo_nbr];
	}
	philo->right_fork = &forks[position];
	philo->left_fork = &forks[(position + philo_nbr + 1) % philo_nbr];
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
		philo->last_meal_timer = 0;
		philo->table = table;
		start_getting_forks(philo, table->forks, i);
	}
}

void	init_table(t_table *table)
{
	table->end_sim = false;
	table->philos = malloc(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		exit_error("Philos malloc failed\n");
	table->forks = malloc(table->philo_nbr * sizeof(t_fork));
	if (table->forks == NULL)
		exit_error("Forks malloc failed\n");
	mutex_handler(&table->table_mtx, INIT);
	init_fork_array(table);
	init_philo_array(table);
}
