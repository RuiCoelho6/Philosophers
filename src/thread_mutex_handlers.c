/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:05:33 by rpires-c          #+#    #+#             */
/*   Updated: 2025/03/26 15:40:11 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	check_mutex_error(int status, char *operation)
{
	if (status == 0)
		return ;
	if (status == EINVAL
		&& (ft_strcmp(operation, "lock") == 0
			|| ft_strcmp(operation, "unlock") == 0))
		exit_error("The value specified by mutex is invalid\n");
	else if (status == EINVAL && ft_strcmp(operation, "init") == 0)
		exit_error("The value specified by attr is invalid\n");
	else if (status == EDEADLK)
		exit_error("A deadlock would occur if the thread blocked "
			"waiting for mutex\n");
	else if (status == EPERM)
		exit_error("The current thread does not hold a lock on mutex\n");
	else if (status == ENOMEM)
		exit_error("The process cannot allocate enough memory to "
			"create another mutex");
	else if (status == EBUSY)
		exit_error("Mutex is locked\n");
	return ;
}

void	mutex_handler(t_mtx *mtx, char *operation)
{
	if (ft_strcmp(operation, "lock") == 0)
		check_mutex_error(pthread_mutex_lock(mtx), operation);
	else if (ft_strcmp(operation, "unlock") == 0)
		check_mutex_error(pthread_mutex_unlock(mtx), operation);
	else if (ft_strcmp(operation, "init") == 0)
		check_mutex_error(pthread_mutex_init(mtx, NULL), operation);
	else if (ft_strcmp(operation, "destroy") == 0)
		check_mutex_error(pthread_mutex_destroy(mtx), operation);
	else
		exit_error("Invalid operation for mutex handler\n");
}

void	check_thread_error(int status, char *operation)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		exit_error("No resources to create another thread\n");
	else if (status == EPERM)
		exit_error("The caller does not have appropriate permission\n");
	else if (status == EINVAL && ft_strcmp(operation, "create") == 0)
		exit_error("The value specified by attr in invalid\n");
	else if (status == EINVAL
		&& (ft_strcmp(operation, "join") == 0
			|| ft_strcmp(operation, "detach") == 0))
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
	void *data, char *operation)
{
	if (ft_strcmp(operation, "create") == 0)
		check_thread_error(pthread_create(thread, NULL, foo, data),
			operation);
	else if (ft_strcmp(operation, "join") == 0)
		check_thread_error(pthread_join(*thread, NULL), operation);
	else if (ft_strcmp(operation, "detach") == 0)
		check_thread_error(pthread_detach(*thread), operation);
	else
		exit_error("Invalid operation for thread handler\n");
	return ;
}
