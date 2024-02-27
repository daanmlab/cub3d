/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:06:49 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/27 14:28:32 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <X11/keysym.h>

# define WIDTH 1080
# define HEIGHT 720
# define TEXTURE_SIZE 512
# define PI 3.14159265

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				endian;
	int				line_length;
	int				x;
	int				y;
	int				width;
	int				height;
}	t_img;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef enum e_hud
{
	PRIMARY,
	SECONDARY
}	t_hud;

typedef struct s_pixel
{
	char			*adr;
	int				x;
	int				y;
	unsigned int	color;
	int				text_x;
	int				text_y;
}	t_pixel;

typedef struct s_rectangle
{
	t_vector		start;
	unsigned int	width;
	unsigned int	height;
	unsigned int	color;
}	t_rectangle;

typedef struct s_player
{
	t_hud		weapon_type;
	t_img		primary_weapon;
	t_img		secondary_weapon;
	t_vector	primary_weapon_origin;
	t_vector	secondary_weapon_origin;
	t_vector	position;
	t_vector	map_square;
	t_vector	dir;
	t_vector	plane;
	char		initial_dir;
	bool		exit;
	bool		is_walking;
	bool		is_walking_back;
	bool		is_walking_left;
	bool		is_walking_right;
	int			is_running;
	double		mouse_sensibility;
	int			last_mouse_x;
	int			delta_mouse_x;
	int			last_mouse_y;
	int			delta_mouse_y;
	double		pov_rotation_y_axis;
	double		animation_curve;
}	t_player;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	HORIZONTAL,
	VERTICAL
}	t_direction;

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	color;
	int				error;
}	t_color;

typedef struct s_map
{
	char		**matrix;
	int			**real_map;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_vector	size;
	t_rectangle	ceiling;
	t_rectangle	floor;
}	t_map;

typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
}	t_textures;

typedef struct s_game
{
	const char	*file;
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_textures	textures;
	t_player	player;
	void		*mlx;
	void		*mlx_win;
	t_img		frame;
}	t_game;

int					parse(int argc, char const *argv[], t_game *game);
int					get_textures(int fd, t_game *game);
int					get_colors(int fd, t_game *game);
int					get_matrix(int fd, t_game *game);
int					find_player(t_game *game);
int					do_floodfill(t_game *game);
void				*free_textures(t_game *game);
void				free_been_matrix(int **been, t_map *map);
char				**realloc_matrix(char **matrix);

typedef struct s_engine	t_engine;

struct s_engine
{
	t_vector		ray_dir;
	t_vector		wall_square;
	double			plane_multiplier;
	double			delta_x;
	double			delta_y;
	double			dist_to_side_x;
	double			dist_to_side_y;
	double			step_x;
	double			step_y;
	double			dda_distance_x;
	double			dda_distance_y;
	double			player_to_wall_distance;
	double			perpendicular_distance;
	double			line_height;
	double			text_y;
	double			text_y_step;
	double			text_x;
	double			wall_hit_x;
	unsigned int	pixel;
	bool			wall_hit;
	t_direction		wall_direction;
	t_img			selected_texture;
};

t_vector			new_vector(double x, double y);
t_vector			v_sum(t_vector v1, t_vector v2);
t_vector			v_mult(t_vector v1, double scalar);
t_vector			v_normalize(t_vector v);
t_vector			v_rotate(t_vector v1, double angle);
double				v_magnitude(t_vector v);

void				line(t_img *img, t_vector start, t_vector end, int color);
void				rectangle(t_img *img, t_rectangle rectangle);
void				my_mlx_pixel_put(t_img *img, t_vector vector,
						unsigned int color);
t_rectangle			new_rectangle(unsigned int width, unsigned int height,
						unsigned int color, t_vector origin);
void				draw_floor_and_ceiling(t_game *game, t_map map,
						t_player player, t_img *img);
void				draw_wall_line(t_engine *this, t_player *player,
						t_img *img);
void				setup_texture(t_engine *this, t_textures textures,
						t_player *player);
void				calculate_distances_to_wall(t_player *player,
						t_engine *this);
void				dda_find_wall(t_engine *this, int **map);
void				set_distances_to_sides(t_player *player, t_engine *this);
int					render_next_frame(t_game *game);
t_player			player_constructor(t_game *game);
int					catch_key_press(int key, t_player *player);
int					catch_key_release(int key, t_player *player);
void				event_listener(t_game *game);
int					clean_exit(t_game	*game);
void				running_animation(t_player *player);
bool				no_colision(t_player *player, char side, int **map);
t_vector			walk(t_player *player, char side, int **map);
void				apply_changes_on_player(t_game *game, t_player *player,
						int **map);
void				setup_ray(t_engine *this, t_player player);
void				dir_and_plane_rotate(t_vector *dir, t_vector *plane,
						double angle);
int					get_mouse_x(t_game *game);
int					get_mouse_y(t_game *game);
void				draw_hud_object(t_game *game, t_player *player);
void				setup_animation_curve(t_player *player);
void				changing_weapon_animation(t_player *player);
void				ft_free_int_matrix(int **matrix, int size);
t_img				img_constructor(t_game *game, char *filename);
t_game				game_constructor(void);
int					setup_window(t_game *game);

#endif
