/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 08:30:39 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/03 12:25:22 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	list_size(t_filling *mp)
{
	int	size;

	size = 0;
	while (mp)
	{
		size++;
		mp = mp->next;
	}
	return (size);
}

// size_t	getLastCharInLine(char *line)
// {
// 	size_t	len;
	
// 	if (!line)
// 		return (0);
// 	len = ft_strlen(line) - 2;
// 	// if (line[len] != '\n')
// 	// 	len += 1;
// 	while (line[len] && len > 0 && line[len] == ' ')
// 		len--;
// 	return (len + 1);
// }

char	*dup_line(char *s1)
{
	char	*dup_l;
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (!s1)
		return (NULL);
	if (just_empty_line(s1) == true)
		return (ft_strdup("\n"));
	len = ft_strlen(s1) - 2;
	while (len >= 0 && s1[len] && s1[len] == ' ')
		len--;
	len++;
	dup_l = malloc((len + 2) * sizeof(char));
	if (!dup_l)
		return (NULL);
	if (s1[0] != '\n' && s1[0] != ' ' && ft_strlen(s1) == 1)
		return (ft_strdup(s1));
	while (++i < len)
		dup_l[i] = s1[i];
	dup_l[i++] = '\n';
	dup_l[i] = '\0';
	return (dup_l);
}

void	list_to_darray(t_cub *data, int i)
{
	t_filling	*mp;
	int			size;

	i = 0;
	mp = data->filling;
	size = list_size(mp);
	data->maps->map = malloc(sizeof(char*) * (size + 1));
	if (!data->maps->map)
		exit(1);
	while (mp)
	{
		data->maps->map[i++] = dup_line(mp->line);
		mp = mp->next;
	}
	data->maps->map[i] = NULL;
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

void	wall_check(char *line, int index, int i)
{
	i = 0;
	i += skip_spaces(line);
	if (line[i] && line[i] == '\n')
	{
		write(2, "Error\n(line: `", 14);
		write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
		write(2, "');empty line encountered insid the map!\n", 41);
		exit(1);
	}
	if (line[i] != '1')
	{
		write(2, "Error\n(line: `", 14);
		write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
		write(2, "');left-wall must be closed by '1'.\n", 36);
		exit(1);
	}
	if (ft_strlen(line) > 1 && line[ft_strlen(line) - 2] != '1')
	{
		write(2, "Error\n(line: `", 14);
		write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
		write(2, "');right-wall must be closed by '1'.\n", 37);
		exit(1);
	}
}

void	Map_boundaries(int *end, char **map)
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

void	check_wall_of_map(t_cub *data)
{
	t_help	*hl;

	hl = data->help;
	// init_data(NULL, NULL, data->maps, MAP);
	init_data(NULL, data->help, NULL, HELP);
	if (!data->filling)
	{
		write(2, "can't find map\n", 15);
		exit(1);
	}
	list_to_darray(data, data->help->x);
	Map_boundaries(&data->end_map, data->maps->map);
	if (line_map(data->maps->map[(hl->i)++], hl->x) == false) // line_map check the content of first and last line.
	{
		print_errline(ft_itoa(data->begin_map), "Error\n");
		write(2, ";this line must be the top-wall of the map, must contain only '1'.\n", 67);
		exit(1);
	}
	while (data->maps->map[hl->i] && hl->i <= data->end_map)
	{
		if (hl->i == data->end_map)
		{
			if (line_map(data->maps->map[hl->i], hl->x) == false) // check the last line.
			{
				print_errline(ft_itoa(data->begin_map + hl->i), "Error\n");
				write(2, ";this line must be the bottom-wall of the map, must contain only '1'.\n", 70);
				exit(1);
			}
		}
		wall_check(data->maps->map[hl->i], data->begin_map + hl->i, hl->x);
		(hl->i)++;
	}
}

void	set_position(t_map *maps, char p)
{
	if (p == 'N')
		maps->start_position = NORTH;
	if (p == 'S')
		maps->start_position = SOUTH;
	if (p == 'E')
		maps->start_position = EAST;
	if (p == 'W')
		maps->start_position = WEST;
}

void	player(t_cub *data, char *line, int y, t_stat stat)
{
	int	i;

	i = 0;
	if (stat == LEFT)
	{
		while (line[++i])
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				set_position(data->maps, line[i]);
				data->maps->pl_xx = i + 1;
				data->maps->pl_yy = y + data->begin_map;
				data->player++;
			}
		}
		if (data->player > 1)
		{
			write(2, "Error\nToo many player in map ", 29);
			exit(print_errline(ft_itoa(data->begin_map + y), NULL));
		}
	}
	else if (stat == RIGHT)
	{
		if (data->player != 1)
		{
			write(2, "Error\nmap must contain a player(N, S, E or W).\n", 47);
			exit (1);
		}
	}
}

