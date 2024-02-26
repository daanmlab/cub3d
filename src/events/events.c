/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:05:38 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:21:07 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_listener(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 1L << 0, catch_key_press, &game->player);
	mlx_hook(game->mlx_win, 3, 1L << 1, catch_key_release, &game->player);
	mlx_hook(game->mlx_win, 17, 1L << 0, clean_exit, game);
}

int	clean_exit(t_game	*game)
{
	mlx_do_key_autorepeaton(game->mlx);
	ft_free_tab(game->map.matrix);
	mlx_destroy_image(game->mlx, game->player.primary_weapon.img);
	mlx_destroy_image(game->mlx, game->player.secondary_weapon.img);
	mlx_destroy_image(game->mlx, game->textures.east.img);
	mlx_destroy_image(game->mlx, game->textures.west.img);
	mlx_destroy_image(game->mlx, game->textures.north.img);
	mlx_destroy_image(game->mlx, game->textures.south.img);
	mlx_destroy_image(game->mlx, game->frame.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	ft_free_int_matrix(game->map.real_map, game->map.size.y);
	free(game->mlx);
	exit(0);
}

int	catch_key_press(int key, t_player *player)
{
	if (key == XK_w)
	{
		player->is_running++;
		player->is_walking = true;
	}
	else if (key == XK_s)
		player->is_walking_back = true;
	else if (key == XK_a)
		player->is_walking_left = true;
	else if (key == XK_d)
		player->is_walking_right = true;
	else if (key == XK_Shift_L)
		player->is_running++;
	else if (key == XK_Escape)
		player->exit = true;
	else if (key == XK_q)
	{
		if (player->weapon_type == PRIMARY)
			player->weapon_type = SECONDARY;
		else
			player->weapon_type = PRIMARY;
	}
	return (0);
}

int	catch_key_release(int key, t_player *player)
{
	if (key == XK_w)
	{
		player->is_walking = false;
		player->is_running--;
	}
	if (key == XK_s)
		player->is_walking_back = false;
	if (key == XK_a)
		player->is_walking_left = false;
	if (key == XK_d)
		player->is_walking_right = false;
	if (key == XK_Shift_L)
		player->is_running--;
	return (0);
}
