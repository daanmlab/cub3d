/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:06:49 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/15 18:12:50 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>


typedef struct s_position
{
    int y;
    int x;
} t_position;

enum Direction{
    NORTH = 'N',
    SOUTH = 'S',
    EAST = 'S',
    WEST = 'W'
};

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

typedef struct s_player
{
    struct s_position    initial_postion;
    enum Direction initial_direction;
} t_player;

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


#endif