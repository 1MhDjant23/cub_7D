/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verife_must_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:04:20 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/25 15:35:40 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	before_filling(t_cub *data)
{
	t_help	*help;
	t_fil	*fill;

	help = data->help;
	help->tmp = get_next_line(help->i);
	if (!help->tmp || help->tmp[0] == '\0')
	{
		print_err(EMPTY);
		exit(EXIT_FAILURE);
	}
	fill = create_node(data, help->tmp);
	data->filling = fill;
	while (true)
	{
		free(help->tmp);
		help->tmp = get_next_line(help->i);
		if (!help->tmp)
			break ;
		add_node(&fill, create_node(data, help->tmp));
	}
	free(help->tmp);
}

void	set_element(t_cub *data)
{
	t_fil	*mp;
	t_fil	*prev;

	mp = data->filling;
	data->help->x = 0;
	while (mp && mp->line && (data->help->x < data->begin_map - 1 \
		|| just_empty_line(mp->line) == true))
	{
		if (just_empty_line(mp->line) == false)
			expand_texture(data, mp->line);
		prev = mp->next;
		free(mp->line);
		mp->line = NULL;
		free(mp);
		mp = NULL;
		if (!prev)
		{
			free_struct(data);
			data->filling = NULL;
			return ;
		}
		mp = prev;
		(data->help->x)++;
	}
	data->filling = mp;
}

int	convert_floor_celing_color(t_cub *data, char *text_color)
{
	char	**rgba;
	int		index;
	int		r;
	int		g;
	int		b;

	index = 0;
	rgba = ft_split(text_color, ',');
	if (!rgba)
	{
		write(2, "malloc\n", 7);
		exit(free_struct(data));
	}
	index += skip_spaces(rgba[0]);
	r = ft_atoi(&rgba[0][index]);
	index += skip_spaces(rgba[0]);
	g = ft_atoi(&rgba[1][index]);
	index += skip_spaces(rgba[0]);
	b = ft_atoi(&rgba[2][index]);
	free_d_arr(rgba);
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	expand_texture(t_cub *data, char *info)
{
	if (!info)
		return ;
	if (info[0] && info[0] == 'N')
		data->maps->n_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'S')
		data->maps->s_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'W')
		data->maps->w_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'E')
		data->maps->e_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'C')
		data->maps->ce_color = convert_floor_celing_color(data, &info[1]);
	if (info[0] && info[0] == 'F')
		data->maps->fl_color = convert_floor_celing_color(data, &info[1]);
}

bool	find_all_elem(t_help *help)
{
	if (help->c == true && help->ea == true && help->f == true
		&& help->no == true && help->so == true && help->we == true)
	{
		return (true);
	}
	return (false);
}
