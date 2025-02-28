/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:30:42 by mait-taj          #+#    #+#             */
/*   Updated: 2025/02/19 09:23:34 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_valid_extension(char *file_name)
{
	int		i;
	char	*after_dot;

	i = 0;
	if (!file_name)
	{
		write(2, "Error\nUsage: ./cub3D [ map.cub ]\n", 32);
		return (false);
	}
	after_dot = ft_strrchr(file_name, '.');
	if (ft_strlen(after_dot) < 4 || ft_compare(after_dot, ".cub") != 0)
	{
		print_err(EXTENS);
		return (false);
	}
	if (ft_compare(file_name, ".cub") == 0)
	{
		write(2, "Error\ncan't accept a hidden file\n", 33);
		return (false);
	}
	return (true);
}

void	set_map(t_cub *data)
{
	t_map	maps;

	data->help->i = open(data->file, O_RDONLY, 0644);
	if (data->help->i == -1)
	{
		perror("open");// no alloc at this statement	
		exit(EXIT_FAILURE);
	}
	before_filling(data);// reading into the file, and store map in a char*.
	first_check_of_elem(data);
	if (!data->filling)
	{
		write(2, "Error\nmap not found\n", 20);
		exit(1);
	}
	all_element_is_good(data);
	init_data(NULL, NULL, &maps, MAP);
	data->maps = &maps;//start map checking
	set_element(data);
	check_wall_of_map(data);
	// printf("$$$$$$$$$$$$$$÷$$$$\n");
	free_d_arr(maps.map);
	maps.map = NULL;
	reset_map(data);
	// printf("for new line\n\n");
	insid_map(data, data->help->x);
	// int	x=0;
	// while (maps.map[x])
	// {
	// 	printf("%s\n", maps.map[x++]);
	// }
	
	// printf("%d\n", data->begin_map);
	// t_filling *tmp = data->filling;
	// while (tmp)
	// {
	// 	printf("%s", tmp->line);
		// printf("%s\n", data->maps->CE_color);
		// printf("%s\n", data->maps->FL_color);
		// printf("%s\n", data->maps->N_texture);
		// printf("%s\n", data->maps->S_texture);
		// printf("%s\n", data->maps->W_texture);
		// printf("%s\n", data->maps->E_texture);
	// 	tmp = tmp->next;
	// }
}

bool	first_step_to_map(t_cub *data)
{
	t_help	help;
	// t_map	maps;
	/**
			@param help - Struct on which i store some var.
			@brief Just for reduce lines
	*/
	init_data(NULL, &help, NULL, HELP);
	data->help = &help;
	set_map(data);
	// int	i =0;
	// while (data->map[i])
	// {
	// 	printf("[%s]", data->map[i++]);
	// }
	
	// init_data(NULL, &help, NULL, HELP);
	// init_data(NULL, NULL, &maps, MAP);
	// data->maps = &maps;
	// check_necessary_elem(data);
	return (false);
}
