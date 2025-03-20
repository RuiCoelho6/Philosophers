/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:05:48 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/20 13:21:48 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_bool_mtx(t_mtx *mtx, bool *var, bool value)
{
	mutex_handler(mtx, LOCK);
	*var = value;
	mutex_handler(mtx, UNLOCK);
}

void	set_int_mtx(t_mtx *mtx, int *var, int value)
{
	mutex_handler(mtx, LOCK);
	*var = value;
	mutex_handler(mtx, UNLOCK);
}

void	set_long_mtx(t_mtx *mtx, long *var, long value)
{
	mutex_handler(mtx, LOCK);
	*var = value;
	mutex_handler(mtx, UNLOCK);
}

void	increase_long_mtx(t_mtx *mtx, long *value)
{
	mutex_handler(mtx, LOCK);
	(*value)++;
	mutex_handler(mtx, UNLOCK);
}
