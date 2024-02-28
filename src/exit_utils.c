/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:44:41 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/27 12:12:59 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_images(t_game *game);

int	clean_exit(t_game	*game)
{
	if (game->map.matrix)
		ft_free_tab(game->map.matrix);
	if (game->map.real_map)
		ft_free_int_matrix(game->map.real_map, game->map.size.y);
	if (game->map.north_texture)
		free(game->map.north_texture);
	if (game->map.south_texture)
		free(game->map.south_texture);
	if (game->map.west_texture)
		free(game->map.west_texture);
	if (game->map.east_texture)
		free(game->map.east_texture);
	clear_images(game);
	if (game->mlx_win)
	{
		mlx_mouse_show(game->mlx, game->mlx_win);
		mlx_destroy_window(game->mlx, game->mlx_win);
	}
	if (game->mlx)
	{
		mlx_do_key_autorepeaton(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

static void	clear_images(t_game *game)
{
	if (game->player.primary_weapon.img)
		mlx_destroy_image(game->mlx, game->player.primary_weapon.img);
	if (game->player.secondary_weapon.img)
		mlx_destroy_image(game->mlx, game->player.secondary_weapon.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->mlx, game->textures.east.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->mlx, game->textures.west.img);
	if (game->textures.north.img)
		mlx_destroy_image(game->mlx, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->mlx, game->textures.south.img);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
}

void	*free_textures(t_game *game)
{
	if (game->map.north_texture)
		free(game->map.north_texture);
	if (game->map.south_texture)
		free(game->map.south_texture);
	if (game->map.west_texture)
		free(game->map.west_texture);
	if (game->map.east_texture)
		free(game->map.east_texture);
	if (game->textures.north.img)
		mlx_destroy_image(game->mlx, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->mlx, game->textures.south.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->mlx, game->textures.west.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->mlx, game->textures.east.img);
	return (NULL);
}

void	ft_free_int_matrix(int **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
