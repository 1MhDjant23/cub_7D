/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:33:19 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/25 13:45:39 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_check(t_cub *data, char *line, int index, int i)
{
	i = 0;
	i += skip_spaces(line);
	if (line[i] && line[i] == '\n')
	{
		free_map_ele(data->maps);
		err_or(data, "empty line encountered insid the map!",
			ft_itoa(index), 1);
	}
	if (line[i] != '1')
	{
		free_map_ele(data->maps);
		err_or(data, "left-wall must be closed by '1'.", ft_itoa(index), 1);
	}
	if (ft_strlen(line) > 1 && line[ft_strlen(line) - 2] != '1')
	{
		free_map_ele(data->maps);
		err_or(data, "right-wall must be closed by '1'.", ft_itoa(index), 1);
	}
}

void	top_wall_check(t_cub *data, t_help *hl)
{
	if (line_map(data->maps->map[(hl->i)++], hl->x) == false)
	{
		free_map_ele(data->maps);
		err_or(data, "line must be top-wall of map, must contain only '1'"\
			, ft_itoa(data->begin_map), 0);
	}
}

void	check_wall_of_map(t_cub *data)
{
	t_help	*hl;

	hl = data->help;
	init_data_2(data->help, NULL, HELP);
	if (!data->filling)
		simple_err(data, "file must containe map\n");
	list_to_darray(data, data->help->x);
	map_boundaries(&data->end_map, data->maps->map);
	top_wall_check(data, hl);
	while (data->maps->map[hl->i] && hl->i <= data->end_map)
	{
		if (hl->i == data->end_map)
		{
			if (line_map(data->maps->map[hl->i], hl->x) == false)
			{
				free_map_ele(data->maps);
				err_or(data, "line must be bottom-wall of map, \
				must contain only '1'", ft_itoa(data->begin_map + hl->i), 0);
			}
		}
		wall_check(data, data->maps->map[hl->i], data
			->begin_map + hl->i, hl->x);
		(hl->i)++;
	}
}

bool	line_map(char *line, int i)
{
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			i += skip_spaces(&line[i]);
		if (line[i] != '1' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

void	map_boundaries(int *end, char **map)
{
	int	size;

	size = coun_line(map) - 1;
	if (!map || !*map)
		exit (1);
	if (size == 0)
		return ;
	while (map[size] && just_empty_line(map[size]) == true)
		size--;
	*end = size;
}
