/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:02:00 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 11:02:01 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	check(t_philo *philo, long time_eat)
{
	long	time;

	time = getcorrecttime();
	if ((time - time_eat) >= philo->table->t_death / 1e3)
		return (true);
	return (false);
}

void	*jack_the_reaper(void *data)
{
	int		i;
	t_table	*table;

	i = 0;
	table = data;
	sem_wait(table->death_sem);
	while (i < table->n_philo)
	{
		mutex_handle(&table->mutex, LOCK);
		if (table->pid_array[i])
			kill(table->pid_array[i], SIGKILL);
		mutex_handle(&table->mutex, UNLOCK);
		++i;
	}
	return (NULL);
}

void	*death_guardian(void *data)
{
	t_philo	*philo;
	long	time_eat;

	philo = (t_philo *)data;
	while (1)
	{
		ft_wait(10);
		time_eat = get_long(&philo->table->mutex, &philo->last_dinner_time);
		if (check(philo, time_eat))
		{
			set_bool(&philo->deadlock, &philo->is_dead, true);
			sem_wait(philo->table->write_sem);
			printf("%-6ld %-2d died\n", getcorrecttime() - \
				philo->table->start_program, philo->id);
			sem_post(philo->table->death_sem);
			free(philo->table->guardian);
			clear(philo->table);
			break ;
		}
		if (get_bool(&philo->deadlock, &philo->full))
			break ;
	}
	return (NULL);
}
