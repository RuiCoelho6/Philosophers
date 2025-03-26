/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:40:35 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/26 15:17:35 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	get_bool_mtx(t_mtx *mtx, bool *var)
{
	bool	ret;

	mutex_handler(mtx, "lock");
	ret = *var;
	mutex_handler(mtx, "unlock");
	return (ret);
}

int	get_int_mtx(t_mtx *mtx, int *var)
{
	int	ret;

	mutex_handler(mtx, "lock");
	ret = *var;
	mutex_handler(mtx, "unlock");
	return (ret);
}

long	get_long_mtx(t_mtx *mtx, long *var)
{
	long	ret;

	mutex_handler(mtx, "lock");
	ret = *var;
	mutex_handler(mtx, "unlock");
	return (ret);
}

long	get_time(char *operation)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_error("gettimeofday failed");
	if (ft_strcmp(operation, "millisecond") == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (ft_strcmp(operation, "microsecond") == 0)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		exit_error("Invalid operation for gettimeofday");
	return (-1);
}

bool	end_sim(t_table *table)
{
	return (get_bool_mtx(&table->table_mtx, &table->end_sim));
}
