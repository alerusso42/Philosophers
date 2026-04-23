/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:01:33 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:34 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	lonely_boy(t_philo *philo)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (clear(philo->table), exit(1));
	if (pid == 0)
	{
		philo->table->start_program = getcorrecttime();
		philo->last_dinner_time = philo->table->start_program;
		write_status(FORK, philo);
		ft_wait(philo->table->t_death);
		write_status(FORK, philo);
	}
	waitpid(pid, NULL, 0);
}

int	main(int arc, char **argv)
{
	t_table	table;

	if (arc != 5 && arc != 6)
		return (printf("WRONG NUMBER OF ARGUMENTS!!\n"), 1);
	if (parsing(argv) == 0 || ft_atol(argv[1]) == 0)
		return (printf("NOT CORRECT ARGUMENT, PLEASE TRY AGAIN!!\n"), 1);
	table = (t_table){0};
	table.n_philo = ft_atol(argv[1]);
	table.t_death = ft_atol(argv[2]) * 1e3;
	table.t_eat = ft_atol(argv[3]) * 1e3;
	table.t_sleep = ft_atol(argv[4]) * 1e3;
	if (arc == 6)
		table.max_dinner = ft_atol(argv[5]);
	else
		table.max_dinner = -1;
	init_table(&table);
	if (table.max_dinner == 0)
		return (0);
	if (table.n_philo == 1)
		return (lonely_boy(&table.philo[0]), 0);
	marchinator(&table);
	clear(&table);
}
