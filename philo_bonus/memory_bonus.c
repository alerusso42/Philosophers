/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:01:38 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:39 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	open_sem(t_table *table)
{
	table->fork_sem = sem_open(SEM_NAME, O_CREAT, 0666, table->n_philo);
	if (table->fork_sem == SEM_FAILED)
		return (clear(table), exit(1));
	sem_unlink(SEM_NAME);
	table->write_sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
	if (table->write_sem == SEM_FAILED)
		return (clear(table), exit(1));
	sem_unlink(SEM_NAME);
	table->death_sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
	if (table->death_sem == SEM_FAILED)
		return (clear(table), exit(1));
	sem_unlink(SEM_NAME);
	sem_wait(table->death_sem);
}

void	init_table(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	table->philo = malloc(table->n_philo * (sizeof(t_philo)));
	if (table->philo == NULL)
		return (printf("MALLOC HAS...FAILED?!"), exit(1));
	table->pid_array = malloc((table->n_philo + 1) * (sizeof(pid_t)) + 1);
	if (table->pid_array == NULL)
		return (printf("MALLOC HAS...FAILED?!"), exit(1));
	pthread_mutex_init(&table->mutex, NULL);
	while (i != table->n_philo)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->meal_counter = 0;
		philo->last_dinner_time = 0;
		philo->full = false;
		philo->is_dead = false;
		philo->table = table;
		pthread_mutex_init(&philo->deadlock, NULL);
		i++;
	}
	open_sem(table);
}

void	clear(t_table *table)
{
	int	i;

	if (table->fork_sem)
		sem_close(table->fork_sem);
	if (table->write_sem)
		sem_close(table->write_sem);
	if (table->death_sem)
		sem_close(table->death_sem);
	pthread_mutex_destroy(&table->mutex);
	i = 0;
	while (i != table->n_philo)
	{
		pthread_mutex_destroy(&table->philo[i].deadlock);
		++i;
	}
	free(table->pid_array);
	free(table->philo);
}
