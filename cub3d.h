/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:31:39 by mait-taj          #+#    #+#             */
/*   Updated: 2025/03/25 14:52:51 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "/Users/mait-taj/Desktop/MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "parsing/get_next_line/get_next_line.h"

/*$$$$$$$$$$$$$$$$$$$$$ macros $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
# define TILESIZE 25
# define WIDTH 1500
# define HEIGHT 1400
# define FOV 60
# define UP 1
# define DOWN 2
# define RIGHT 3
# define LEFT 4
# define SPEED 2

/*$$$$$$$$$$$$$$$$$$$$$ Struct $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef enum s_stat
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

typedef struct s_map
{
	char	**map;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	int		fl_color;
	int		ce_color;
	int		pl_xx;
	int		pl_yy;
	int		rwo;
	int		column;
	t_stat	start_position;
}	t_map;

typedef struct s_help
{
	int		i;
	int		x;
	int		player;
	char	*tmp;
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	c;
	bool	f;
}	t_help;

typedef struct s_filling
{
	char				*line;
	struct s_filling	*next;
}				t_filling;

typedef struct s_cub
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

/*$$$$$$$$$$$$$$$$$$$$$ Struct of rays and the player $$$$$$$$$$$$$$$$$$$$$$$*/
typedef struct s_ray{
	double	x_ray;
	double	y_ray;
	double	r_angle;
	int		facing_x;
	int		facing_y;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	bool	h_or_v;
	double	distance;
}	t_ray_cast;

typedef struct s_pixel
{
	int			**so_pexel;
	int			**no_pexel;
	int			**we_pexel;
	int			**ea_pexel;
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
}			t_pixel;

typedef struct p{
	t_cub		data;
	double		dir_angle;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray_cast	*ray;
	double		player_x;
	double		player_y;
	t_pixel		*pixels;
}t_game;

/*_______________ Textures Parts _____________________________________________*/
void	save_pixels(t_game *game);
void	load_images(t_game *game, mlx_image_t **img, char *text);
void	draw_wall(int *start_wall, t_game *game, int ray_counter,
			double line_H);
int		free_struct(t_cub *data);
int		get_rgba(int r, int g, int b, int a);

/*_______________________________ Parse Input ________________________________*/

bool	check_valid_extension(char *file_name);
bool	first_step_to_map(t_cub *data);
int		coun_line2(char **map);

/*__________ Utils ______________ Utils _________________ Utils ______________*/

t_filling	*create_node(t_cub *data,
		char *content);
size_t			ft_compare(char *s1, char *s2);
void		init_data(t_cub *data);
void		init_data_2(t_help *help, t_map *maps, t_stat stat);
void		before_filling(t_cub *data);
int			coun_line(char **map);
int			skip_spaces(char *str);
void		set_position(t_map *maps, char p);
void		add_node(t_filling **head, t_filling *new);
void		first_check_of_elem(t_cub *data);
void		set_bool(t_help *help, char c, t_cub *data);
bool		just_empty_line(char *line);
char		*extract_element(char *line, int j, char *src, t_cub *data);
void		path_if_exist(t_cub *data, char *line);
void		color_valid(t_cub *data, t_help *help, char *line);
bool		without_info(char *line);
char		*argcolor(t_cub *data, char *line, int index, int i);
size_t		until_new_line(char *str);
char		*just_path(char *line);
void		list_to_darray(t_cub *data, int i);
bool		is_a_player(char c);

/*+++++++++++++++++++++ Parse Map +++++++++++++++++++++++++++++++++++++++++*/

bool	check_line_element(t_help *help, char *line, t_cub *data);
void	all_element_is_good(t_cub *data);
bool	find_all_elem(t_help *help);
void	map_boundaries(int *end, char **map);
void	check_wall_of_map(t_cub *data);
bool	line_map(char *line, int i);
void	set_element(t_cub *data);
void	expand_texture(t_cub *data, char *info);
int		list_size(t_filling *mp);
void	insid_map(t_cub *data, int i);
void	reset_map(t_cub *data);
/*_________________________ Error message____________________________________*/

void	print_err(t_stat stat);
int		err(char *str);
void	complex_err(t_cub *data, char *str, char *i, char *j);
int		err_or(t_cub *data, char *str, char *index, int stat);

/*______________________________ Free Data __________________________________*/

void	free_d_arr(char **str);
void	free_map_ele(t_map *maps);
int		free_all_data(t_cub *data);
void	simple_err(t_cub *data, char *str);
int		destroy_texture(t_game *game);
void	free_dint(int **pex, mlx_image_t *img);

/*____________________________Recasting Part ________________________________*/
void	key_hook( void *param);
double	deg_to_rad(double angle);
double	normalize_ray_angle(double angle);
void	check_dir(t_game *game);
void	facing(t_game *game, int j);
void	init_game_data(t_game *game);
void	field_of_view(t_game *game);
void	render_view(t_game *game);
void	find_horizontal(t_game *game, int j);
void	find_vertical(t_game *game, int j);
void	update_position(t_game *game, int find, double nx, double ny);
#endif
