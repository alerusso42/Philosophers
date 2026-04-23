/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:41:43 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/31 11:54:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/header.h"

static int	other_messages(int error);
static int	other_messages2(int error);

int	error(t_data *data, int error)
{
	reset_memory(data);
	if (error == ER_BAD_ARGC)
	{
		return (fd_printf(2, "Error\nYour program must take the following\
 arguments:\n\
number_of_philosophers time_to_die time_to_eat time_to_sleep\n\
[number_of_times_each_philosopher_must_eat]\n\n\
1) number_of_philosophers: The number of philosophers and forks.\
\n\
2) time_to_die (ms): If a philosopher hasn't eaten within \
time_to_die\n\
ms since their last meal or the start, they die.\n\
3) time_to_eat (ms): Time it takes a philosopher to eat,\
requiring\ntwo forks.\n\
4) time_to_sleep (ms): Time a philosopher spends sleeping.\n\
5) number_of_times_each_philosopher_must_eat (optional): If all\n\
philosophers have eaten at least this many times, the \
simulation\n\
stops. If not specified, it stops when a philosopher dies.\n\n"));
	}
	return (other_messages(error));
}

static int	other_messages(int error)
{
	if (error == ER_MALLOC)
	{
		return (fd_printf(2, "Malloc error (Wtf).\n"));
	}
	else if (error == ER_NEGATIVE)
	{
		return (fd_printf(2, "Arguments must be positive integers\n"));
	}
	else if (error == ER_INVALID_ARG)
	{
		fd_printf(2, "Segmentation fault (core dumped)\n");
		ft_wait(3 * SECONDS);
		fd_printf(2, "EHHHH, VOLEVI!\n");
		ft_wait(2 * SECONDS);
		fd_printf(2, "GUARDA CHE FACCIA, NON SE L'ASPETTAVA!\n");
	}
	else if (error == (ER_GETTIMEOFDAY))
	{
		fd_printf(2, "Gettimeofday error (wtf)\n");
	}
	return (other_messages2(error));
}

static int	other_messages2(int error)
{
	if (error == (ER_USLEEP))
	{
		fd_printf(2, "Usleep error (wtf)\n");
	}
	else if (error == (ER_MUTEX_INIT))
	{
		fd_printf(2, "mutex_init error (wtf)\n");
	}
	else if (error == (ER_PTHREAD_CREATE))
	{
		fd_printf(2, "pthread_create error (wtf)\n");
	}
	return (error);
}
