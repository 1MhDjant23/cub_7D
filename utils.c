/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:35:59 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/01 11:49:38 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_compare(char *s1, char *s2)
{
    size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

void	init_data(t_cub *data, t_help *help, t_map *maps , t_stat stat)
{
	if (stat == DATA)
	{
		data->file = NULL;
		data->map = NULL;
		data->line_m = NULL;
		data->help = NULL;
		data->begin_map = 0;
		data->end_map = 0;
		data->player = 0;
	}
	if (stat == HELP)
	{
		help->i = 0;
		help->x = 0;
		help->tmp = NULL;
		help->player = 0;
		help->C = false;
		help->F = false;
		help->NO = false;
		help->SO = false;
		help->WE = false;
		help->EA = false;
	}
	if (stat == MAP)
	{
		maps->map = NULL;
		maps->CE_color = NULL;
		maps->FL_color = NULL;
		maps->N_texture = NULL;
		maps->W_texture = NULL;
		maps->S_texture = NULL;
		maps->E_texture = NULL;
		maps->pl_xx = 0;
		maps->pl_yy = 0;
	}
}

void	before_filling(t_cub *data)
{
	t_help		*help;
	t_filling	*fill;

	help = data->help;
	help->tmp = get_next_line(help->i);
	if (!help->tmp || help->tmp[0] == '\0')
	{
		free(help->tmp);
		print_err(EMPTY);
		exit(EXIT_FAILURE);
	}
	fill = create_node(help->tmp);
	data->filling = fill;
	while (true)
	{
		printf("{%s}\n", fill->line);
		free(help->tmp);
		help->tmp = get_next_line(help->i);
		if (!help->tmp)
			break ;
		add_node(&fill, create_node(help->tmp));
	}
	close(data->help->i);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	coun_line(char **map)//at now i don't use it 
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	set_element(t_cub *data)
{
	t_filling	*mp;
	t_filling	*prev;

	mp = data->filling;
	data->help->x = 0;
	while (mp && mp->line && (data->help->x < data->begin_map - 1 || just_empty_line(mp->line) == true))
	{
		printf("%s", mp->line);
		if (just_empty_line(mp->line) == false)
			expand_texture(data->maps, mp->line);
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

void	set_bool(t_help *help, char c)
{
	if (c == 'N')
		help->NO = true;
	else if (c == 'S')
		help->SO = true;
	else if (c == 'W')
		help->WE = true;
	else if (c == 'E')
		help->EA = true;
	else if (c == 'F')
		help->F = true;
	else if (c == 'C')
		help->C = true;
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

