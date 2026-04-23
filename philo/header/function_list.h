/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:02:19 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/08 16:49:59 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_LIST_H
# define FUNCTION_LIST_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include "header.h"

//	ROOT DIRECTORY

int				error(t_data *data, int error);

//	MANAGE_DATA

int				alloc_memory(t_data *data, long long int philo_num);
void			reset_memory(t_data *data);
int				start_threads(t_data *data);
int				quit_threads(t_data *data);
int				parsing(t_data *data, int argc, char *argv[]);

//	ROUTINE

void			*routine(void *ptr);
void			*monitor(void *ptr);
int				eat(t_philo *philo);
int				philo_lives(t_philo *philo);
int				someone_died(t_philo *philo);
void			kill_everyone(t_data *data, int which, int *everyone_lives);
int				p_state(t_philo *philo, int state);

//	UTILS

int				time_delay_test(void);
int				p_color(int color, char *s);
void			*ft_calloc(size_t nmemb, size_t size);
long long int	ft_atoi(const char *nptr);
int				fd_printf(int fd, const char *str, ...);
int				l_printf(const char *str, ...);
int				ft_wait(long long int pause);
int				get_current_time(struct timeval *start, long long int *current);

#endif