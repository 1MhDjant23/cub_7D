
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
#include <math.h>
#include "/Users/mait-taj/Desktop/MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include "parsing/get_next_line/get_next_line.h"

/*$$$$$$$$$$$$$$$$$$$$$ macros $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
#define TILESIZE 50
#define WIDTH 1800//2560//1800
#define HEIGHT 900//1440
#define FOV 60
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define SPEED 10

/*$$$$$$$$$$$$$$$$$$$$$ Struct $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef	enum	s_stat
{
	HELP,
	DATA,
	EXTENS,
	EMPTY,
	MAP,
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_stat;


typedef	struct	s_map
{
	char	**map;
	char	*N_texture;
	char	*S_texture;
	char	*W_texture;
	char	*E_texture;
	int		FL_color;
	int		CE_color;
	int			pl_xx;
	int			pl_yy;
	int			rwo;
	int			column;
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
	int			count_elem;
	t_help		*help;
	t_map		*maps;
	t_filling	*filling;
}				t_cub;

/*$$$$$$$$$$$$$$$$$$$$$ Struct of rays and the player $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
typedef struct s_ray{
    double x_ray;//
    double y_ray;//
    double r_angle;
    int     facing_x;
    int     facing_y;
    double Hx;
    double Hy;
    double Vx;
    double Vy;
	bool	H_or_V;//
    double distance;//distance of ray
}ray_cast;

typedef	struct	s_pixel
{
	int	**SO_Pexel;
	int	**NO_Pexel;
	int	**WE_Pexel;
	int	**EA_Pexel;
	mlx_image_t	*NO;
	mlx_image_t	*SO;
	mlx_image_t	*WE;
	mlx_image_t	*EA;
}			t_pixel;
typedef struct p{
    // char **map;
	t_cub *data;
   double dir_angle;
   mlx_t *mlx;
    mlx_image_t * img;
    ray_cast *ray;
    double player_x;
    double player_y;
//------------------------
	t_pixel		*pixels;
}t_game;

/*_______________ Textures Parts ____________________________________________________*/
int	check_for_walls(t_game *game, double nx, double ny);
int get_rgba(int r, int g, int b, int a);
int	get_color_from_distance(double distance);//color draw
int	get_color_from_texture(t_game *game, int myXX, int myYY);//mait
void	load_pixels(t_game *game);
void	save_pixels(t_game *game);
void	load_images(t_game *game);
void	draw_wall(int *start_wall, t_game *game, int ray_counter, double line_H);
int	free_struct(t_cub *data);

/*_______________________________ Parse Input ______________________________________*/

bool	check_valid_extension(char *file_name);
bool	first_step_to_map(t_cub *data);
void	print_position(t_stat position);
/*__________ Utils ______________ Utils _________________ Utils ____________________*/

size_t	ft_compare(char *s1, char *s2);
void	init_data(t_cub *data);
void	init_data_2(t_help *help, t_map *maps, t_stat stat);
void	before_filling(t_cub *data);
int		coun_line(char **map);
// int		coun_line(char *line);
// char	*str_str(char *src, char *st, t_help *help);
// void    check_necessary_elem(t_cub *data);
// t_stat	choise_stat(int n);
int		skip_spaces(char *str);
// void	extr_val_of_elem(char *elemnt, t_help *help);
t_filling	*create_node(t_cub *data, char *content);
// bool	check_empty_line(char *line);
void	add_node(t_filling **head, t_filling *new);
void	first_check_of_elem(t_cub *data);
bool	check_line_element(t_help *help, char *line, t_cub *data);
void	set_bool(t_help *help, char c, t_cub *data);
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
void	expand_texture(t_cub *data, char *info);
int		list_size(t_filling *mp);
void	insid_map(t_cub *data, int i);
void	reset_map(t_cub *data);
/*_________________________ Error message____________________________________________*/

void	print_err(t_stat stat);
void	cannot_find(char *str);
void	elem_not_found(char *str);
int		print_errline(char *i_to_a, char *s1);
int		err(char *str);

/*______________________________ Free Data ___________________________________________*/

void	free_d_arr(char **str);
void	free_map_ele(t_map *maps);
void	free_all_data(t_cub *data);

/*______________________________Recasting Part ___________________________________________*/
// void	key_hook(mlx_key_data_t keydata, void *param);
void	key_hook( void *param);
double	deg_to_rad(double angle);
double	normalize_ray_angle(double angle);
void	check_dir(t_game *game);
void	facing(t_game *game, int j);
int		check(t_game *game, double y_ray, double x_ray);
void	init_game_data(t_game *game);
void	field_of_view(t_game *game);
// void	key_hook(mlx_key_data_t keydata, void *param);
void	render_view(t_game *game);
void	dda(t_game *game , int color, double  x1, double y1);
#endif
