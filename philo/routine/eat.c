/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:57 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 10:40:42 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_fork);
	p_state(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	p_state(philo, FORK);
	p_state(philo, EAT);
	pthread_mutex_lock(philo->generic_mutex);
	get_current_time(&philo->time, &philo->last_meal_time);
	pthread_mutex_unlock(philo->generic_mutex);
	ft_wait(philo->time_to_eat * MSECONDS);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->philo_fork);
	return (0);
}
