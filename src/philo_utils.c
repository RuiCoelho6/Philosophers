/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:18:44 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/05 20:34:19 by rpires-c         ###   ########.fr       */
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
		if(get_bool_mtx(&table->table_mtx, table->end_sim))
			break ;
		elapsed_time = get_time(MICROSECOND) - start_sim_time;
		remaining_time = usec - elapsed_time;
		if(remaining_time > 1000)
			usleep(usec / 2);
		else
			while(get_time(MICROSECOND) - start_sim_time < usec)
				;
	}
}

void	exit_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}
