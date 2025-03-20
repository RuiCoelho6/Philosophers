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
	long	threads_running;
	pthread_t	monitor;
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
void	increase_long_mtx(t_mtx *mtx, long *value);

/**
 * get_[type of data]_mtx: Locks a mutex, retrieves the value of the specified variable and unlocks the mutex.
 * 
 * @mtx: Pointer to the mtx to handle.
 * @var: Variable to retrieve.
 */
bool	get_bool_mtx(t_mtx *mtx, bool *var);
int		get_int_mtx(t_mtx *mtx, int *var);
long	get_long_mtx(t_mtx *mtx, long *var);
bool	end_sim(t_table *table);

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

void	think(t_philo *philo, bool pre);

void	desynch_philos(t_philo *philo);

void	*monitor_dinner(void *data);

void	wait_all_threads(t_table *table);

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr);

void	print_status(t_philo *philo, t_status op, bool debug);

void	start_simulation(t_table *table);

#endif

#include "../philo.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

long	ft_atol(char *str)
{
	long	result;
	int		sign;

	if (!str || *str == '\0')
		exit_error("Input is empty");
	result = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-' && sign == 1)
			sign = -1;
		else if (*str == '-' && sign == -1)
			sign = 1;
		str++;
	}
	if (!is_digit(*str))
		exit_error("Only numbers are allowed\n");
	if (sign == -1)
		exit_error("Negative number are not allowed\n");
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			exit_error("Number bigger than INT_MAX\n");
		str++;
	}
	return (result * sign);
}

/*
 *  Convert time from miliseconds (given by the user)
 *  to microseconds to use in USLEEP function
 * 
 *  Check if timestamp is larger than the minimum allowed
*/
void	check_and_parse(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);

	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		exit_error("Timestamps must be larger than 60ms\n");
	if (av[5])
		table->limit_of_meals = ft_atol(av[5]);
	else
		table->limit_of_meals = -1;
}

#include "../philo.h"

/* 
 * Even/Odd fork assignments
 */
static void	start_getting_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}
}

/* 	int			id;
	pthread_t	thread_id;
	long		meal_counter;
	bool		is_full;
	long		last_meal_timer;
	t_fork		right_fork;
	t_fork		left_fork;
	t_table		*table;
 */
