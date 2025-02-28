/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:28:54 by mait-taj          #+#    #+#             */
/*   Updated: 2025/02/19 09:24:53 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	(void)ac;
	t_cub	data;

	init_data(&data, NULL, NULL, DATA);
	if (!check_valid_extension(av[1]))
		return (1);
	data.file = av[1];
	first_step_to_map(&data);
	printf("\n\n<<<<<<<<<<<< Map is good >>>>>>>>>>>\n\n");
	return (0);
}
