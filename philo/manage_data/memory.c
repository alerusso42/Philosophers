/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:18:38 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 10:55:24 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int	alloc_memory(t_data *data, long long int philo_num)
{
	int	num;
	int	i;

	num = (int)philo_num;
	data->philo = (t_philo *)ft_calloc(num + 1, sizeof(t_philo));
	if (!data->philo)
		return (ER_MALLOC);
	i = -1;
	while (++i != num)
		data->philo[i] = (t_philo){0};
	num += 1;
	data->forks = (pthread_mutex_t *)ft_calloc(num + 1, \
		sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ER_MALLOC);
	data->generic_mutex = (pthread_mutex_t *)ft_calloc(num + 1, \
		sizeof(pthread_mutex_t));
	if (!data->generic_mutex)
		return (ER_MALLOC);
	data->threads = (pthread_t *) \
	ft_calloc(num, sizeof(pthread_t));
	if (!data->threads)
		return (ER_MALLOC);
	return (0);
}

void	reset_memory(t_data	*data)
{
	if (!data)
		return ;
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->generic_mutex)
	{
		free(data->generic_mutex);
		data->generic_mutex = NULL;
	}
	if (data->threads)
	{
		free(data->threads);
		data->threads = NULL;
	}
}
