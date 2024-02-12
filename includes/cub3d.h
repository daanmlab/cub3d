/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:06:49 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/12 15:45:32 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"

typedef struct s_color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} t_color;

typedef struct s_map
{
    unsigned char **matrix;
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    struct s_color ceiling_color;
    struct s_color floor_color;
} t_map;

typedef struct s_game
{
    struct s_map map;
    int y;
} t_game;

/**
 * Parsing
*/
int parse(int argc, char const *argv[], t_game *game);

#endif