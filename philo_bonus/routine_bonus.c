/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:01:56 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	philo->table->guardian = malloc(sizeof(pthread_t));
	philo->last_dinner_time = philo->table->start_program;
	pthread_create(philo->table->guardian, NULL, death_guardian, philo);
	pthread_detach(*philo->table->guardian);
	while (get_bool(&philo->deadlock, &philo->is_dead) == false)
	{
		ft_wait(100);
		if (eat_and_sleep(philo) == FULL)
		{
			ft_wait(50);
			free(philo->table->guardian);
			clear(philo->table);
			exit(0);
		}
		if (get_bool(&philo->deadlock, &philo->is_dead) == false)
			think(philo);
		else
			break ;
	}
	free(philo->table->guardian);
	clear(philo->table);
	exit(69);
}

void		wait_everyone(t_table *table);

void	marchinator(t_table *table)
{
	int			i;
	pthread_t	thread_id;

	i = 0;
	table->start_program = getcorrecttime();
	while (i < table->n_philo)
	{
		table->pid_array[i] = fork();
		if (table->pid_array[i] == -1)
			return (clear(table), exit(1));
		if (table->pid_array[i] == 0)
			routine(&table->philo[i]);
		++i;
		ft_wait(10);
	}
	table->pid_array[i] = 0;
	pthread_create(&thread_id, NULL, jack_the_reaper, (void *)table);
	wait_everyone(table);
	sem_post(table->death_sem);
	pthread_join(thread_id, NULL);
}

void	wait_everyone(t_table *table)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (table->pid_array[i] && (waitpid(-1, &status, WUNTRACED) != -1))
	{
		if (status / 256 == 69)
		{
			while (i < table->n_philo)
			{
				mutex_handle(&table->mutex, LOCK);
				if (table->pid_array[i])
					kill(table->pid_array[i], SIGKILL);
				mutex_handle(&table->mutex, UNLOCK);
				++i;
			}
			break ;
		}
		mutex_handle(&table->mutex, LOCK);
		table->pid_array[i] = 0;
		mutex_handle(&table->mutex, UNLOCK);
		++i;
	}
}
