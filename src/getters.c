/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:40:35 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/17 12:24:16 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	get_bool_mtx(t_mtx *mtx, bool *var)
{
	bool	ret;

	mutex_handler(mtx, LOCK);
	ret = *var;
	mutex_handler(mtx, UNLOCK);
	return (ret);
}

int	get_int_mtx(t_mtx *mtx, int *var)
{
	int	ret;

	mutex_handler(mtx, LOCK);
	ret = *var;
	mutex_handler(mtx, UNLOCK);
	return (ret);
}

long	get_long_mtx(t_mtx *mtx, long *var)
{
	long	ret;

	mutex_handler(mtx, LOCK);
	ret = *var;
	mutex_handler(mtx, UNLOCK);
	return (ret);
}

long	get_time(t_time operation)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_error("gettimeofday failed");
	if (operation == MILLISECOND)
		return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (operation == MICROSECOND)
		return((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		exit_error("Invalid operation for gettimeofday");
	return (-1);
}

bool	end_sim(t_table *table)
{
	return (get_bool_mtx(&table->table_mtx, &table->end_sim));
}
