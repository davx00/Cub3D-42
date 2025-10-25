/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 08:53:36 by despanol          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define SCREEN_WIDTH 940
# define SCREEN_HEIGHT 640

typedef struct s_directions
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	right;
	bool	left;
}	t_directions;

typedef struct s_texture
{
	void	*img_text;
	char	*data;
	int		width;
	int		heght;
	int		pixel;
	int		length;
	int		endian;
}	t_texture;

typedef struct s_img
{
	void		*img;
	char		*data;
	int			pixel;
	int			length;
	int			endian;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_img;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		hit;
}	t_ray;

typedef struct s_npc
{
	double			x;
	double			y;
	double			angle;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			direct;
	int				count;
	t_directions	movement;
}	t_npc;

typedef struct s_map
{
	int		width;
	int		height;
	int		index;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**matriz;
	char	**matriz_new;
	int		rgb_roof[3];
	int		rgb_ground[3];
	double	parse;
	double	count_rgb;
	int		count_textures;
}	t_map;

typedef struct s_parse
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		fd;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*map_route;
	t_map	map;
	t_img	image;
	t_npc	npc;
	t_ray	ray;
}	t_parse;

int				check_file_extension(char *file_name);
int				parse(int argc, char **argv, t_parse *data);
char			**make_rectangular_map(char **map, t_parse *cub3d);
int				flood_fill(char **map, int x, int y, int height);
void			free_new_map(char **map, int limit);
void			complete_spaces(char *line, int i, int width);
int				printf_error(int error);
void			free_map(char **map_lines, t_parse *cub3d);
void			free_paths(t_parse *cub3d);
void			free_matriz_map(t_parse *cub3d);
void			free_new_matriz(t_parse *cub3d);
void			free_mlx_images(t_parse *cub3d);
int				free_all(t_parse *cub3d);
int				close_window(t_parse *cub3d);
void			validate_border_walls(char current_char,
					int x, int y, t_parse *cub3d);
int				needs_flood_fill_validation(char current_char);
void			validate_flood_fill(t_parse *cub3d,
					char **map_copy, char **rectangular_map, int coords[2]);
void			valid_map(t_parse *cub3d);
void			init_player_position(t_parse *cub3d,
					int x, int y, char direction);
void			find_and_set_player(t_parse *cub3d);
int				parse_texture_line(t_parse *cub3d, char *line);
int				process_texture_config(char *line, t_parse *cub3d);
void			free_str(char **str);
int				printf_error_rgb(char **color, char *clean);
int				process_rgb_component(char **color, int i, int *rgb);
int				validate_rgb_values(char *color_str, int rgb[3]);
int				parse_color_configuration(char *line, t_parse *cub3d);
int				is_map_line(char *line);
int				handle_map_line_content(char *line,
					t_parse *cub3d, char **map_lines);
int				is_line_empty_or_whitespace(const char *line);
int				parse_map(char *line, t_parse *cub3d, char **map_lines);
void			main_engine(t_parse *ctx);
void			initialize_image_and_textures(t_parse *game);
void			draw_ceiling_and_floor(t_parse *game);
void			render_scene(t_parse *game);
int				key_up(int key, t_parse *game);
int				key_down(int key, t_parse *game);
int				process_player_actions(t_parse *game);
bool			check_wall(t_parse *game, double x, double y);
void			render_wall_slice(t_parse *game, int x);
void			draw_wall_column(t_parse *game,
					int draw_start, int draw_end, int x);
void			fill_image_buffer(t_parse *game, int color);
void			move_npc(t_parse *game);
void			render_wall_slice(t_parse *game, int x);
void			render_buffer_to_window(t_parse *game);
void			validate_player_flood_fill(t_parse *cub3d,
					char **mp_cpy, int x, int y);
t_texture		*select_texture(t_parse *game);
double			calc_wall_x(t_parse *game);
int				calc_tex_x(t_parse *game, t_texture *texture, double wall_x);
int				calc_tex_y(t_parse *game,
					t_texture *texture, int draw_start, int y);
unsigned int	get_tex_color(t_texture *texture, int tex_x,
					int tex_y, int side);
void			calculate_step_and_side_dist(t_parse *game);
t_texture		*get_wall_texture(t_parse *game);
int				calculate_tex_x(t_parse *game, t_texture *texture);
int				calculate_tex_y(t_texture *texture, int draw_start, int y,
					double perp_wall_dist);

#endif