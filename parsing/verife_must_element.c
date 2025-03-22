/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verife_must_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:04:20 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/22 15:02:32 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	before_filling(t_cub *data)
{
	t_help		*help;
	t_filling	*fill;

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
}

void	set_element(t_cub *data)
{
	t_filling	*mp;
	t_filling	*prev;

	mp = data->filling;
	data->help->x = 0;
	while (mp && mp->line && (data->help->x < data->begin_map - 1 \
		|| just_empty_line(mp->line) == true))
	{
		if (just_empty_line(mp->line) == false)
			expand_texture(data, mp->line);
		prev = mp;
		mp = mp->next;
		free(prev->line);
		free(prev);
		prev = NULL;
		if (!mp)
		{
			data->filling = NULL;
			return ;
		}
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
		data->maps->N_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'S')
		data->maps->S_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'W')
		data->maps->W_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'E')
		data->maps->E_texture = ft_strdup(&info[2]);
	if (info[0] && info[0] == 'C')
		data->maps->CE_color = convert_floor_celing_color(data, &info[1]);
	if (info[0] && info[0] == 'F')
		data->maps->FL_color = convert_floor_celing_color(data, &info[1]);
}

bool	find_all_elem(t_help *help)
{
	if (help->C == true && help->EA == true && help->F == true
		&& help->NO == true && help->SO == true && help->WE == true)
	{
		return (true);
	}
	return (false);
}
