/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:28:54 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/02 12:15:26 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_position(t_stat position)
{
	if (position == WEST)
		printf("WEST\n");
	if (position == EAST)
		printf("EAST\n");
	if (position == NORTH)
		printf("NORTH\n");
	if (position == SOUTH)
		printf("SOUTH\n");
}

int	main(int ac, char **av)
{
	(void)ac;
	t_cub	data;

	init_data(&data, NULL, NULL, DATA);
	if (!check_valid_extension(av[1]))
		return (1);
	data.file = av[1];
	first_step_to_map(&data);
	int	i = 0;
	while (data.maps->map[i])
	{
		printf("%s\n", data.maps->map[i++]);
	}
	printf("%s\n", data.maps->CE_color);
	printf("%s\n", data.maps->FL_color);
	printf("%s\n", data.maps->N_texture);
	printf("%s\n", data.maps->W_texture);
	printf("%s\n", data.maps->S_texture);
	printf("%s\n", data.maps->E_texture);
	printf("%d\n", data.maps->pl_xx);
	printf("%d\n", data.maps->pl_yy);
	print_position(data.maps->start_position);
	// printf("%s\n", data.maps->E_texture);
	printf("\n\n<<<<<<<<<<<< Map is good >>>>>>>>>>>\n\n");
	return (0);
}
