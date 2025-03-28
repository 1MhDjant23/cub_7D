/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_u_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:51:57 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/25 15:35:15 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	new_line_exist(char *s)
{
	int	i;

	if (!s)
		return (false);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

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
	if (!new_line_exist(s1))
		len = ft_strlen(s1) - 1;
	while (len >= 0 && s1[len] && s1[len] == ' ')
		len--;
	dup_l = malloc(((len++) + 2) * sizeof(char));
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
	t_fil	*mp;
	int		size;

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

int	line_struct(t_fil *fill)
{
	int	i;

	i = 0;
	while (fill && just_empty_line(fill->line) == false)
	{
		i++;
		fill = fill->next;
	}
	return (i);
}

void	reset_map(t_cub *data)
{
	t_fil	*fill;
	int		i;
	int		x;
	char	*tmp;

	tmp = NULL;
	i = -1;
	x = 0;
	data->maps->map = malloc(sizeof(char *) * (line_struct(data->filling) + 1));
	if (!data->maps->map)
		exit(free_all_data(data));
	fill = data->filling;
	while (fill && ++i <= data->end_map)
	{
		data->maps->map[x++] = ft_substr(fill->line, 0,
				until_new_line(fill->line));
		fill = fill->next;
	}
	data->maps->map[x] = NULL;
}
