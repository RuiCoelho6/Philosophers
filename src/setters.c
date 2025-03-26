/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:05:48 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/26 15:17:04 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_bool_mtx(t_mtx *mtx, bool *var, bool value)
{
	mutex_handler(mtx, "lock");
	*var = value;
	mutex_handler(mtx, "unlock");
}

void	set_int_mtx(t_mtx *mtx, int *var, int value)
{
	mutex_handler(mtx, "lock");
	*var = value;
	mutex_handler(mtx, "unlock");
}

void	set_long_mtx(t_mtx *mtx, long *var, long value)
{
	mutex_handler(mtx, "lock");
	*var = value;
	mutex_handler(mtx, "unlock");
}

void	increase_long_mtx(t_mtx *mtx, long *value)
{
	mutex_handler(mtx, "lock");
	(*value)++;
	mutex_handler(mtx, "unlock");
}
