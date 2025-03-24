/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:03:47 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/24 17:47:41 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sub_setting(t_help *help, char c, t_cub *data)
{
	if (c == 'N')
	{
		help->NO = true;
		data->count_elem++;
	}
	else if (c == 'S')
	{
		help->SO = true;
		data->count_elem++;
	}
	else if (c == 'W')
	{
		help->WE = true;
		data->count_elem++;
	}
}

void	set_bool(t_help *help, char c, t_cub *data)
{
	if (c == 'E')
	{
		help->EA = true;
		data->count_elem++;
	}
	else if (c == 'F')
	{
		help->F = true;
		data->count_elem++;
	}
	else if (c == 'C')
	{
		help->C = true;
		data->count_elem++;
	}
	sub_setting(help, c, data);
}

size_t	until_new_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

bool	is_a_player(char c)
{
	if (c != '\0' && (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		return (true);
	return (false);
}

int	coun_line2(char **map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i] && !just_empty_line(map[i]))
		i++;
	return (i);
}
