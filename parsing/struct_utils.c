/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:39:02 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/17 16:40:12 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_filling	*create_node(t_cub *data, char *content)
{
	t_filling	*node;

	node = malloc(sizeof(t_filling));
	if (!node)
	{
		free(data->help->tmp);
		write(2, "Error\nThe allocation is failing.\n", 33);
		exit(free_struct(data));
	}
	node->line = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	add_node(t_filling **head, t_filling *new)
{
	t_filling	*temp;

	if (!head || !new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;		
}

void	extensionOfTextures(char *path)
{
	char	*tmp;
	if (!path)
		return ;
	tmp = ft_strrchr(path, '.');
	if (!tmp)
		exit(write(2, "Error\npath of textures must be a type of `.PNG`\n", 48));
	if (ft_compare(tmp, ".png") == 0)
		return ;
	exit(write(2, "Error\npath of textures must be a type of `.PNG`\n", 48));
}

void	path_if_exist(t_cub *data, char *line)
{
	char	*path;

	path = NULL;
	if (line[0] == 'E' || line[0] == 'N' || line[0] == 'S' || line[0] == 'W')
		path = &line[2];
	else
		return ;
	extensionOfTextures(path);
	data->help->x = open(path, O_RDONLY);
	if (data->help->x == -1)
	{
		write(2, "Error\n(line `", 13);
		write(2 , ft_itoa(data->help->i + 1), ft_strlen(ft_itoa(data->help->i)));
		write(2, "') enter a valid texture!.\n", 27);
		exit(1);
	}
	close(data->help->x);
}
