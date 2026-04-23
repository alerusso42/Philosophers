/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:25:46 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/31 10:06:27 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define TOO_MUCH_SIGNS 0
#define TRUE 1

static int				ft_isspace(const char str);
static long long int	ft_size(const char *str, long long int *i);
static int				ft_issign(const char *str, long long int *i);
static int				ft_isdigit(const char str);
/*
int main()
{
    char    str[30] = "  \f\n\r \t \v ++-2147483646";
    int     number;

    number = atoi(str);
    printf("originale: %d\n", number);
    number = ft_atoi(str);
    printf("replica: %d\n", number);
    return (0);
}
*/

/*
	Atoi modified: 	if there are too much signs, returns LLONG_MAX;
					if there are non digit characters, returns LLONG_MIN.
*/
long long int	ft_atoi(const char *nptr)
{
	long long int			i;
	int						sign;
	long long int			number;
	long long int			size_numb;

	i = 0;
	sign = 1;
	number = 0;
	while (ft_isspace(nptr[i]) == TRUE)
		++i;
	sign = ft_issign(nptr, &i);
	if (sign == TOO_MUCH_SIGNS)
		return (LLONG_MAX);
	size_numb = ft_size(nptr, &i);
	while ((ft_isdigit(nptr[i]) == TRUE))
	{
		number += (1 * size_numb) * (nptr[i] - '0');
		size_numb = size_numb / 10;
		++i;
	}
	if ((nptr[i] != '\0') && (nptr[i] != ' '))
		return (LLONG_MAX);
	number = number * sign;
	return (number);
}

static int	ft_isspace(const char str)
{
	if (str == ' ' || str == '\f' || str == '\n')
		return (1);
	if (str == '\r' || str == '\t' || str == '\v')
		return (1);
	return (0);
}

static int	ft_isdigit(const char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

static int	ft_issign(const char *str, long long int *i)
{
	int	sign;
	int	too_much_signs;

	sign = 1;
	too_much_signs = 2;
	while (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = sign * -1;
		++(*i);
		--too_much_signs;
		if (too_much_signs <= 0)
		{
			return (TOO_MUCH_SIGNS);
		}
	}
	return (sign);
}
// ft_size gives a multiple of 10.

static long long int	ft_size(const char *str, long long int *i)
{
	long long int	size_numb;
	long long int	make_power;
	long long int	local_i;

	make_power = 0;
	while (str[*i] == '0')
		++(*i);
	local_i = *i;
	while (ft_isdigit(str[local_i]) == 1)
	{
		++make_power;
		++local_i;
	}
	size_numb = 1;
	while ((make_power != 0) & (make_power != 1))
	{
		size_numb = size_numb * 10;
		--make_power;
	}
	if (make_power == 0)
		size_numb = 0;
	return (size_numb);
}
