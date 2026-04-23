/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:05:17 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/30 16:40:18 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
int	main()
{
	char	*pointer;

	pointer = (char *)ft_calloc(7, 2);
	if (pointer == NULL)
		return (FULL_MEMORY);
	ft_strlcpy(pointer, "sdv", 555);
	printf("\n%s\n", pointer);
	free(pointer);
	return (0);
}*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*pointer;

	pointer = NULL;
	if ((nmemb == 0) || (size == 0))
		return (malloc(0));
	total_size = (nmemb * size);
	if (total_size / nmemb != size)
		return (NULL);
	pointer = malloc(total_size);
	if (pointer == NULL)
		return (NULL);
	memset(pointer, 0, total_size);
	return (pointer);
}
