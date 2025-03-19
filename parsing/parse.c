/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:30:42 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/16 15:32:32 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_valid_extension(char *file_name)
{
	int		i;
	char	*after_dot;

	i = 0;
	if (!file_name)
	{
		write(2, "Error\nUsage: ./cub3D [ map.cub ]\n", 33);
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

void	set_large_line(t_map *maps)
{
	size_t	i;
	size_t	curent;
	char	*str;
	str = maps->map[0];
	i = 1;
	curent = ft_strlen(maps->map[0]);
	while (maps->map[i])
	{
		if (ft_strlen(maps->map[i]) > curent)
		{
			str = maps->map[i];
			curent = ft_strlen(maps->map[i]);
		}
		i++;
	}
	maps->column = coun_line(maps->map);
	maps->rwo = curent - 1;
}

void	set_map(t_cub *data)
{
	data->help->i = open(data->file, O_RDONLY, 0644);
	if (data->help->i == -1)
	{
		perror("open");// no alloc at this statement	
		exit(EXIT_FAILURE);
	}
	// exit(1);
	init_data_2(NULL, data->maps, MAP);
	before_filling(data);// reading into the file, and store map in a char*.
	close(data->help->i);
	first_check_of_elem(data);
	if (!data->filling)
		exit(write(2, "Error\nmap not found\n", 20));
	all_element_is_good(data);
	set_element(data);
	check_wall_of_map(data);
	set_large_line(data->maps);
	free_d_arr(data->maps->map);
	data->maps->map = NULL;
	reset_map(data);
	insid_map(data, data->help->x);
}

bool	first_step_to_map(t_cub *data)
{
	t_help	help;
	t_map	*maps;

	init_data_2(&help, NULL, HELP);
	data->help = &help;
	maps = malloc(sizeof(t_map));
	if (!maps)
		exit(EXIT_FAILURE);
	data->maps = maps;//start map checking
	set_map(data);
	return (false);
}
