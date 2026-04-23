/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:25:11 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 10:41:19 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

static void	consider_empty_args(int *argc, char *argv[]);
static void	convert_argv(t_data *data, char *argv[]);
static int	check_input_number(t_data *data);
static void	give_philosophers_informations(t_data *data);

int	parsing(t_data *data, int argc, char *argv[])
{
	long long int	philo_num;
	int				err;

	consider_empty_args(&argc, argv);
	if (argc < 5 || argc > 6)
		return (ER_BAD_ARGC);
	philo_num = ft_atoi(argv[1]);
	err = (philo_num < 1) * ER_NEGATIVE;
	err += (philo_num > INT_MAX) * ER_INVALID_ARG;
	if (err)
		return (err);
	if (alloc_memory(data, philo_num) != 0)
		return (ER_MALLOC);
	data->philo_num = philo_num;
	convert_argv(data, argv);
	err = check_input_number(data);
	if (err)
		return (err);
	give_philosophers_informations(data);
	return (0);
}

/*
	Decrease argc for every *argv == "" (in other words, made by only one '\0')
	and erase empty *argv.

	The args->* ./philo "77" "" "42" "" "" NULL * become
				./philo "77" "42" NULL
	
	argc goes from 6 to 3.
	
	1)	Decrease argc by one only if *argv[index] is equal to terminator;
	2)	While the previous argument is empty, put back the index;
	3)	Make the furthest empty *argv equal to the current index position.
	4)	Out of the loop, move NULL to the furthest empty *argv. 
*/
static void	consider_empty_args(int *argc, char *argv[])
{
	int	index;
	int	temp;

	index = 1;
	while (argv[index])
	{
		argc -= (*argv[index] == '\0');
		temp = index;
		while (*argv[index - 1] == '\0')
			--index;
		argv[temp] = argv[index];
		index = temp;
		++index;
	}
	temp = index;
	while (*argv[index - 1] == '\0')
		--index;
	argv[temp] = argv[index];
}

static void	convert_argv(t_data *data, char *argv[])
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] == NULL)
		data->number_of_times_each_philosopher_must_eat = -1;
	else
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

static int	check_input_number(t_data *data)
{
	int	err;

	err = 0;
	err += (data->time_to_die < 0) * 10;
	err += data->time_to_die == LLONG_MAX;
	err += (data->time_to_eat < 0) * 10;
	err += data->time_to_eat == LLONG_MAX;
	err += (data->time_to_sleep < 0) * 10;
	err += data->time_to_sleep == LLONG_MAX;
	err += (data->number_of_times_each_philosopher_must_eat < -1) * 10;
	err += data->number_of_times_each_philosopher_must_eat == LLONG_MAX;
	if (err >= 10)
		return (ER_NEGATIVE);
	else if (err % 10)
		return (ER_INVALID_ARG);
	return (0);
}

static void	give_philosophers_informations(t_data *data)
{
	int	i;

	i = -1;
	while (++i != (int)data->philo_num)
	{
		data->philo[i].philo_num = data->philo_num;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].number_of_times_each_philosopher_must_eat = \
		(int)data->number_of_times_each_philosopher_must_eat;
		data->philo[i].id = i;
		data->philo[i].philo_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[i + 1];
		data->philo[i].last_philo = false;
		data->philo[i].someone_died = &data->someone_died;
	}
	i -= 1;
	data->philo[i].last_philo = true;
	data->philo[i].right_fork = &data->forks[0];
	if (data->philo_num == 2)
	{
		data->philo[0].right_fork = &data->forks[1];
		data->philo[1].right_fork = &data->forks[0];
	}
}
