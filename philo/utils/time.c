/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:39:54 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 10:38:14 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int	get_current_time(struct timeval *start, long long int *current)
{
	struct timeval	curr;

	if ((start) && !(start->tv_sec) && !(start->tv_usec))
	{
		gettimeofday(start, NULL);
		return (0);
	}
	gettimeofday(&curr, NULL);
	*current = ((curr.tv_sec - start->tv_sec) * SECONDS) \
		+ (curr.tv_usec - start->tv_usec);
	return (0);
}

/*
	VERSION 2.0 (idea taken from Oceano)

	1)	We record the initial time;
	2)	We set the elapsed time (time from start) to
		zero. we'll loop until it is not bigger than
		the requested pause;
	LOOP:
		3)	We get data about the current time;
		4)	We update elapsed: current - start time;
		5)	We update rem (remaining time):
			requested pause - elapsed time;
		6)	If more than 1 MILLISECOND is left,
			ft_wait half the remaining time.

	This approach allows to sleep the most of the time,
	and to check strictly the last MICROSECONDS using
	gettimeofday.

	Here's an example, for a 10000 microseconds pause,
	Considering gettimeofday errors:

	1 STEP: elapsed is 2 microseconds, therefore
			rem = 9998 (10000 - 2);
			we sleep for rem / 2 = 4999 (9998 / 2);

	TOTAL SLEPT: 4999

	2 STEP: elapsed is 5000 microseconds, therefore
			rem = 5000 (10000 - 5000);
			we sleep for rem / 2 = 2500 (5000 / 2);

	TOTAL SLEPT: 7500

	3 STEP: elapsed is 7501 microseconds, therefore
			rem = 2499 (10000 - 7501);
			we sleep for rem / 2 = 1249 (2500 / 2);

	TOTAL SLEPT: 8750

	4 STEP: elapsed is 8750 microseconds, therefore
			rem = 1250 (10000 - 8750);
			we sleep for rem / 2 = 625 (1250 / 2);

	TOTAL SLEPT: 9375

	5 STEP: elapsed is 9377 microseconds, therefore
			rem = 623 (10000 - 9377);
			WE DONT SLEEP: rem is less than 1000

	TOTAL SLEPT: 9377

	6 STEP and so on: we rely only on gettimeofday errors.

	TOTAL SLEPT: 9378
	TOTAL SLEPT: 9378
	TOTAL SLEPT: 9380
	TOTAL SLEPT: 9381
	...
	TOTAL SLEPT: 10001

	//
	Notice: if usleep performs an error bigger than 1000,
			our current parameter, we'll have delays.
*/
int	ft_wait(long long int pause)
{
	usleep((int)pause);
	return (0);
}
/*
int	ft_wait(long long int pause)
{
	struct timeval	start;
	struct timeval	curr;
	long long int	rem;
	long long int	elapsed;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < pause)
	{
		gettimeofday(&curr, NULL);
		elapsed = ((curr.tv_sec - start.tv_sec) * SECONDS) \
		+ (curr.tv_usec - start.tv_usec);
		rem = pause - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}
	*/

/*
static int	calc_delay(long long int *delay);

	usleep function works with steps.

	If you need to ft_wait 20 micros:

	0 µs - 7 µs - 14 µs - 21 µs - STOP!

	Why did it stop at 21 micros, and not 20?
	Because it checks if it has waited enough time
	every often (in this example, every 7 micros).
	This chunk of time depends on system sheduling and
	CPU characteristics.

	What does the ft_wait function do?

	1)	If the delay has not been calculated yet, it
		calls calc_delay;
	2)	It calculates the rest in the division between
		the ft_wait length and the delay, saving it in diff
		(in above example: 20 % 7 = 6);
	3)	It calculates The big chunks of the ft_wait to do
		(in above example: 20 - 6 = 14);
	4)	It usleep for 14, then for 6.

	Still, the performance of regular usleep is still
	better.


int	ft_wait(long long int micros)
{
	static long long int	delay = -1;
	long long int			diff;
	long long int			big_ft_wait;
	int						err;

	err = 0;
	if (delay == -1)
		err = calc_delay(&delay);
	if (err != 0)
		return (err);
	diff = micros % delay;
	big_ft_wait = micros - (diff);
	if (usleep(big_ft_wait) != 0)
		return (ER_USLEEP);
	if (usleep(diff) != 0)
		return (ER_USLEEP);
	return (0);
}

static int	calc_delay(long long int *delay)
{
	struct timeval	time;
	struct timeval	paragon;

	if (gettimeofday(&time, NULL) != 0)
		return (ER_GETTIMEOFDAY);
	if (usleep(0) != 0)
		return (ER_USLEEP);
	if (gettimeofday(&paragon, NULL) != 0)
		return (ER_GETTIMEOFDAY);
	*delay = (((paragon.tv_sec - time.tv_sec) * 1000000) + \
	(paragon.tv_usec - time.tv_usec));
	return (0);
}

int	brute_ft_wait(long long int micros)
{
	while (micros--)
		usleep(1);
	return (0);
}
*/
