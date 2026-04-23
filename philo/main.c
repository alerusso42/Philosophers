/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:06:05 by alerusso          #+#    #+#             */
/*   Updated: 2025/06/10 09:50:56 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/header.h"

int	main(int argc, char *argv[])
{
	int			err_type;
	t_data		data;

	data = (t_data){0};
	err_type = parsing(&data, argc, argv);
	if (err_type != 0)
		return (error(&data, err_type));
	err_type = start_threads(&data);
	if (err_type != 0)
		return (error(&data, err_type));
	err_type = quit_threads(&data);
	if (err_type != 0)
		return (error(&data, err_type));
	reset_memory(&data);
	return (0);
}
