/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:01:27 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:28 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	mutex_handle(pthread_mutex_t *fork, int command)
{
	if (command == LOCK)
		return (pthread_mutex_lock(fork));
	else if (command == UNLOCK)
		return (pthread_mutex_unlock(fork));
	return (53550);
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	temp;

	mutex_handle(mutex, LOCK);
	temp = *value;
	mutex_handle(mutex, UNLOCK);
	return (temp);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	temp;

	mutex_handle(mutex, LOCK);
	temp = *value;
	mutex_handle(mutex, UNLOCK);
	return (temp);
}
