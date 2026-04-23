/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:01:47 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:48 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <malloc.h>
# include <semaphore.h>
# include <fcntl.h>

# define SEM_NAME "sem"

enum	e_forks
{
	LOCK,
	UNLOCK,
};

enum	e_action
{
	SLEEPING,
	EATING,
	THINKING,
	FORK,
	FULL,
};

typedef struct s_table	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_mutex_t	deadlock;
	int				id;
	long			last_dinner_time;
	long			meal_counter;
	bool			full;
	bool			is_dead;
	bool			is_full;
}						t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_t		*guardian;
	pthread_mutex_t	mutex;
	sem_t			*fork_sem;
	sem_t			*write_sem;
	sem_t			*death_sem;
	pid_t			*pid_array;
	long			n_philo;
	long			t_death;
	long			t_eat;
	long			t_sleep;
	long			max_dinner;
	long			start_program;
}						t_table;

int		parsing(char **argv);
long	ft_atol(const char *nptr);
void	init_table(t_table *table);
void	clear(t_table *table);
long	getcorrecttime(void);
int		ft_wait(long pause);
void	write_status(int action, t_philo *philo);
int		eat_and_sleep(t_philo *philo);
void	think(t_philo *philo);
void	lonely_boy(t_philo *philo);
void	marchinator(t_table *table);
int		mutex_handle(pthread_mutex_t *fork, int command);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	*death_guardian(void *data);
void	*jack_the_reaper(void *data);

#endif