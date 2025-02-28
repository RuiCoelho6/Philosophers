/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:15:06 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/28 16:05:58 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* 
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_of_meals;
	long	start_sim;
	bool	end_sim;
	t_philo	*philos;
	t_fork	*forks;
 */
void	init_table(t_table *table)
{
	table->philo_nbr ;
	init_table(&table);
}

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
