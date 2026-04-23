/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:01:22 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eat_and_sleep(t_philo *philo)
{
	sem_wait(philo->table->fork_sem);
	write_status(FORK, philo);
	sem_wait(philo->table->fork_sem);
	write_status(FORK, philo);
	write_status(EATING, philo);
	ft_wait(philo->table->t_eat);
	sem_post(philo->table->fork_sem);
	sem_post(philo->table->fork_sem);
	philo->meal_counter++;
	if (philo->meal_counter == philo->table->max_dinner)
		return (set_bool(&philo->deadlock, &philo->full, true), FULL);
	set_long(&philo->table->mutex, &philo->last_dinner_time, \
	getcorrecttime());
	write_status(SLEEPING, philo);
	ft_wait(philo->table->t_sleep);
	return (0);
}

void	think(t_philo *philo)
{
	long	t_think;

	t_think = 0;
	if (philo->table->n_philo % 2)
		t_think = (philo->table->t_eat * 2) - philo->table->t_sleep;
	else if (philo->table->n_philo % 2 == 0 && philo->table->t_eat > \
	philo->table->t_sleep)
		t_think = philo->table->t_eat - philo->table->t_sleep;
	if (t_think != 0)
	{
		write_status(THINKING, philo);
		ft_wait(t_think);
	}
}
