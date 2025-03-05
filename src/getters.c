/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:40:35 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/05 12:14:56 by rpires-c         ###   ########.fr       */
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
