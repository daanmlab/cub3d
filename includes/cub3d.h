/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:06:49 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/18 23:29:16 by tlouro-c         ###   ########.fr       */
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

# define WIDTH 1080
# define HEIGHT 720

typedef struct s_position
{
    int y;
    int x;
} t_position;

typedef enum e_direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
}	t_direction;

typedef struct s_color
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int  color;
    int error;
} t_color;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				endian;
	int				line_length;
    int             x;
    int             y;
}					t_img;

typedef struct s_map
{
    char **matrix;
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    struct s_position size;
    struct s_color ceiling_color;
    struct s_color floor_color;
} t_map;

typedef struct s_textures
{
    struct s_img north;
    struct s_img south;
    struct s_img west;
    struct s_img east;
} t_textures;

typedef struct s_game
{
    struct s_map map;
    struct s_textures textures;
    struct s_color  ceiling_color;
    struct s_color  floor_color;
    struct s_player player;
    void			*mlx;
	void			*mlx_win;
    int y;
} t_game;


/**
 * Parsing
*/
int parse(int argc, char const *argv[], t_game *game);
int get_textures(int fd, t_game *game);
int	get_colors(int fd, t_game *game);
int get_matrix(int fd, t_game *game);
int get_player(t_game *game);
int do_floodfill(t_game *game);
void	*free_textures(t_game *game);

/**
 * utils
*/
void free_matrix(char **matrix);










//? tlouro-c

typedef struct s_vector	t_vector;
typedef struct s_player	t_player;
typedef struct s_engine t_engine;

struct s_vector
{
	double	x;
	double	y;
};

struct s_player
{
	t_vector	position;
	t_vector	map_square;
	t_vector	direction;
	t_vector	plane;
};

struct s_engine
{
	t_vector	ray_dir;
	t_vector	wall_square;
	double		plane_multiplier;
	double		delta_x;
	double		delta_y;
	double		dist_to_side_x;
	double		dist_to_side_y;
	double		step_x;
	double		step_y;
	double		dda_distance_x;
	double		dda_distance_y;
	double		player_to_wall_distance;
	double		perpendicular_distance;
	double		line_height;
	bool		wall_hit;
	t_direction	wall_direction;
};

//* Vector Functions

t_vector	new_vector(double x, double y);
t_vector	v_sum(t_vector v1, t_vector v2);
t_vector	v_mult(t_vector v1, double scalar);
t_vector	v_normalize(t_vector v);
t_vector	v_rotate(t_vector v1, double angle);
double		v_magnitude(t_vector v);


void		line(t_img *img, t_vector start, t_vector end, int color);

#endif
