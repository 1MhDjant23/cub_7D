
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:31:39 by mait-taj          #+#    #+#             */
/*   Updated: 2025/01/05 18:16:41 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

/*$$$$$$$$$$$$$$$$$$$$$ Struct $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef	enum	s_stat
{
	HELP,
	DATA,
	EXTENS,
	EMPTY,
	MAP,
	LEFT,
	RIGHT,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	// FLOOR,
	// CEILING,
}	t_stat;

typedef	struct	s_map
{
	char	**map;
	char	*N_texture;
	char	*S_texture;
	char	*W_texture;
	char	*E_texture;
	char	*FL_color;
	char	*CE_color;
	int			pl_xx;
	int			pl_yy;
	t_stat	start_position;//  start position and spawning orientation for player
}	t_map;
typedef	struct s_help
{
	int		i;
	int		x;
	int		player;
	char	*tmp;
	bool	NO;
	bool	SO;
	bool	WE;
	bool	EA;
	bool	C;
	bool	F;
	
}	t_help;

typedef	struct	s_filling
{
	char				*line;
	struct s_filling	*next;
}				t_filling;

typedef	struct s_cub
{
	char		*file;
	char		*line_m;
	char		**map;
	int			begin_map;
	int			end_map;
	int			player;
	t_help		*help;
	t_map		*maps;
	t_filling	*filling;
}				t_cub;

/*_______________________________ Parse Input ______________________________________*/

bool	check_valid_extension(char *file_name);
bool	first_step_to_map(t_cub *data);

/*__________ Utils ______________ Utils _________________ Utils ____________________*/

size_t	ft_compare(char *s1, char *s2);
void	init_data(t_cub *data, t_help *help, t_map *maps, t_stat stat);
void	before_filling(t_cub *data);
int		coun_line(char **map);
// int		coun_line(char *line);
// char	*str_str(char *src, char *st, t_help *help);
// void    check_necessary_elem(t_cub *data);
// t_stat	choise_stat(int n);
int		skip_spaces(char *str);
// void	extr_val_of_elem(char *elemnt, t_help *help);
t_filling	*create_node(char *content);
// bool	check_empty_line(char *line);
void	add_node(t_filling **head, t_filling *new);
void	first_check_of_elem(t_cub *data);
bool	check_line_element(t_help *help, char *line);
void	set_bool(t_help *help, char c);
bool	find_all_elem(t_help *help);
bool	just_empty_line(char *line);
char	*extract_element(char *line, int index, char *src, int x);
void	all_element_is_good(t_cub *data);
void	path_if_exist(t_cub *data, char *line);
void	color_valid(t_help *help , char *line);
bool	without_info(char *line);
char	*valid_arg_color(char *line, int index, int i);

/*+++++++++++++++++++++ Parse Map ++++++++++++++++++++++++++++++++++++++++++++++++++*/

size_t	getLastCharInLine(char *line);
void	check_wall_of_map(t_cub *data);
void	set_element(t_cub *data);
void	expand_texture(t_map *maps, char *info);
int		list_size(t_filling *mp);
void	insid_map(t_cub *data, int i);
void	reset_map(t_cub *data);
/*_________________________ Error message____________________________________________*/

void	print_err(t_stat stat);
void	cannot_find(char *str);
void	elem_not_found(char *str);
int		print_errline(char *i_to_a, char *s1);

/*______________________________ Free Data ___________________________________________*/

void	free_d_arr(char **str);
void	free_map_ele(t_map *maps);
void	free_all_data(t_cub *data);
#endif
