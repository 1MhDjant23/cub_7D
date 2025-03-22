/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_u_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:51:57 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/22 17:29:06 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*dup_line(t_cub *data, char *s1)
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
		exit(free_all_data(data));
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
	data->maps->map = malloc(sizeof(char *) * (size + 1));
	if (!data->maps->map)
		simple_err(data, "Malloc Insufficient Memory.\n");
	while (mp)
	{
		data->maps->map[i++] = dup_line(data, mp->line);
		mp = mp->next;
	}
	data->maps->map[i] = NULL;
}

void	reset_map(t_cub *data)
{
	t_filling	*fill;
	int			i;
	char		*tmp;

	fill = data->filling;
	i = -1;
	data->help->tmp = ft_strjoin(data->help->tmp, fill->line);
	fill = fill->next;
	while (fill && ++i <= data->end_map)
	{
		tmp = data->help->tmp;
		data->help->tmp = ft_strjoin(data->help->tmp, fill->line);
		free(tmp);
		free(fill->line);
		free(fill);
		fill = fill->next;
	}
	free(data->filling);
	data->maps->map = ft_split(data->help->tmp, '\n');
	free(data->help->tmp);
	data->help->tmp = NULL;
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

bool	is_a_player(char c)
{
	if (c != '\0' && (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		return (true);
	return (false);
}
