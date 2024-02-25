/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:05:38 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/25 16:26:49 by tlouro-c         ###   ########.fr       */
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
	//mlx_mouse_show(game->mlx, game->mlx_win);
	mlx_destroy_image(game->mlx, game->frame.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(1);
}


int catch_key_press(int key, t_player *player)
{
	if (key == XK_w)
		player->is_walking = true;
	if (key == XK_s)
		player->is_walking_back = true;
	if (key == XK_a)
		player->is_walking_left = true;
	if (key == XK_Left)
		player->is_looking_left = true;
	if (key == XK_d)
		player->is_walking_right = true;
	return (0);
}

int catch_key_release(int key, t_player *player)
{
	if (key == XK_w)
		player->is_walking = false;
	if (key == XK_s)
		player->is_walking_back = false;
	if (key == XK_a)
		player->is_walking_left = false;
	if (key == XK_d)
		player->is_walking_right = false;
	if (key == XK_Left)
		player->is_looking_left = false;
	return (0);
}
