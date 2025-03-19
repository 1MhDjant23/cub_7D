/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:37:20 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/17 16:38:13 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_rgb(char *line, t_help *help)
{
	char	**spl;
	int		i;
	int		res;

	i = 0;	
	spl = ft_split(line, ',');
	if (!spl)
		exit(1);
	while (spl[i])
	{
		res = ft_atoi(spl[i++]);
		if (res > 255 || res < 0)
		{
			write(2, "Error\n(line: `", 14);
			write(2, ft_itoa(help->i + 1), ft_strlen(ft_itoa(help->i + 1)));
			write(2, "'): R,G,B colors must be in range [0,255]\n", 42);
			exit(1);
		}
	}
	free_d_arr(spl);
}

void	argu_ment(char *line, char **splt, int index)
{
	int	i;
(void)splt;
	i = 0;
	i += skip_spaces(line);

	if (line[i] == '\0' || line[i] == '\n')
	{
		write(2, "Error\n(line: `", 14);
		write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
		exit(write(2, "');Set valid R,G,B color\n", 25));
	}
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] && line[i] == ' ')
	{
		i += skip_spaces(&line[i]);
		if (line[i] && line[i] != '\n')
		{
			write(2, "Error\n(line: `", 14);
			write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
			exit(write(2, "');space between digit encountered\n", 35));
		}
	}
}

char	*valid_arg_color(char *line, int index, int i)
{
	int		ver;
	char	**spl;

	ver = 0;
	i = 0;
	i += skip_spaces(line);
	if (line[i] == ',')
		exit(write(2, "Error\nSyntax error; R,G,B color\n", 32));
	while (line[i])
	{
		if (( line[i] == '+' && ft_isdigit(line[i + 1])) || (line[i] != ' ' && line[i] != ',' && line[i] != '\n' && !ft_isdigit(line[i])))
			exit(write(2, "Error\nR,G,B color must contain only digit\n", 42));
		if (line[i] == ',' && line[i + 1] == ',')
			break ;
		if (line[i++] == ',')
			ver++;
	}
	if (ver != 2)
	{
		write(2, "Error\nToo many comma `,' in line (", 34);
		write(2, ft_itoa(index), ft_strlen(ft_itoa(index)));
		exit(write(2, ")!.\n", 4));
	}
	spl = ft_split(line, ','); // hereeeee e e e e e e e e ee  e e e e e e e 
	i = 0;
	while (spl[i])
		argu_ment(spl[i++], spl, index);
	free_d_arr(spl);
	return (&line[1]);
}


void	color_valid(t_help *help , char *line)
{
	int	i;

	i = 1;
	
	if (line[0] && (line[0] == 'C' || line[0] == 'F'))
	{
		i += skip_spaces(&line[i]);
		is_rgb(&line[1], help);
	}
}