static void	init_philo_array(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->is_full = false;
		philo->meal_counter = 0;
		philo->table = table;
		mutex_handler(&philo->philo_mtx, INIT);
		start_getting_forks(philo, table->forks, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready = false;
	table->threads_running = 0;
	table->philos = malloc(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		exit_error("Philos malloc failed\n");
	mutex_handler(&table->table_mtx, INIT);
	mutex_handler(&table->print_mtx, INIT);
	table->forks = malloc(table->philo_nbr * sizeof(t_fork));
	if (table->forks == NULL)
		exit_error("Forks malloc failed\n");
	while(++i < table->philo_nbr)
	{
		mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	init_philo_array(table);
}


void	wait_all_threads(t_table *table)
{
	while(!get_bool_mtx(&table->table_mtx, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handler(mtx, LOCK);
	if(*threads == philo_nbr)
		ret = true;
	mutex_handler(mtx, UNLOCK);
	return (ret);
}

void	write_debug(t_status status, t_philo *philo, long elapsed)
{
	if(status == TAKEN_FIRST_FORK && !end_sim(philo->table))
		printf("%6ld philo: %d has taken the first fork [%d]\n", elapsed, philo->id,
			philo->first_fork->fork_id);
	if(status == TAKEN_SECOND_FORK && !end_sim(philo->table))
		printf("%6ld philo: %d has taken the second fork [%d]\n", elapsed, philo->id,
			philo->second_fork->fork_id);
	else if(status == EATING && !end_sim(philo->table))
		printf("%6ld philo: %d is eating | meal counter: %ld\n", elapsed, philo->id,
			philo->meal_counter);
	else if(status == SLEEPING && !end_sim(philo->table))
		printf("%6ld philo: %d is sleeping\n", elapsed, philo->id);
	else if(status == THINKING && !end_sim(philo->table))
		printf("%6ld philo: %d is thinking\n", elapsed, philo->id);
	else if(status == DIED)
		printf("%6ld philo: %d died\n", elapsed, philo->id);
}

void	print_status(t_philo *philo, t_status op, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_sim;
	if(philo->is_full)
		return ;
	mutex_handler(&philo->table->print_mtx, LOCK);
	if(debug)
		write_debug(op, philo, elapsed);
	else
	{
		if((op == TAKEN_FIRST_FORK || op == TAKEN_SECOND_FORK)
			&& !end_sim(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if(op == EATING && !end_sim(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if(op == SLEEPING && !end_sim(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if(op == THINKING && !end_sim(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if(op == DIED)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	mutex_handler(&philo->table->print_mtx, UNLOCK);
}

void	exit_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}

void	think(t_philo *philo, bool pre)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre)
		print_status(philo, THINKING, DEBUG_MODE);
	if(philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if(t_think < 0)
		t_think = 0;
	my_usleep(t_think * 0.42, philo->table);
}

void	desynch_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
		my_usleep(30000, philo->table);
	else
	{
		if(philo->id % 2)
			think(philo, true);
	}
}

void	my_usleep(long usec, t_table *table)
{
	long	start_sim_time;
	long	elapsed_time;
	long	remaining_time;

	start_sim_time = get_time(MICROSECOND);
	while(get_time(MICROSECOND) - start_sim_time < usec)
	{
		if(end_sim(table))
			break ;
		elapsed_time = get_time(MICROSECOND) - start_sim_time;
		remaining_time = usec - elapsed_time;
		if(remaining_time > 1000)
			usleep(remaining_time / 2);
		else
			while(get_time(MICROSECOND) - start_sim_time < usec)
				;
	}
}

#include "../philo.h"

void	check_mutex_error(int status, t_op operation)
{
	if (status == 0)
		return ;
	if (status == EINVAL
		&& (operation == LOCK || operation == UNLOCK))
		exit_error("The value specified by mutex is invalid\n");
	else if(status == EINVAL && operation == INIT)
		exit_error("The value specified by attr is invalid\n");
	else if(status == EDEADLK)
		exit_error("A deadlock would occur if the thread blocked "
			"waiting for mutex\n");
	else if(status == EPERM)
		exit_error("The current thread does not hold a lock on mutex\n");
	else if(status == ENOMEM)
		exit_error("The process cannot allocate enough memory to "
			"create another mutex");
	else if(status == EBUSY)
		exit_error("Mutex is locked\n");
	return ;
}

void	mutex_handler(t_mtx *mtx, t_op operation)
{
	if (operation == LOCK)
		check_mutex_error(pthread_mutex_lock(mtx), operation);
	else if (operation == UNLOCK)
		check_mutex_error(pthread_mutex_unlock(mtx), operation);
	else if (operation == INIT)
		check_mutex_error(pthread_mutex_init(mtx, NULL), operation);
	else if (operation == DESTROY)
		check_mutex_error(pthread_mutex_destroy(mtx), operation);
	else
		exit_error("Invalid operation for mutex handler\n");
}

void	check_thread_error(int status, t_op operation)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		exit_error("No resources to create another thread\n");
	else if (status == EPERM)
		exit_error("The caller does not have appropriate permission\n");
	else if (status == EINVAL && operation == CREATE)
		exit_error("The value specified by attr in invalid\n");
	else if (status == EINVAL
		&& (operation == JOIN || operation == DETACH))
		exit_error("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		exit_error("No thread could be found corresponding to that "
			"specified by the given thread ID\n");
	else if (status == EDEADLK)
		exit_error("A deadlock was detected or the value of "
			"thread specifies the calling thread\n");
	return ;
}

void	thread_handler(pthread_t *thread, void *(*foo)(void *),
	void *data, t_op operation)
{
	if (operation == CREATE)
		check_thread_error(pthread_create(thread, NULL, foo, data),
			operation);
	else if (operation == JOIN)
		check_thread_error(pthread_join(*thread, NULL), operation);
	else if (operation == DETACH)
		check_thread_error(pthread_detach(*thread), operation);
	else
		exit_error("Invalid operation for thread handler\n");
	return ;
}

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

#include "../philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_die;

	if (get_bool_mtx(&philo->philo_mtx, &philo->is_full))
		return (false);
	elapsed = get_time(MILLISECOND) - get_long_mtx(&philo->philo_mtx, &philo->last_meal_timer);
	t_die = philo->table->time_to_die / 1000;
	if (elapsed > t_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	i = -1;
	table = (t_table *) data;
	while (!all_threads_running(&table->table_mtx, &table->threads_running,
				table->philo_nbr))
		;
	while(!end_sim(table))
	{
		i = -1;
		while(++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i))
			{
				set_bool_mtx(&table->table_mtx, &table->end_sim, true);
				print_status(table->philos + i, DIED, DEBUG_MODE);
				break ;
			}
		}
	}
	return(NULL);
}

#include "../philo.h"

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
		init_table(&table);
		start_simulation(&table);
		clean(&table);
	}
	return (0);
}
