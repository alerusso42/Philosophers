/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:54:27 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 10:59:49 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

//to avoid unnecessary locks, the data raise safe variable philo->death is set.
int	philo_lives(t_philo *philo)
{
	int	is_alive;

	if (philo->death)
		return (false);
	is_alive = true;
	pthread_mutex_lock(philo->generic_mutex);
	if (philo->state == DEAD)
		is_alive = false;
	pthread_mutex_unlock(philo->generic_mutex);
	if (is_alive == false)
		philo->death = true;
	return (is_alive);
}

//enter here when monitor detects someone should die.
//if someone is full, it does not print anything.
void	kill_everyone(t_data *data, int which, int *everyone_lives)
{
	int		i;
	bool	someone_full;

	i = 0;
	someone_full = false;
	while (i != data->philo_num)
	{
		pthread_mutex_lock(&data->generic_mutex[i]);
		if (data->philo[i].state == FULL)
			someone_full = true;
		data->philo[i].state = DEAD;
		pthread_mutex_unlock(&data->generic_mutex[i]);
		++i;
	}
	data->someone_died = true;
	*everyone_lives = false;
	if (someone_full)
		return ;
	pthread_mutex_lock(&data->write_mutex);
	get_current_time(&data->time, &data->current_time);
	l_printf(M_DEAD, data->current_time / MS, which);
	pthread_mutex_unlock(&data->write_mutex);
}
