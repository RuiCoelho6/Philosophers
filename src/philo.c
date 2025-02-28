/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:15:06 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/28 15:24:05 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* 
 *  ./philo 5 800 200 200 [5]
 *  5 : number of philosophers
 *  800 : time to die
 *  200 : time to eat
 *  200 : time to sleep
 *  5 : maximum number of meals (optional)
 */
int	main(int ac, char **av)
{
	t_table table;

	if (!(ac == 5 || ac == 6))
		exit_error("Error: Input should be like\n"
			"./philo 5 800 200 200 [5]\n");
	check_and_parse(&table, av);
	return (0);
}
