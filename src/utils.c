/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:57:03 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/27 14:47:40 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_mouse_x(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->mlx_win, &x, &y);
	return (x);
}

int	get_mouse_y(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->mlx_win, &x, &y);
	return (y);
}

t_img	img_constructor(t_game *game, char *filename)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(game->mlx, filename,
			&img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

t_game	game_constructor(void)
{
	t_game	new;

	new.mlx = NULL;
	new.mlx_win = NULL;
	new.frame.img = NULL;
	new.map.east_texture = NULL;
	new.map.north_texture = NULL;
	new.map.south_texture = NULL;
	new.map.west_texture = NULL;
	new.map.matrix = NULL;
	new.map.real_map = NULL;
	new.player.primary_weapon.img = NULL;
	new.player.secondary_weapon.img = NULL;
	new.textures.east.img = NULL;
	new.textures.north.img = NULL;
	new.textures.south.img = NULL;
	new.textures.west.img = NULL;
	return (new);
}

int	setup_window(t_game *game)
{
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->mlx_win)
		return (ft_putstr_fd("error creating window\n", 2), -1);
	mlx_mouse_move(game->mlx, game->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_do_key_autorepeatoff(game->mlx);
	game->frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame.img)
		return (ft_putstr_fd("error creating image\n", 2), -1);
	game->frame.addr = mlx_get_data_addr(game->frame.img,
			&game->frame.bits_per_pixel, &game->frame.line_length,
			&game->frame.endian);
	if (!game->frame.addr)
		return (ft_putstr_fd("error getting image address\n", 2), -1);
	return (0);
}
