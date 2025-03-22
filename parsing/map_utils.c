/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:30:39 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/22 17:59:23 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player(t_cub *data, char *line, int y, t_stat stat)
{
	int	i;

	i = 0;
	if (stat == LEFT)
	{
		while (line[++i])
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W')
			{
				set_position(data->maps, line[i]);
				data->maps->pl_xx = i + 1;
				data->maps->pl_yy = y + data->begin_map;
				data->player++;
			}
		}
		if (data->player > 1)
			err_or(data, "Too many player in map", ft_itoa(data
					->begin_map + y), 1);
	}
	else if (stat == RIGHT)
	{
		if (data->player != 1)
			simple_err(data, "map must contain a player(N, S, E or W).\n");
	}
}

bool	cond_wall(char **map, int y, int i)
{
	if ((map[y][i + 1] && map[y][i + 1] != '0' && map[y][i + 1] != '1'
		&& !is_a_player(map[y][i + 1]))
			|| (map[y][i - 1] && map[y][i - 1] != '0'
			&& map[y][i - 1] != '1' && !is_a_player(map[y][i - 1]))
			|| (map[y + 1][i] && map[y + 1][i] != '0' && map[y + 1][i]
			!= '1' && !is_a_player(map[y + 1][i]))
			|| (map[y - 1][i] && map[y - 1][i] != '0' && map[y - 1][i]
			!= '1' && !is_a_player(map[y - 1][i])))
	{
		return (true);
	}
	return (false);
}

void	inv_character(t_cub *data, char c)
{
	if (c != '0' && c != '1' && c != ' ' && !is_a_player(c))
	{
		write(2, "Invalid charactere encountered\n", 31);
		exit(free_all_data(data));
	}
}

void	surrounded_wall(t_cub *data, int y, int i)
{
	if (ft_strlen(data->maps->map[y]) > ft_strlen(data->maps->map[y - 1])
		&& i >= (int)(ft_strlen(data->maps->map[y - 1]))
			&& data->maps->map[y][i] != '1')
	{
		complex_err(data, "map must closed and surrounded by walls `1`",
			ft_itoa(data->begin_map + y), ft_itoa(i + 1));
	}
	if (ft_strlen(data->maps->map[y]) > ft_strlen(data->maps->map[y + 1])
		&& i >= (int)(ft_strlen(data->maps->map[y + 1]))
			&& data->maps->map[y][i] != '1')
	{
		complex_err(data, "map must closed and surrounded by walls `1`",
			ft_itoa(data->begin_map + y), ft_itoa(i + 1));
	}
}

void	insid_map(t_cub *data, int i)
{
	int		y;

	y = 0;
	while (data->maps->map[++y] && y < data->end_map)
	{
		player(data, data->maps->map[y], y, LEFT);
		i = -1;
		while (data->maps->map[y][++i])
		{
			inv_character(data, data->maps->map[y][i]);
			if (data->maps->map[y][i] == '0' || is_a_player(data->maps
				->map[y][i]))
			{
				surrounded_wall(data, y, i);
				if (cond_wall(data->maps->map, y, i))
				{
					complex_err(data, "map must closed and \
						surrounded by walls `1`",
						ft_itoa(data->begin_map + y), ft_itoa(i + 1));
				}
			}
		}
	}
	player(data, NULL, 0, RIGHT);
}