bool	is_a_player(char c)
{
	if (c != '\0' &&( c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		return (true);
	return (false);
}

void	reset_map(t_cub *data)
{
	t_filling	*fill;
	int	i;

	fill = data->filling;
	i = -1;
	while (fill && ++i <= data->end_map)
	{
		data->help->tmp = ft_strjoin(data->help->tmp, fill->line);
		// printf("%s", fill->line);
		// free(fill->line);
		// free(fill);
		// fill = NULL;
		fill = fill->next;
	}
	data->maps->map = ft_split(data->help->tmp, '\n');
	free(data->help->tmp);
	data->help->tmp = NULL;
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
			if (data->maps->map[y][i] != '0' && data->maps->map[y][i] != '1' && data->maps->map[y][i] != ' ' && !is_a_player(data->maps->map[y][i]))
				exit(write(2, "Invalid charactere encountered\n", 31));
			if (data->maps->map[y][i] == '0' || is_a_player(data->maps->map[y][i]))
			{
				if (ft_strlen(data->maps->map[y]) > ft_strlen(data->maps->map[y - 1]) && i >= (int)(ft_strlen(data->maps->map[y - 1]) ) && data->maps->map[y][i] != '1')
				{
					write(2, "Error\nLn ", 9);
					write(2, ft_itoa(data->begin_map + y), ft_strlen(ft_itoa(data->begin_map + y)));
					write(2, ", Col ", 6);
					write(2, ft_itoa(i + 1), ft_strlen(ft_itoa(i + 1)));
					exit(write(2, ";map must closed and surrounded by walls `1`\n", 45));
				}
				if (ft_strlen(data->maps->map[y]) > ft_strlen(data->maps->map[y + 1]) && i >= (int)(ft_strlen(data->maps->map[y + 1]) ) && data->maps->map[y][i] != '1')
				{
					write(2, "Error\nLn ", 9);
					write(2, ft_itoa(data->begin_map + y), ft_strlen(ft_itoa(data->begin_map + y)));
					write(2, ", Col ", 6);
					write(2, ft_itoa(i + 1), ft_strlen(ft_itoa(i + 1)));
					exit(write(2, ";map must closed and surrounded by walls `1`\n", 45));
				}
				if ((data->maps->map[y][i + 1] && data->maps->map[y][i + 1] != '0' && data->maps->map[y][i + 1] != '1' && !is_a_player(data->maps->map[y][i + 1]))
					|| (data->maps->map[y][i - 1] && data->maps->map[y][i - 1] != '0' && data->maps->map[y][i - 1] != '1' && !is_a_player(data->maps->map[y][i - 1]))
					|| (data->maps->map[y + 1][i] && data->maps->map[y + 1][i] != '0' && data->maps->map[y + 1][i] != '1' && !is_a_player(data->maps->map[y + 1][i]))
					|| (data->maps->map[y - 1][i] && data->maps->map[y - 1][i] != '0' && data->maps->map[y - 1][i] != '1'  && !is_a_player(data->maps->map[y - 1][i])))
				{
					write(2, "Error\nLn ", 9);
					write(2, ft_itoa(data->begin_map + y), ft_strlen(ft_itoa(data->begin_map + y)));
					write(2, ", Col ", 6);
					write(2, ft_itoa(i + 1), ft_strlen(ft_itoa(i + 1)));
					exit(write(2, ";map must closed and surrounded by walls `1`\n", 45));
				}
			}
		}
	}
	player(data, NULL, 0, RIGHT);
}
