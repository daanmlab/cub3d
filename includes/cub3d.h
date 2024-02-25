/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:06:49 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/25 16:26:25 by tlouro-c         ###   ########.fr       */
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
# define TEXTURE_SIZE 64
# define PI 3.14159265

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;


typedef struct s_rectangle
{
	t_vector		start;
	unsigned int	width;
	unsigned int	height;
	unsigned int	color;
}	t_rectangle;

typedef struct s_player
{
	t_vector	position;
	t_vector	map_square;
	t_vector	dir;
	char		initial_dir;
	t_vector	plane;
	bool		is_walking;
	bool		is_walking_back;
	bool		is_walking_left;
	bool		is_walking_right;
	bool		is_running;
	bool		is_looking_right;
	bool		is_looking_left;
	int		pov_rotation_x_axis;
	int		pov_rotation_y_axis;
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
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int  color;
    int error;
}	t_color;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				endian;
	int				line_length;
    int             x;
    int             y;
}	t_img;

typedef struct s_map
{
	char		**matrix;
    int 		**real_map;
    char 		*north_texture;
    char 		*south_texture;
    char 		*west_texture;
    char 		*east_texture;
	t_vector	size;
    t_rectangle ceiling;
    t_rectangle floor;
}	t_map;

typedef struct s_textures
{
    t_img north;
    t_img south;
    t_img west;
    t_img east;
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


/**
 * Parsing
*/
int parse(int argc, char const *argv[], t_game *game);
int get_textures(int fd, t_game *game);
int	get_colors(int fd, t_game *game);
int get_matrix(int fd, t_game *game);
int find_player(t_game* game);
int do_floodfill(t_game *game);
void	*free_textures(t_game *game);

/**
 * utils
*/
void free_matrix(char **matrix);










//? tlouro-c

typedef struct s_engine t_engine;

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


//* Vector Functions

t_vector	new_vector(double x, double y);
t_vector	v_sum(t_vector v1, t_vector v2);
t_vector	v_mult(t_vector v1, double scalar);
t_vector	v_normalize(t_vector v);
t_vector	v_rotate(t_vector v1, double angle);
double		v_magnitude(t_vector v);

void		line(t_img *img, t_vector start, t_vector end, int color);
void		rectangle(t_img *img, t_rectangle rectangle);
void		my_mlx_pixel_put(t_img *img, t_vector vector, unsigned int color);
t_rectangle	new_rectangle(unsigned int width, unsigned int height,
		unsigned int color);

void	draw_floor_and_ceiling(t_game *game, t_map map, t_player player,
			 t_img *img);

void	draw_wall_line(t_engine *this, t_player *player, t_img *img);
void	setup_texture(t_engine *this, t_textures textures);
void	calculate_distances_to_wall(t_player *player, t_engine *this);
void	dda_find_wall(t_engine *this, int **map);
void	set_distances_to_sides(t_player *player, t_engine *this);

int		render_next_frame(t_game *game);


//* Constructors

t_player player_constructor(void);

int catch_key_press(int key, t_player *player);
int catch_key_release(int key, t_player *player);

void	event_listener(t_game *game);
int	clean_exit(t_game	*game);

#endif
