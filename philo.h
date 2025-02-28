/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:51:38 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/28 15:22:12 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>

typedef struct s_philo t_philo;
typedef struct s_fork t_fork;
typedef struct s_table t_table;
typedef pthread_mutex_t t_mtx;

/* 
 *  philo_nbr : number of philosophers
 *  time_to_die : time to die for each philosopher
 *  time_to_eat : time to eat for each philosopher
 *  time_to_sleep : time to sleep for each philosopher
 *  limits_of_meals : number of maximum meals for each philosopher
 *                    is -1 when not specified since it's optional
 *  start_sim: timestamp of the beginning of the simulation
 *  end_sim : true if the simulation should end
 *  philo_nbr : array of pointers to the philosophers
 *  forks : array of pointers to the forks
 */
typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_of_meals;
	long	start_sim;
	bool	end_sim;
	t_philo	*philos;
	t_fork	*forks;
}	t_table;

/* 
 *  fork_id : id of the fork
 *  fork : mutex associated with the fork
 */
typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

/* 
 *  id : id of the philosopher
 *  thread_id : id of the thread associated with the philosopher
 *  meal_counter : number of meals the philosopher has eaten
 *  is_full : true if the philosopher has eaten the maximum number of meals
 *  last_meal_timer : timestamp of the last meal
 *  right_fork : mutex associated with the right fork
 *  left_fork : mutex associated with the left fork
 *  table : pointer control structure
 */
typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	long		meal_counter;
	bool		is_full;
	long		last_meal_timer;
	t_fork		right_fork;
	t_fork		left_fork;
	t_table		*table;
}	t_philo;

/* 
 *  exit_error : function to print an error message and exit the program
 *  This function does not return
 *  @param message : message to print
*/
void	exit_error(char *message);

void	check_and_parse(t_table *table, char **av);

#endif
