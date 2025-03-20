/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_eat_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:53:50 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/20 11:53:58 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philo *philo, bool pre)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre)
		print_status(philo, THINKING, DEBUG_MODE);
	if(philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if(t_think < 0)
		t_think = 0;
	my_usleep(t_think, philo->table);
}

void	desynch_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
		my_usleep(30000, philo->table);
	else
	{
		if(philo->id % 2)
			think(philo, true);
	}
}

void	my_usleep(long usec, t_table *table)
{
	long	start_sim_time;
	long	elapsed_time;
	long	remaining_time;

	start_sim_time = get_time(MICROSECOND);
	while(get_time(MICROSECOND) - start_sim_time < usec)
	{
		if(end_sim(table))
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
