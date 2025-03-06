/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:51:38 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/06 16:18:25 by rpires-c         ###   ########.fr       */
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
#include <errno.h>

#define DEBUG_MODE 0
/*
 *  Operations for mutex/threads
*/
typedef enum e_op
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_op;

/*
 *  Operations for get_time
*/
typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time;

/*
 *  Operations for writing the status
*/
typedef enum e_status
{
	EATING,
	THINKING,
	SLEEPING,
	TAKEN_FIRST_FORK,
	TAKEN_SECOND_FORK,
	DIED,
}	t_status;

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
	bool	all_threads_ready;
	t_mtx	table_mtx;
	t_mtx	print_mtx;
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
	t_mtx		philo_mtx;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
}	t_philo;

/**
 * exit_error : function to print an error message and exit the program
 * 
 * @message: message to print explaining the error
 * 
 * This function does not return
 */
void	exit_error(char *message);

/**
 * check_and_parse: This function extracts numerical values from the arguments
 *                  and assigns them to the corresponding fields in the `t_table` structure.
 * 
 * @table: Pointer to the structure storing simulation parameters.
 * @av: Array of arguments.
 * 
 * Converts time values from milliseconds to microseconds for use with `usleep()`.
 * Ensures all provided timestamps are larger than the minimum required threshold (60ms).
 * Sets the meal limit if provided, otherwise, defaults to -1 (unlimited meals).
 */
void	check_and_parse(t_table *table, char **av);

/**
 * mutex_handler: Manages mutex operations such as locking, unlocking,
 *                initialization, and destruction.
 * 
 * @mtx: Pointer to the mutex being manipulated.
 * @operation: The mutex operation to be performed (LOCK, UNLOCK, INIT, DESTROY).
 * 
 * Checks for errors using check_mutex_error().
 */
void	mutex_handler(t_mtx *mtx, t_op operation);

/**
 * thread_handler: Manages thread operations such as creation, joining, and detaching.
 * 
 * @thread: Pointer to the thread being managed.
 * @foo: Function pointer to the thread's entry function.
 * @data: Pointer to the data passed to the thread function.
 * @operation: The thread operation to be performed (CREATE, JOIN, DETACH).
 * 
 * Checks for errors using check_thread_error().
 */
void	thread_handler(pthread_t *thread, void *(*foo)(void *),
			void *data, t_op operation);

/**
 * init_table: Initializes the values of the table strutch and assigns the first forks each philosopher.
 * 
 * @table: Pointer to the structure storing simulation parameters.
 */
void	init_table(t_table *table);

/**
 * set_[type of data]_mtx: Locks a mutex, alters the value of the specified variable and unlocks the mutex.
 * 
 * @mtx: Pointer to the mtx to handle.
 * @var: Variable to alter.
 * @value: Value to atribute to the variable.
 */
void	set_bool_mtx(t_mtx *mtx, bool *var, bool value);
void	set_int_mtx(t_mtx *mtx, int *var, int value);
void	set_long_mtx(t_mtx *mtx, long *var, long value);

/**
 * get_[type of data]_mtx: Locks a mutex, retrieves the value of the specified variable and unlocks the mutex.
 * 
 * @mtx: Pointer to the mtx to handle.
 * @var: Variable to retrieve.
 */
bool	get_bool_mtx(t_mtx *mtx, bool *var);
int		get_int_mtx(t_mtx *mtx, int *var);
long	get_long_mtx(t_mtx *mtx, long *var);

/**
 * get_time: retuns elapsed time in seconds, milliseconds or microseconds.
 * 
 * @operation: The gettime operation to be performed (SECOND, MILLISECOND, MICROSECOND).
 */
long	get_time(t_time operation);

/**
 * my_usleep: Custom sleep function that prevents a thread from sleeping longer than necessary.
 * 
 * @usec: The duration to sleep in microseconds.
 * @table: Pointer to the structure storing simulation parameters.
 * 
 * This function ensures a thread sleeps for the specified duration while:
 * - Periodically checking if the simulation has ended to avoid unnecessary loops
 * - Using usleep() for efficiency when the remaining sleep time is significant
 * - Switching to active waiting using a spinlock when the remaining time is less than
 *   1 microsecond to maintain precision without oversleeping.
 */
void	my_usleep(long usec, t_table *table);

void	print_status(t_philo *philo, t_status op, bool debug);

void	eat(t_philo *philo);

void	think(t_philo *philo);

void	start_simulation(t_table *table);

#endif
