/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_eat_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:53:50 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/17 12:44:43 by rpires-c         ###   ########.fr       */
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
