/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:15:06 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/20 13:36:11 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool_mtx(&table->table_mtx, &table->all_threads_ready))
		;
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		mutex_handler(&philo->philo_mtx, DESTROY);
	}
	mutex_handler(&table->print_mtx, DESTROY);
	mutex_handler(&table->table_mtx, DESTROY);
	free(table->forks);
	free(table->philos);
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
	t_table	table;

	if (!(ac == 5 || ac == 6))
		exit_error("Error: Input should be like\n"
			"./philo 5 800 200 200 [5]\n");
	else
	{
		check_and_parse(&table, av);
		if (table.philo_nbr > 200)
			exit_error("");
		init_table(&table);
		start_simulation(&table);
		clean(&table);
	}
	return (0);
}
