/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:43:23 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/24 11:06:54 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_rgb(t_cub *data, char *line, t_help *help)
{
	char	**spl;
	int		i;
	int		res;

	i = 0;
	spl = ft_split(line, ',');
	if (!spl)
	{
		write(2, "Error\nmalloc faill\n", 19);
		exit(free_struct(data));
	}
	while (spl[i])
	{
		res = ft_atoi(spl[i++]);
		if (res > 255 || res < 0)
		{
			err_or(data, "R,G,B colors must be in range [0,255]"\
				, ft_itoa(help->i + 1), 0);
		}
	}
	free_d_arr(spl);
}

void	argu_ment(t_cub *data, char *line, int index)
{
	int	i;

	i = 0;
	i += skip_spaces(line);
	if (line[i] == '\0' || line[i] == '\n')
		err_or(data, "Set valid R,G,B color", ft_itoa(index), 0);
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] && line[i] == ' ')
	{
		i += skip_spaces(&line[i]);
		if (line[i] && line[i] != '\n')
			err_or(data, "space between digit encountered", ft_itoa(index), 0);
	}
}

void	only_digits(t_cub *data, char *line, int i)
{
	if ((line[i] == '+' && ft_isdigit(line[i + 1])) || (line[i] != ' '\
		&& line[i] != ',' && line[i] != '\n' && !ft_isdigit(line[i])))
		simple_err(data, "R,G,B color must contain only digit\n");
}

char	*argcolor(t_cub *data, char *line, int index, int i)
{
	int		ver;
	char	**spl;

	ver = 0;
	i = 0;
	i += skip_spaces(line);
	if (line[i] == ',')
		simple_err(data, "Syntax error; R,G,B color\n");
	while (line[i])
	{
		only_digits(data, line, i);
		if (line[i] == ',' && line[i + 1] == ',')
			break ;
		if (line[i++] == ',')
			ver++;
	}
	if (ver != 2)
		err_or(data, "Too many comma `,'", ft_itoa(index), 0);
	spl = ft_split(line, ',');
	i = 0;
	while (spl[i])
		argu_ment(data, spl[i++], index);
	free_d_arr(spl);
	return (ft_strdup(&line[1]));
}

void	color_valid(t_cub *data, t_help *help, char *line)
{
	int	i;

	i = 1;
	if (line[0] && (line[0] == 'C' || line[0] == 'F'))
	{
		i += skip_spaces(&line[i]);
		is_rgb(data, &line[1], help);
	}
}
