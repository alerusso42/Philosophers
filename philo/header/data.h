/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:17:53 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 10:48:39 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# include "header.h"
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

/*
//	MESSAGES
*/
# define M_THINK "%d %d is thinking\n"
# define M_EAT "%d %d is eating\n"
# define M_SLEEP "%d %d is sleeping\n"
# define M_FORK "%d %d has taken a fork\n"
# define M_DEAD "%d %d died\n"

/*
//	This defines the pause from a monitor check and another
*/
# define MONITOR_TIMER 10e3
# define TIME_THINK 150

enum e_error
{
	OK,
	ER_BAD_ARGC,
	ER_MALLOC,
	ER_NEGATIVE,
	ER_INVALID_ARG,
	ER_GETTIMEOFDAY,
	ER_USLEEP,
	ER_MUTEX_INIT,
	ER_PTHREAD_CREATE,
};

/*
//	MS Stands for MilliSeconds
//	Time during philo print is in microseconds.
//	MS divides time before print
*/
enum e_time
{
	MICROSECONDS = 1LL,
	MS = 1000LL,
	MSECONDS = 1000LL,
	SECONDS = 1000000LL,
	MINUTES = 6000000LL,
};

enum e_philo_state
{
	THINK = 0,
	EAT = 1,
	SLEEP = 2,
	FORK = 3,
	DEAD = 4,
	FULL = 5,
};

enum e_color
{
	RESET = 0,
	BLACK = 30,
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	MAGENTA = 35,
	CYAN = 36,
	WHITE = 37,
	BOLD_BLACK = 90,
	BOLD_RED = 91,
	BOLD_GREEN = 92,
	BOLD_YELLOW = 93,
	BOLD_BLUE = 94,
	BOLD_MAGENTA = 95,
	BOLD_CYAN = 96,
	BOLD_WHITE = 97,
};

//philo * is an array of philosophers data structures
//threads * is an array of threads
//forks * is an array of forks (mutex)
//generic_mutex * is an array of mutex
//
//times are long long to manage atoi errors
//someone died is updated by philosophers after death
//
//write mutex is used by philos to write and check if others died
//to check if others died they use a ptr to someone died
//
//generic mutex is used for:
//- philo->last_meal_time
//- philo->state
//otherwise data raise between monitor and philos would occur
struct s_data
{
	struct timeval	time;
	t_philo			*philo;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*generic_mutex;
	long long int	philo_num;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	number_of_times_each_philosopher_must_eat;
	long long int	current_time;
	pthread_t		monitor;
	pthread_mutex_t	write_mutex;
	unsigned char	someone_died;
};

//state represents enum e_state (DEAD, THINK, EATING...)
//id of philo starts at ZERO
struct s_philo
{
	struct timeval	time;
	unsigned char	*someone_died;
	pthread_mutex_t	*philo_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*generic_mutex;
	long long int	philo_num;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	current_time;
	long long int	last_meal_time;
	int				number_of_times_each_philosopher_must_eat;
	int				id;
	int				turn_to_eat;
	unsigned char	state;
	unsigned char	last_philo;
	unsigned char	death;
};

#endif