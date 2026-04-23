/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:57:48 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 10:52:31 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int	create_philos(t_data *data);
int	init_mutex(t_data *data);

//here starts the program timer
int	start_threads(t_data *data)
{
	int		err;

	err = 0;
	get_current_time(&data->time, NULL);
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (ER_MUTEX_INIT);
	err = create_philos(data);
	if (err != 0)
		return (err);
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	if (init_mutex(data) != 0)
		return (ER_MUTEX_INIT);
	if (pthread_create(&data->monitor, NULL, monitor, (void *)data) != 0)
		return (ER_PTHREAD_CREATE);
	i = 0;
	while (i != data->philo_num)
	{
		data->philo[i].time = data->time;
		if (pthread_create(&data->threads[i], NULL, routine, \
			(void *)&data->philo[i]) != 0)
			return (ER_PTHREAD_CREATE);
		ft_wait(100);
		++i;
	}
	return (0);
}

//TRICK
//after mutex are initialized, the last philo forks are swapped
int	init_mutex(t_data *data)
{
	int				i;
	pthread_mutex_t	*temp;

	i = 0;
	while (i != data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ER_MUTEX_INIT);
		if (pthread_mutex_init(&data->generic_mutex[i], NULL) != 0)
			return (ER_MUTEX_INIT);
		++i;
	}
	i = 0;
	while (i != data->philo_num)
	{
		data->philo[i].write_mutex = &data->write_mutex;
		data->philo[i].generic_mutex = &data->generic_mutex[i];
		++i;
	}
	--i;
	temp = data->philo[i].philo_fork;
	data->philo[i].philo_fork = data->philo[i].right_fork;
	data->philo[i].right_fork = temp;
	return (0);
}

int	quit_threads(t_data	*data)
{
	int		i;

	i = 0;
	pthread_join(data->monitor, NULL);
	while (i != data->philo_num)
	{
		pthread_join(data->threads[i], NULL);
		++i;
	}
	i = 0;
	while (i != data->philo_num)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			p_color(RED, "\nTrying to destroy a lock mutex\n");
		}
		pthread_mutex_destroy(&data->generic_mutex[i]);
		++i;
	}
	pthread_mutex_destroy(&data->write_mutex);
	return (0);
}
